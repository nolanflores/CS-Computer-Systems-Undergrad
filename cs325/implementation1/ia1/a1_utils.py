import sys
import math
import random
from typing import List

def distance(p1, p2):
    """Calculate the Euclidean distance between two points."""
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)


def generate_random_input_file(
    n: int,
    output_file: str = 'input.txt',
    seed: int = 42,
    ):
    """
    This function generates a random input file with n unique points.

    Args:
    n: int - The number of points to generate
    output_file: str - The output file to write to
    seed: int - The random seed for reproducibility
    Returns:
    None
    """
    random.seed(seed)
    x_values = random.sample(range(1, n*10), n)  # Ensures distinct x values
    y_values = random.sample(range(1, n*10), n)  # Ensures distinct y values
    points = list(zip(x_values, y_values))
    with open(output_file, 'w') as f:
        for point in points:
            f.write(f"{point[0]} {point[1]}\n")
    

def read_input_from_cli():
    """
    This function reads the input file from the command line and returns the data as a list of lists

    Args:
    None

    Returns:
    List[list] - The list of lists of the input file
    """
    if len(sys.argv) < 2:
        print("Usage: python3 main.py <input_file>")
        sys.exit(1)

    input_file = sys.argv[1]
    data = read_file_to_list(input_file)
    return data

def read_file_to_list(input_file: str) -> List[tuple]:
    """
    This function reads the input file and returns a list of lists

    Args:
    input_file: str - The input file to read

    Returns:
    List[tuple] - The list of tuples of the input file
    """
    data = []
    with open(input_file, 'r') as f:
        for line in f:
            # Split line by whitespace and convert each to float
            numbers = line.strip().split()
            # Read each number as a float
            row = tuple(float(x) for x in numbers)
            data.append(row)
    return data

def sort_pairs(pairs: List[Tuple[Tuple[float, float], Tuple[float, float]]]) -> List[Tuple[Tuple[float, float], Tuple[float, float]]]:
    """
    This function sorts the list of pairs of points by the x-coordinate of the first point in each pair,
    then by the y-coordinate of the first point in each pair
    """
    pairs.sort(key=lambda pair: (pair[0][0], pair[0][1], pair[1][0], pair[1][1]))
    
    return pairs

def write_output_to_file(distance: float, points: List[tuple], output_file: str='output.txt'):
    """
    This function writes the output array to a file called output.txt

    Args:
    distance: float - The minimum distance between two points
    points: List[tuple | list] - The list of tuples of points

    Returns:
    None

    Example:
    distance = 1.0
    points = [([1.0, 7.0], [1.0, 8.0]), ([9.0, 5.0], [9.0, 6.0]), ([9.0, 6.0], [9.0, 7.0]), ([9.0, 7.0], [9.0, 8.0])]
    write_output_to_file(distance, points)

    Output:
    1.0
    1 7 1 8
    9 5 9 6
    9 6 9 7
    9 7 9 8
    """
    with open(output_file, 'w') as f:
        # Write the distance
        f.write(str(distance) + '\n')
        # Write the tuple of tuples
        for point in points:
            f.write(f"{point[0][0]:.0f} {point[0][1]:.0f} {point[1][0]:.0f} {point[1][1]:.0f} \n")
