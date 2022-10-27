from cs50 import get_int


def main():
    while True:
        height = get_int("Height: ")
        if 1 <= height <= 8:
            break

    build_pyramid(height, height)


def build_pyramid(h, j):
    if h == 1:
        print(" " * (j - 1), end='')
        print("#  #")

    else:
        build_pyramid(h - 1, j)
        print(" " * (j - h) + '#' * h + '  ' + '#' * h)


main()
