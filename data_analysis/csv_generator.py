"""
CSV generator to exercise with data analysis example
"""

import sys
# import json
import csv
# import random
# import itertools
import pathlib


def main():
    """
    main function
    """
    input_format = str('cols rows filename')
    bad_input_message = str('call as: csv_generator.py ') + input_format

    if len(sys.argv) < 4:
        print(bad_input_message)
        sys.exit()

    try:
        cols = int(sys.argv[1])
        rows = int(sys.argv[2])
    except ValueError:
        print('bad cols or rows\n{0}'.format(bad_input_message))
        sys.exit()
    print('generate csv files with {0} cols and {1} rows'.format(cols, rows))

    out_file_name = pathlib.Path(sys.argv[3])
    if not out_file_name.parent.is_dir:
        print('bad filename\n{0}'.format(bad_input_message))
        sys.exit()
    print('save result to file {0}'.format(out_file_name))

    file_output = [[0 for x in range(cols)]for y in range(rows)]
    for x_ind in range(rows):
        for y_ind in range(cols):
            print(file_output[x_ind][y_ind])
    print(file_output)

    if out_file_name.suffix != 'csv':
        out_file_name.suffix = 'csv'

    if out_file_name.exists():
        out = open(str(out_file_name), "w")
        out.write('')
        out.close()

    out = open(str(out_file_name), "a")

    csv_writer = csv.writer(out, delimiter=',', quotechar='"',
            quoting=csv.QUOTE_MINIMAL
            )

    csv_writer.writerows(file_output)

    out.close()


if __name__ == "__main__":
    main()
