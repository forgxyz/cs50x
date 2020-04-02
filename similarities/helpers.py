from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # files have been opened by the compare program - being passed the contents

    # declare variables for program
    tempA, tempB = "", ""
    setA, setB = set(), set()
    cursorA, cursorB = 0, 0

    # iterate through lines in a
    # scan until \n is found
    for char in a:
        if char == "\n":
            # end of the line
            # add the line stored in temp to the set
            setA.add(tempA)
            tempA = ""
        else:
            # concatenate char to temporary storage
            tempA += char
            # increase cursor counter
        cursorA += 1
        if cursorA == len(a):
            # necessary in case the file does not end with a newline so last line is not left in temp
            setA.add(tempA)
            tempA = ""

    # repeat for b
    for char in b:
        if char == "\n":
            # end of the line
            # add the line stored in temp to the set
            setB.add(tempB)
            tempB = ""
        else:
            # concatenate char to temporary storage
            tempB += char
            # increase cursor counter
        cursorB += 1
        if cursorB == len(b):
            # necessary in case the file does not end with a newline so last line is not left in temp
            setB.add(tempB)
            tempB = ""

    # use intersection() method on the two sets
    # return set of lines found in both files
    return setA.intersection(setB)


def sentences(a, b):
    """Return sentences in both a and b"""

    # tokenize a and b into strings
    setA, setB = set(sent_tokenize(a)), set(sent_tokenize(b))

    # return those sentences found in both a and b
    return setA.intersection(setB)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # check n against length of a & b
    if (n > len(a)) or (n > len(b)):
        return ""

    # declare variables for program
    cursorA, cursorB = 0, 0
    tempA, tempB = "", ""
    setA, setB = set(), set()

    # slice a / b into bites n chars long
    # for each char, take that + n more and add it to a set
    for char in a:
        for i in range(n):
            tempA += a[cursorA + i]
        if "\n" not in tempA:
            setA.add(tempA)
        tempA = ""
        cursorA += 1
        if (cursorA + n) > len(a):
            break

    for char in b:
        for i in range(n):
            tempB += b[cursorB + i]
        if "\n" not in tempB:
            setB.add(tempB)
        tempB = ""
        cursorB += 1
        if (cursorB + n) > len(b):
            break

    return setA.intersection(setB)
