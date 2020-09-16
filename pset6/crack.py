# this program decrypts passwords hashed with C's crypt function

from sys import argv
import crypt


def main():
    # ensure proper usage
    if len(argv) != 2:
        print("usage: python crack.py hash")
        exit(1)

    # store the hash and salt from user input
    usrhash = argv[1]
    salt = usrhash[0:2]
    length = 52

    # run crypt on string and compare the result to hash
    # start with 1 letter string and check a-zA-Z
    for i in range(0, 5):
        # iterate first letter
        for j in range(length):
            # test one char length password
            # will only run this when i is 0
            if i == 0:
                testword = convert(j)
                temp = crypt.crypt(testword, salt)
                if temp == usrhash:
                    print(testword)
                    exit(0)
            else:
                # iterate second letter
                for k in range(length):
                    # test two char length password
                    if i == 1:
                        testword = convert(j) + convert(k)
                        temp = crypt.crypt(testword, salt)
                        if temp == usrhash:
                            print(testword)
                            exit(0)
                    else:
                        # iterate third letter
                        for l in range(length):
                            # test three char length password
                            if i == 2:
                                testword = convert(j) + convert(k) + convert(l)
                                temp = crypt.crypt(testword, salt)
                                if temp == usrhash:
                                    print(testword)
                                    exit(0)
                            else:
                                # iterate fourth letter
                                for m in range(length):
                                    # test fourth char length password
                                    if i == 3:
                                        testword = convert(j) + convert(k) + convert(l) + convert(m)
                                        temp = crypt.crypt(testword, salt)
                                        if temp == usrhash:
                                            print(testword)
                                            exit(0)
                                    else:
                                        # iterate fifth letter
                                        for n in range(length):
                                            # test fifth char length password
                                            testword = convert(j) + convert(k) + convert(l) + convert(m) + convert(n)
                                            temp = crypt.crypt(testword, salt)
                                            if temp == usrhash:
                                                print(testword)
                                                exit(0)


def convert(i):
    if i >= 0 and i < 26:
        ltr = chr(i + 65)
        return ltr
    else:
        ltr = chr(i + 97)
        return ltr


if __name__ == "__main__":
    main()