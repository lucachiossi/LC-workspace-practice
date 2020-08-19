"""This script generate a file inputfile.txt"""

import sys
import random

if len(sys.argv) != 3:
    print("ERROR: pleas call\ninput_file_generator.py <size> <range>")

INPUT_SIZE = int(sys.argv[1])
INPUT_RANGE = int(sys.argv[2])

PATH = "./inputfile.txt"
INPUT_FILE = open(PATH, 'w')

for x in range(0, INPUT_SIZE):
    RAND_VALUE = random.randint(1, INPUT_RANGE)
    INPUT_FILE.write(str(RAND_VALUE))
    if x != INPUT_SIZE-1:
        INPUT_FILE.write(", ")

INPUT_FILE.close()
