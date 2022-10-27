from cs50 import get_string
import re


def main():
    while True:
        card = get_string("Number: ")
        if re.match(r"\d+", card):
            break

    if validation(card):
        if re.match(r"^5[12345]", card) and re.match(r"\d{16}", card):
            print("MASTERCARD")

        elif re.match(r"^3[47]", card) and re.match(r"\d{15}", card):
            print("AMEX")

        elif re.match(r"^4", card) and re.match(r"\d{13,17}", card):
            print("VISA")

        else:
            print("INVALID")

    else:
        print("INVALID")


def validation(card):
    sum1 = 0
    sum2 = 0

    for c in range(len(card) - 2, -1, -2):
        if (int(card[c]) * 2) > 9:
            sum1 += int(str(int(card[c]) * 2)[0])
            sum1 += int(str(int(card[c]) * 2)[1])
        else:
            sum1 += int(card[c]) * 2

        sum2 += int(card[c + 1])

    if len(card) % 2 == 1:
        sum2 += int(card[0])

    total = sum1 + sum2
    return (total % 10 == 0)


main()