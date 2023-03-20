#!/bin/python3

# regexr replace via command line

import re
import sys

def main():
    if len(sys.argv) != 3:
        print('Usage: python regexr.py <regex> <replacement>')
        exit(1)

    regex = sys.argv[1]
    replacement = sys.argv[2]

    for line in sys.stdin:
        print(re.sub(regex, replacement, line), end='')
        

if __name__ == '__main__':
    main()