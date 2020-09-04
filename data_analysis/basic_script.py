"""
BASIC SCRIPT for DATA ANALYSIS
"""
import sys
import pathlib
import time
import pandas
# import matplotlib.pyplot as plt
# import seaborn as sns
# import numpy as np
# import scipy as sci
# import statsmodels.api as sm
# from sklearn.datasets import load_boston
# from sklearn.linear_model import LinearRegression
# from sklearn.model_selection import train_test_split
# from sklearn.linear_model import LogisticRegression
# from sklearn.naive_bayes import GaussianNB
# from statsmodels.stats.outliers_influence import variance_inflation_factor
# from sklearn.tree import DecisionTreeRegressor


def main():
    """
    main function
    """
    start = time.time()
    input_format = str('input_filename')
    bad_input_message = str('call as: basic_script.py ') + input_format

    # get user input
    if len(sys.argv) < 2:
        print(bad_input_message)
        sys.exit()

    input_file = pathlib.Path(sys.argv[1])

    if not input_file.exists():
        print('bad input_filename\n{0}'.format(bad_input_message))
        sys.exit()

    print('filename: {}'.format(input_file))

    # read dataset
    data_set = pandas.read_csv(input_file, decimal='.', sep=',')

    # analize data description
    description_file = '/tmp/basic_script_dataset_describe.txt'
    tmp_file = open(description_file, 'w')
    tmp_file.write(data_set.describe().to_string())
    tmp_file.close()
    print('data set description available at "{}"'.format(description_file))

    # filter dataset

    # plot on graphs

    end = time.time()
    print('time: {}'.format(end-start))


if __name__ == "__main__":
    main()
