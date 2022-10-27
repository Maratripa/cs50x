from cs50 import get_string


def main():
    line = get_string("Text: ")

    characters = 0
    words = 1
    sentences = 0

    for c in line:
        if c.isalpha():
            characters += 1

        if c == " ":
            words += 1

        if c in ['.', '!', '?']:
            sentences += 1

    grade = (0.0588 * (100 * characters / words)) - (0.296 * (100 * sentences / words)) - 15.8

    if grade < 1:
        print("Before Grade 1")

    elif 1 <= grade < 16:
        print(f"Grade {round(grade)}")

    else:
        print("Grade 16+")


main()