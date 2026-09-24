import sys
from itertools import combinations
import math
from a1_utils import read_input_from_cli, distance, write_output_to_file

def brute_force_closest_pair(points: list[tuple[float, float]]) -> tuple[float, list[tuple[tuple[float, float], tuple[float, float]]]]:
    """
    Find the closest pair of points using brute force.
    
    Args:
        points (list[tuple[float, float]]): A list of 2D points, where each point is represented 
                                            as a tuple of coordinates (x, y).
                                            
    Returns:
        tuple[float, list[tuple[tuple[float, float], tuple[float, float]]]]:
            - The updated minimum distance (float) between the closest pair(s) of points.
            - A list of tuples representing the closest point pairs, where each pair is a 
              tuple of two points ((x1, y1), (x2, y2)).
    """

    min_dist = float('inf')
    closest_pairs = []
    
    #TODO 

    return min_dist, closest_pairs

if __name__ == "__main__":
    try:
        points = read_input_from_cli()
        min_dist, closest_pairs = brute_force_closest_pair(points)

        print(f"Minimum Distance: {min_dist}")
        print("Closest Pairs:")
        for pair in closest_pairs:
            print(pair)
        write_output_to_file(distance=min_dist, points=closest_pairs, output_file= 'brute_force_output.txt')
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)
