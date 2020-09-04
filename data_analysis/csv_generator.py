"""
CSV generator to exercise with data analysis example
"""
# pylint: disable-msg=too-many-locals
# pylint: disable-msg=too-many-locals

import sys
# import json
import csv
import random
# import itertools
import pathlib
import time


def main():
    """
    main function
    """
    start = time.time()
    input_format = str('cols rows filename')
    bad_input_message = str('call as: csv_generator.py ') + input_format

    # get user input
    if len(sys.argv) < 4:
        print(bad_input_message)
        sys.exit()

    try:
        cols = int(sys.argv[1])
        rows = int(sys.argv[2])
    except ValueError:
        print('bad cols or rows\n{0}'.format(bad_input_message))
        sys.exit()
    print('cols: {0} rows: {1}'.format(cols, rows))

    out_file_name = pathlib.Path(sys.argv[3])
    if not out_file_name.parent.is_dir:
        print('bad filename\n{0}'.format(bad_input_message))
        sys.exit()
    print('filename: {0}'.format(out_file_name))

    # define data format
    names = ['Luca', 'Alberto', 'Davide', 'Marco', 'Federico', 'Giuseppe']
    surnames = ['rossi', 'verdi', 'neri', 'bianchi', 'arancioni', 'blu']
    float_range = [1.0, 1000000.0]
    int_range = [1, 1000]

    def fun_float():
        return random.uniform(float_range[0], float_range[1])

    def fun_int():
        return random.randint(int_range[0], int_range[1])

    def fun_names():
        return names[random.randint(0, len(names)-1)]

    def fun_surnames():
        return surnames[random.randint(0, len(surnames)-1)]

    def fun_time():
        return int(round(time.time() * 1000))

    data = {
        'float numbers': fun_float,
        'names': fun_names,
        'int numbers': fun_int,
        'surnames': fun_surnames,
        'time': fun_time
        }

    # create matrix representing csv file rows
    file_output = [[0 for x in range(cols)]for y in range(rows)]

    lst = list(range(cols-int(cols % len(data.keys()))))
    for ind_col in lst[0::len(data.keys())]:
        for ind_col_shift in range(len(data.keys())):
            file_output[0][ind_col+ind_col_shift] = \
                    list(data.keys())[ind_col_shift]

    for ind_row in range(1, rows):
        for ind_col in lst[0::len(data.keys())]:
            for ind_col_shift in range(len(data.keys())):
                file_output[ind_row][ind_col+ind_col_shift] = \
                        data[list(data.keys())[ind_col_shift]]()

    last_indeces_start = cols-int(cols % len(data.keys()))
    for final_ind in range(last_indeces_start, cols):
        file_output[0][final_ind] = \
                list(data.keys())[final_ind-last_indeces_start]

    for ind_row in range(1, rows):
        for final_ind in range(last_indeces_start, cols):
            file_output[ind_row][final_ind] = \
                    data[list(data.keys())[final_ind-last_indeces_start]]()

    # print(file_output)

    # save matrix to the csv file
    if out_file_name.suffix != 'csv':
        out_file_name = pathlib.Path(str(out_file_name)+'.csv')

    out = open(str(out_file_name), "w")

    print('saving to {}'.format(str(out_file_name)))
    csv_writer = csv.writer(out, delimiter=',', quotechar='"',
                            quoting=csv.QUOTE_MINIMAL)
    csv_writer.writerows(file_output)

    out.close()

    end = time.time()
    print('time: {}'.format(end-start))


if __name__ == "__main__":
    main()
