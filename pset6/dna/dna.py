import sys
import csv


def main(args):
    if len(args) != 3:
        print("Usage: dna.py DATABASE SEQUENCE")
        return 1

    f1 = open(args[2], 'r')
    seq = f1.readlines()[0]
    f1.close()

    f2 = open(args[1], 'r')
    reader = csv.DictReader(f2)
    ls = [i for i in reader]
    f2.close()

    strs = {}
    for key in ls[0]:
        if key != "name":
            strs[key] = 1

    for s in strs:
        while s * (strs[s] + 1) in seq:
            strs[s] += 1

    some_found = False
    for p in ls:
        valid = True
        for key in strs:
            if int(p[key]) != strs[key]:
                valid = False

        if valid:
            print(p["name"])
            some_found = True

    if not some_found:
        print("No match")


main(sys.argv)