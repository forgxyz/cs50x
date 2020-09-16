from cs50 import get_int


# take integer input from user and print a pyramid
def main():
    # restrict range of inputs between 1 and 8
    while True:
        height = get_int("height: ")
        if height in range(1, 9):
            break

    # iterate through rows
    for i in range(1, height + 1):
        # print whitespace
        for j in range(height - i):
            print(" ", end="")
        # print hash
        for k in range(i):
            print("#", end="")
        # print middle whitespace
        for l in range(2):
            print(" ", end="")
        # print final hash
        for m in range(i):
            print("#", end="")
        # print newline
        print()


if __name__ == "__main__":
    main()