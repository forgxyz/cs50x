# this program checks a credit card against Luhn's Algorithm


from cs50 import get_float, get_int, get_string


def main():

    ccNum = get_int("please enter a credit card number for testing: ")
    length = len(str(ccNum))
    if length < 13 or length > 17:
        print("INVALID")
        return 1

    if checksum(ccNum):
        # valid credit card number, now check issuer
        # All American Express numbers start with 34 or 37
        if int(str(ccNum)[0]) == 3 and (int(str(ccNum)[1]) == 4 or int(str(ccNum)[1]) == 7):
            print("AMEX")
        # most MasterCard numbers start with 51, 52, 53, 54, or 55
        elif int(str(ccNum)[0]) == 5 and (int(str(ccNum)[1]) > 0 and int(str(ccNum)[1]) < 6):
            print("MASTERCARD")
        # and all Visa numbers start with 4.
        elif int(str(ccNum)[0]) == 4:
            print("VISA")
        else:
            print("INVALID")
            exit(2)


def checksum(ccNum):
    # Luhn's Algorithm:
    # multiply every other digit, starting with the last
    index = -1
    bucket = 0
    for i in range(len(str(ccNum))):
        if i % 2 == 0:
            # add the digits from ccNum what were not doubled (odd reverse index)
            bucket += int(str(ccNum)[index])

        else:
            # double the digit (odd reverse index)
            temp = int(str(ccNum)[index]) * 2
            if temp > 9:
                bucket += (temp - 9)
            else:
                bucket += temp

        index -= 1

    # if total % 10 = 0, the cc number is valid
    if bucket % 10 == 0:
        return True
    else:
        print("INVALID")
        exit(1)


if __name__ == "__main__":
    main()