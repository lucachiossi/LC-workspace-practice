"""
BASIC SCRIPT for DATA ANALYSIS
"""
# import pandas as pd
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
    input_format = str('cols rows filename')
    bad_input_message = str('call as: csv_generator.py ') + input_format

    # get user input
    if len(sys.argv) < 4:
        print(bad_input_message)
        sys.exit()

# Filter input

# Make graphs

if __name__ == "__main__":
    main()
