from cs50 import get_float


def main():
    # get change from user and ensure it is a positive number
    while True:
        change = get_float("how much change is owed: ")
        if change > 0:
            break

    # remove the decimal and any imprecision
    change = round(change * 100)
    count = 0

    # check for each coin
    while change > 24:
        # quarters
        change -= 25
        count += 1
    while change > 9:
        # dimes
        change -= 10
        count += 1
    while change > 4:
        # nickels
        change -= 5
        count += 1
    while change > 0:
        # pennies
        change -= 1
        count += 1

    print(count)


if __name__ == "__main__":
    main()
