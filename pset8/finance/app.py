import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
# if not os.environ.get("API_KEY"):
#     raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # set-up variables
    userid = session.get("user_id")
    userdata = db.execute("SELECT * FROM users WHERE id=:userid", userid=userid)
    holdings = db.execute("SELECT symbol, SUM(shares) FROM tx WHERE id=:userid GROUP BY symbol", userid=userid)
    username = userdata[0]['username']
    cash = userdata[0]['cash']

    # create table
    # symbol, shares, current price, value
    # then cash
    table = ''
    totalval = cash
    for row in holdings:
        shares = row['SUM(shares)']
        if shares != 0:
            symbol = row['symbol']
            price = float(lookup(symbol)['price'])
            value = shares * price
            totalval += value
            table += f"<tr><td>{symbol.upper()}</td><td>{shares}</td><td>{usd(price)}</td><td>{usd(value)}</td></tr>"

    table += f"<tr><td>CASH</td><td>{cash:,.2f}</td><td>{usd(1)}</td><td>{usd(cash)}</td></tr>"
    table += f"<tr><td>Total Value</td><td></td><td></td><td>{usd(totalval)}</td></tr>"

    return render_template("index.html", table=table, username=username)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        # set variables
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        quote = lookup(symbol)
        price = quote['price']
        cost = shares * price
        userid = session.get("user_id")
        cash = (db.execute("SELECT * FROM users WHERE id=:userid", userid=userid))[0]['cash']

        if not symbol:
            return apology("you must enter a ticker!")

        if not quote:
            return apology("invalid ticker")

        if shares < 0:
            return apology("cannot buy negative shares!")

        if cost > cash:
            return apology("not enough cash")

        # update cash balance to reflect purchase
        db.execute("UPDATE users SET cash=:cash WHERE id=:userid", cash=(cash-cost), userid=userid)

        # record purchase in table "tx"
        """tx fields:
            txid
            id
            type
            shares
            price
            symbol
            timestamp"""
        db.execute("INSERT INTO tx (id, type, shares, price, symbol) VALUES (:userid, 1, :shares, :price, :symbol)", userid=userid, shares=shares, price=price, symbol=symbol)
        return redirect("/")

    else:
        return render_template("buy.html")



@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    username = request.args.get('username')
    if len(username) < 1 or not db.execute("SELECT * FROM users WHERE username=:username", username=username):
        return jsonify(False)
    else:
        return jsonify(True)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    tabledata = db.execute("SELECT * FROM tx WHERE id=:userid", userid=session.get('user_id'))
    table = ''

    for row in tabledata:
        if row['type'] == 1:
            txtype = "Buy"
        else:
            txtype = "Sell"

        symbol = row['symbol']
        shares = row['shares']
        price = row['price']
        timestamp = row['timestamp']
        table += f"<tr><td>{txtype}</td><td>{symbol.upper()}</td><td>{shares}</td><td>{usd(price)}</td><td>{usd(shares * price)}</td><td>{timestamp}</td></tr>"

    return render_template("history.html", table=table)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("you must enter a symbol!")
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("invalid ticker")
        return render_template("quoted.html", name=quote['name'], price=usd(quote['price']), symbol=quote['symbol'])
    else:
        return render_template("quote.html")

    """error handle when the form is empty or ticker invalid"""


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # check method - if POST then ping database
    if request.method == "POST":
        # check username field: if empty or in use
        if not request.form.get("username"):
            return apology("username must not be empty")

        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) != 0:
            length = len(rows)
            return apology("username taken, please try another", length)

        # check password against confirmation
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("passwords do not match!")

        # username unique and passwords match
        # hash the password
        hash = generate_password_hash(request.form.get("password"))

        # store user login and password
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash=hash)

        return redirect("/")
    # else (GET) render webpage
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # render holdings
    userid = session.get("user_id")
    if not db.execute("SELECT * FROM tx WHERE id=:userid", userid=userid):
        return render_template("sell.html")

    userdata = db.execute("SELECT users.id, users.username, users.cash, tx.txid, tx.type, tx.shares, tx.price, tx.symbol FROM users JOIN tx ON users.id=tx.id WHERE users.id=:userid", userid=userid)
    cash = userdata[0]['cash']

    if request.method=='POST':
        symbol = request.form.get('symbol').lower()
        shares = int(request.form.get('shares'))
        holdings = db.execute("SELECT symbol, SUM(shares) FROM tx WHERE id=:userid GROUP BY symbol", userid=userid)
        price = lookup(symbol)['price']
        value = price * shares

        # check user input against owned shares
        for row in holdings:
            if symbol == row['symbol']:
                if shares > row['SUM(shares)']:
                    return apology("you don't own that many shares to sell!")

        # sell shares
        # record transaction as negative shares and the price
        db.execute("INSERT INTO tx (id, type, shares, price, symbol) VALUES (:userid, 0, :shares, :price, :symbol)", userid=userid, shares=-shares, price=price, symbol=symbol)

        # increase cash by price * shares sold
        db.execute("UPDATE users SET cash=:cash WHERE id=:userid", cash=cash+value, userid=userid)

        return redirect("/")
    else:
        # fill out table options
        options = ''
        for row in userdata:
            symbol = (row['symbol'].upper())
            if symbol not in options:
                options += f"""<option value="{symbol}">{symbol}</option>"""
        return render_template("sell.html", options=options)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
