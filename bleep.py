#!/rsr/bin/env python3

from sys import argv


def main():
    # check command line argument - accept just one
    if len(argv) != 2:
        print("usage: python bleep.py dictionary.txt")
        exit(1)

    dictionary = argv[1]

    # open the dictionary file and write the banned words to a set
    banned = set(line.strip() for line in open(dictionary))

    # prompt user for a message
    usrInput = input("please enter a sentence: ")

    # tokenize message using split into a dictionary
    token = usrInput.split()

    # check each token against the banned set
    for word in token:
        if word.lower() in banned:
            # overwrite each letter with * censor
            censor = "*" * len(word)
            print(censor + " ", end="")
        else:
            # otherwise just print it
            print(word + " ", end="")
    print("")


if __name__ == "__main__":
    main()