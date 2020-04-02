# this program implements caesar's cipher

from cs50 import get_string
from sys import argv


def main():
    # pseudocode:
    # accept one command line argement: an integer key
    if len(argv) != 2:
        print("usage: python caesar.py key")
        exit(1)
    print(len(argv))

    key = int(argv[1])

    # prompt user for plaintext
    plaintext = get_string("plaintext: ")

    # encrypt the message using the key where the integer is the alphabetical offset
    ciphertext = caesar(plaintext, key)

    # return the encrypted ciphertext to the user
    print("ciphertext: " + ciphertext)


def caesar(plaintext, key):
    i = 0
    ciphertext = ""
    for char in plaintext:
        if char.isupper():
            # if upper, offset is 65
            ciphertext = ciphertext + chr(((((ord(char) - 65 + (key % 26)) % 26)) + 65))

        elif char.islower():
            # if lower, offset is 97
            ciphertext = ciphertext + chr(((((ord(char) - 97 + (key % 26)) % 26)) + 97))

        else:
            # if space or character, do not modify
            ciphertext = ciphertext + char
        i += 1

    return ciphertext


if __name__ == "__main__":
    main()