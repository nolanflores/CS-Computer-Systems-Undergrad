# Author: Derek Lilienthal
# Description: Test suite for assignment 1 algorithms using pytest

import pytest
import os
import sys
import time
import numpy as np

# Change the current working directory to this file's directory
os.chdir(os.path.dirname(os.path.abspath(__file__)))
path_to_this_file = os.path.dirname(os.path.abspath(__file__))

INPUT1_PATH = "./ex_input1.txt"
INPUT2_PATH = "./ex_input2.txt"
INPUT3_PATH = "./ex_input3.txt"
INPUT4_PATH = "./ex_input4.txt"
INPUT5_PATH = "./ex_input5.txt"
INPUT_10000_PATH = "./input_10000.txt"
INPUT_1000_PATH = "./input_1000.txt"

OUTPUT1_PATH = "./ex_output1.txt"
OUTPUT2_PATH = "./ex_output2.txt"
OUTPUT3_PATH = "./ex_output3.txt"
OUTPUT4_PATH = "./ex_output4.txt"
OUTPUT5_PATH = "./ex_output5.txt"

import subprocess
import os
import glob
from pathlib import Path
from typing import List, Tuple
import pandas as pd

TIMED_TARGET_FILE = INPUT_1000_PATH

# from a1_utils import *

RESULTS_DF = pd.DataFrame(columns=["Algorithm", "Input File", "Output File", "Expected Output", "Test Output", "Match", "Missing Numbers", "Extra Numbers", "True Distance", "Test Distance"])

from typing import List, Tuple


def compare_lists(
    list1: List[List[float]],
    list2: List[List[float]],
    tolerance: float = 0.5
) -> Tuple[bool, List[float], List[float], float, float]:
    """
    Compares two lists of lists of numbers to ensure they are equal based on the given criteria:

    1. Checks if the lists match exactly in order (with a given tolerance).
    2. If they do not match in order, checks if all numbers in list1 appear in list2 (again, with tolerance), ignoring order.
    3. If some numbers from list1 are missing in list2, returns which numbers are missing.
    4. If the second list has extra numbers that aren't matched in the first, returns which numbers are extra.
    5. Uses the specified tolerance to compare closeness of floating-point values.
    6. Returns the first number in both lists (sublist[0] for the first sublist in each list).

    Args:
        list1 (List[List[float]]): The first list of lists.
        list2 (List[List[float]]): The second list of lists.
        tolerance (float): The acceptable range for comparing numbers.

    Returns:
        Tuple[bool, List[float], List[float], float, float]:
            A tuple containing:
              - A boolean indicating if the lists are considered equal under the rules.
              - A list of missing numbers from list1 that are not found in list2.
              - A list of extra numbers found in list2 that do not match any in list1.
              - The first number of list1.
              - The first number of list2.
    """
    def is_close(a: float, b: float, tol: float) -> bool:
        return abs(a - b) <= tol

    # Safely extract the first number in each list if present
    first_num_list1 = list1[0][0] if list1 and list1[0] else None
    first_num_list2 = list2[0][0] if list2 and list2[0] else None

    # (1) Check if lists match exactly in order (with tolerance).
    if len(list1) == len(list2):
        order_match = True
        for sublist1, sublist2 in zip(list1, list2):
            if len(sublist1) != len(sublist2):
                order_match = False
                break
            for num1, num2 in zip(sublist1, sublist2):
                if not is_close(num1, num2, tolerance):
                    order_match = False
                    break
            if not order_match:
                break
        if order_match:
            # If everything matches in order, return True, no missing or extra.
            return True, [], [], first_num_list1, first_num_list2

    # (2) If not matching in order, flatten both lists and compare ignoring order.
    flat_list1 = [num for sublist in list1 for num in sublist]
    flat_list2 = [num for sublist in list2 for num in sublist]

    used_indices = set()
    missing_numbers = []

    # Try to match each element of list1 to a distinct element in list2 within tolerance.
    for num1 in flat_list1:
        found_match = False
        for i, num2 in enumerate(flat_list2):
            if i not in used_indices and is_close(num1, num2, tolerance):
                used_indices.add(i)
                found_match = True
                break
        if not found_match:
            missing_numbers.append(num1)

    # Identify extra numbers in list2 that were never matched.
    extra_numbers = [flat_list2[i] for i in range(len(flat_list2)) if i not in used_indices]

    # If there are any missing or extra numbers, the lists are not considered equal.
    if missing_numbers or extra_numbers:
        return False, missing_numbers, extra_numbers, first_num_list1, first_num_list2

    # Otherwise, the lists match ignoring order.
    return True, [], [], first_num_list1, first_num_list2

def read_file_to_list(input_file: str):
    """
    This function reads the input file and returns a list of lists

    Args:
    input_file: str - The input file to read

    Returns:
    List[list] - The list of lists of the input file
    """
    data = []
    with open(input_file, 'r') as f:
        for line in f:
            # Split line by whitespace and convert each to float
            numbers = line.strip().split()
            # Read each number as a float
            row = [float(x) for x in numbers]
            data.append(row)
    return data


def run_script_with_output(script_path, input_file):
    """
    Runs a Python script with a positional argument and returns the most recently
    created text file in the script's directory.

    Parameters:
        script_path (str): Path to the Python script to run.
        arg (str): The positional argument to pass to the script.

    Returns:
        str: Path to the most recently created text file in the script's directory, or None if no text files are found.
    """
    # Resolve absolute path of the script
    script_path = Path(script_path).resolve()

    # Get the directory of the script
    script_dir = script_path.parent

    # Run the script with the positional argument
    print(f"Running script: {script_path} {input_file}")
    try:
        subprocess.run([ "/home/derek/OSU/RAG-experiements/rag_venv_311/bin/python3", str(script_path), input_file], check=True, cwd=script_dir)
    except subprocess.CalledProcessError as e:
        print(f"Error while running the script: {e}")
        return None

    # Find the most recently created text file in the script's directory
    text_files = glob.glob(str(script_dir / "*.txt"))
    if not text_files:
        print("No text files found in the directory.")
        return None

    # Sort files by creation time (newest first)
    most_recent_file = max(text_files, key=os.path.getctime)
    
    # Load the contents of the file
    output_file = read_file_to_list(most_recent_file)

    return output_file

def test_dnc(target_file, debug=False):
    results = []
    # Testing output 1
    try:
        tested_output_file = run_script_with_output(target_file, INPUT1_PATH)
        example_output_file = read_file_to_list(OUTPUT1_PATH)
        are_equal, missing, extra, true_dist, test_dist = compare_lists(example_output_file, tested_output_file)
        if debug:
            print(are_equal)   
            print(missing)  
            print(extra)
        results.append([target_file, INPUT1_PATH, OUTPUT1_PATH, example_output_file, tested_output_file, are_equal, missing, extra, true_dist, test_dist])
    except:
        results.append([target_file, INPUT1_PATH, OUTPUT1_PATH, "Error", "Error", "Error", "Error", "Error", "Error", "Error"])

    # Testing output 2
    try:
        tested_output_file = run_script_with_output(target_file, INPUT2_PATH)
        example_output_file = read_file_to_list(OUTPUT2_PATH)
        are_equal, missing, extra, true_dist, test_dist = compare_lists(example_output_file, tested_output_file)
        if debug:
            print(are_equal)   
            print(missing)  
            print(extra)
        results.append([target_file, INPUT2_PATH, OUTPUT2_PATH, example_output_file, tested_output_file, are_equal, missing, extra, true_dist, test_dist])
    except:
        results.append([target_file, INPUT2_PATH, OUTPUT2_PATH, "Error", "Error", "Error", "Error", "Error", "Error", "Error"])

    # Testing output 3
    try:
        tested_output_file = run_script_with_output(target_file, INPUT3_PATH)
        example_output_file = read_file_to_list(OUTPUT3_PATH)
        are_equal, missing, extra, true_dist, test_dist = compare_lists(example_output_file, tested_output_file)
        if debug:
            print(are_equal)   
            print(missing)  
            print(extra)
        results.append([target_file, INPUT3_PATH, OUTPUT3_PATH, example_output_file, tested_output_file, are_equal, missing, extra, true_dist, test_dist])
    except:
        results.append([target_file, INPUT2_PATH, OUTPUT2_PATH, "Error", "Error", "Error", "Error", "Error", "Error", "Error"])
    # Testing output 4
    try:
        tested_output_file = run_script_with_output(target_file, INPUT4_PATH)
        example_output_file = read_file_to_list(OUTPUT4_PATH)
        are_equal, missing, extra, true_dist, test_dist = compare_lists(example_output_file, tested_output_file)
        if debug:
            print(are_equal)   
            print(missing)  
            print(extra)
        results.append([target_file, INPUT4_PATH, OUTPUT4_PATH, example_output_file, tested_output_file, are_equal, missing, extra, true_dist, test_dist])
    except:
        results.append([target_file, INPUT2_PATH, OUTPUT2_PATH, "Error", "Error", "Error", "Error", "Error", "Error", "Error"])
    # Testing output 5
    try:
        tested_output_file = run_script_with_output(target_file, INPUT5_PATH)
        example_output_file = read_file_to_list(OUTPUT5_PATH)
        are_equal, missing, extra, true_dist, test_dist = compare_lists(example_output_file, tested_output_file)
        if debug:
            print(are_equal)   
            print(missing)  
            print(extra)
        results.append([target_file, INPUT5_PATH, OUTPUT5_PATH, example_output_file, tested_output_file, are_equal, missing, extra, true_dist, test_dist])
    except:
        results.append([target_file, INPUT2_PATH, OUTPUT2_PATH, "Error", "Error", "Error", "Error", "Error", "Error", "Error"])
    # Add results to the dataframe
    for result in results:
        RESULTS_DF.loc[len(RESULTS_DF)] = result

# Test to make sure native divide and conquer algorithm is faster than brute force
def test_brute_force_vs_naive():
    """
    Tests the speed of the brute force algorithm vs the naive divide and conquer approach.
    Returns:
        brute_force_is_faster (bool): True if brute force is faster, False otherwise.
        success (bool): True if the test runs without errors.
    """
    try:
        naive_is_faster = False
        start_time = time.time()
        run_script_with_output("brute_force.py", TIMED_TARGET_FILE)
        brute_force_time = time.time() - start_time

        start_time = time.time()
        run_script_with_output("divide_conquer.py", TIMED_TARGET_FILE)
        divide_conquer_time = time.time() - start_time

        if divide_conquer_time < brute_force_time:
            naive_is_faster = True

        return naive_is_faster, False, brute_force_time, divide_conquer_time
    except Exception as e:
        print(f"Error running brute force vs naive test: {e}")
        return False, True, 0, 0

def test_naive_vs_enhanced():
    """
    Tests the speed of the naive divide and conquer algorithm vs the enhanced divide and conquer algorithm.
    Returns:
        naive_divide_is_faster (bool): True if naive divide and conquer is faster, False otherwise.
        success (bool): True if the test runs without errors.
    """
    try:
        enhanced_divide_is_faster = False
        counter = 0
        min_time = np.inf

        # Measure naive divide & conquer time
        divide_conquer_time = 100000

        # Measure enhanced divide & conquer time
        while not min_time < divide_conquer_time:
            counter += 1
            start_time = time.time()
            run_script_with_output("divide_conquer.py", TIMED_TARGET_FILE)
            divide_conquer_time = time.time() - start_time

            start_time = time.time()
            run_script_with_output("enhanced_dnc.py", TIMED_TARGET_FILE)
            enhanced_dnc_time = time.time() - start_time

            if enhanced_dnc_time < min_time:
                min_time = enhanced_dnc_time

            if min_time < divide_conquer_time:
                enhanced_divide_is_faster = True
                break
            if counter > 3:
                break

        return enhanced_divide_is_faster, False, divide_conquer_time, min_time
    except Exception as e:
        print(f"Error running naive vs enhanced test: {e}")
        return False, True, 0, 0

# Run the test suite
test_dnc(target_file="brute_force.py")
test_dnc(target_file="divide_conquer.py")
test_dnc(target_file="enhanced_dnc.py", debug=True)
naive_is_faster, bf_error, bf_time, naive_time_1 = test_brute_force_vs_naive()
naive_divide_is_faster, naive_error, naive_time_2, enhanced_time = test_naive_vs_enhanced()
print(RESULTS_DF)

# Save the results to a text file
directory_name = os.path.basename(os.path.dirname(os.path.abspath(__file__)))
print('Writing results to file', f"{path_to_this_file}/{directory_name}-results.txt")

with open(f"{path_to_this_file}/{directory_name}-results.txt", "w") as f:
    f.write("###############################################################################\n")
    f.write(f"Results of the test suite for assignment 1 algorithms for {directory_name}\n")
    f.write("###############################################################################\n\n")
    if naive_error or (not naive_divide_is_faster):
        f.write("*Enhanced divide and conquer is NOT faster than divide and conquer\n")
        f.write(f"  Enhanced divide and conquer time: {enhanced_time}\n")
        f.write(f"  Naive divide and conquer time: {naive_time_2}\n")
    else:
        f.write("Enhanced divide and conquer is faster than divide and conquer\n")
        f.write(f"  Enhanced divide and conquer time: {enhanced_time}\n")
        f.write(f"  Naive divide and conquer time: {naive_time_2}\n")
    if bf_error or (not naive_is_faster):
        f.write("*Divide and conquer is NOT faster than brute force\n")
        f.write(f"  Naive divide and conquer time: {naive_time_1}\n")
        f.write(f"  Brute force time: {bf_time}\n")
    else:
        f.write("Divide and conquer is faster than brute force\n")
        f.write(f"  Naive divide and conquer time: {naive_time_1}\n")
        f.write(f"  Brute force time: {bf_time}\n")
    f.write(RESULTS_DF.to_markdown())

RESULTS_DF.to_csv(f"{path_to_this_file}/{directory_name}-results.csv", index=False)

print("Results written to file.")
