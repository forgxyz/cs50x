#!/rsr/bin/env python3

from sys import argv


def main():
    # check command line arguments
    if len(argv) != 2:
        print("usage: python vigenere.py keyword")
        exit(1)
    elif not argv[1].isalpha():
        print("key must be alphabetical only")
        exit(1)

    # set-up variables for later use
    k = argv[1]  # keyword
    pos = 0  # position indicator for iterating through keyword
    c = []  # list for adding encrypted letters

    # prompt user for plaintext string
    p = input("plaintext: ")

    # encrypt plaintext
    for l in p:
        # encrypt letter l with k[index % len(k)] where index counts +1 with each runthrough of the loop
        c.append(encrypt(l, k[pos % len(k)]))
        if l.isalpha():
            pos += 1

    print("ciphertext: {}".format("".join(c)))


def encrypt(letter, key):
    # the key is not case sensitive
    key = (ord(key.upper()) - 65)

    if letter.isalpha():
        if letter.isupper():
            # 65
            letter = (((ord(letter) - 65) + key) % 26) + 65
            return chr(letter)
        elif letter.islower():
            # 97
            letter = (((ord(letter) - 97) + key) % 26) + 97
            return chr(letter)
    else:
        return letter


if __name__ == "__main__":
    main()