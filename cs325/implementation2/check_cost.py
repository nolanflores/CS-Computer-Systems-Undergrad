#!/usr/bin/env python3
# check_cost.py

import os
import sys
import getopt

def gen_matrix(sizex, sizey):
    return [[0]*sizey for _ in range(sizex)]

class ScoreParam:
    def __init__(self, loss_matrix, x_indexdict, y_indexdict):
        self.loss_matrix = loss_matrix
        self.x_indexdict = x_indexdict
        self.y_indexdict = y_indexdict
        
    def loss_char(self, xc, yc):
        return self.loss_matrix[self.x_indexdict[xc]][self.y_indexdict[yc]]

def check_file(f_pth):
    if f_pth and not os.path.exists(f_pth):
        raise ValueError(f"{f_pth} not found")

def read_cost_matrix(fns=''):
    """
    Reads a cost matrix file in CSV format, where:
      - The first line has the y-symbols as columns (ignoring the first column).
      - Each subsequent line starts with an x-symbol, followed by integer costs.

    Returns:
      loss_matrix (list of lists),
      x_indexdict (dict),
      y_indexdict (dict)
    """
    check_file(fns)

    loss_matrix = []
    x_indexdict = {}
    y_indexdict = {}

    with open(fns, 'r') as f:
        line_idx = 0
        for line in f:
            parts = line.strip().split(',')
            if line_idx == 0:
                # The first row: column headers for Y
                ys = [y.strip() for y in parts[1:]]
            else:
                # Subsequent rows: x symbol + costs
                x = parts[0].strip()
                x_indexdict[x] = line_idx - 1

                row_costs = []
                for j, val in enumerate(parts[1:]):
                    y_indexdict[ys[j]] = j
                    row_costs.append(int(val.strip()))
                loss_matrix.append(row_costs)

            line_idx += 1

    return loss_matrix, x_indexdict, y_indexdict

def get_cost(ax, ay, loss_matrix, x_indexdict, y_indexdict):
    """
    Given two equal-length strings (ax, ay), compute the total cost
    by summing loss_matrix[x_i][y_i] for each character position i.
    """
    cost = 0
    for i, ai in enumerate(ax):
        cost += loss_matrix[x_indexdict[ai]][y_indexdict[ay[i]]]
    return cost

def check_cost(
    fni='', 
    loss_matrix=None, 
    x_indexdict=None, 
    y_indexdict=None, 
    fno='cost_check_results.txt',
    fni2=''
):
    """
    1) Checks the primary file (fni):
       - Ensures lines match the format "AX,AY: REPORTED_COST".
       - Confirms reported_cost == computed_cost (via the provided matrix).
       - Logs any mismatches.

    2) If a solution file (fni2) is provided:
       - We do NOT compute or validate the solution file’s alignment or cost.
       - We only parse the cost at the end of each line and compare it to the *primary* file’s reported cost.
       - If they differ, we mark it "Incorrect"; otherwise "Correct".

    A summary of mismatches is printed to the console, and full results
    are written to fno.
    """
    check_file(fni)
    if fni2:
        check_file(fni2)

    # Read lines from primary file
    with open(fni, 'r') as fi:
        primary_lines = fi.readlines()

    # If second solution file is provided, read its lines
    secondary_lines = []
    if fni2:
        with open(fni2, 'r') as fi2:
            secondary_lines = fi2.readlines()
        if len(secondary_lines) != len(primary_lines):
            raise ValueError(
                "The second solution file has a different number of lines than the primary file. "
                "Cannot compare them line by line."
            )

    # Counters
    primary_fail_count = 0  # Mismatch between computed cost and primary reported cost
    solution_mismatch_count = 0  # Mismatch between primary reported cost and second file's cost

    with open(fno, 'w') as fo:
        line_number = 1

        for idx, line in enumerate(primary_lines):
            line = line.strip()
            try:
                # Format: "AX,AY: REPORTED_COST"
                parts = line.split(':')
                if len(parts) != 2:
                    raise ValueError(f"Format error at line {line_number}: {line}")

                # Parse the cost reported in the primary file
                reported_cost_str = parts[1].strip()
                reported_cost_primary = float(reported_cost_str)

                # Parse alignment from the primary file
                alignment_part = parts[0].strip()  # "AX,AY"
                ax, ay = alignment_part.split(',')
                ax = ax.strip()
                ay = ay.strip()

                if len(ax) != len(ay):
                    raise ValueError(f"Invalid alignment at line {line_number}: {line}")

                # Compute cost from matrix for the primary alignment
                computed_cost = get_cost(ax, ay, loss_matrix, x_indexdict, y_indexdict)

                # Compare primary reported vs. computed
                if abs(reported_cost_primary - computed_cost) < 1e-9:
                    msg_primary = f"Line {line_number}: Primary cost check passed."
                else:
                    primary_fail_count += 1
                    msg_primary = (f"Line {line_number}: Primary mismatch. "
                                   f"Computed: {computed_cost}, Reported: {reported_cost_primary}")

                # If there's a solution file, compare costs only (no alignment check)
                if fni2:
                    line2 = secondary_lines[idx].strip()
                    # We assume the solution file is well-formed, so just parse the cost:
                    parts2 = line2.split(':')
                    if len(parts2) < 2:
                        raise ValueError(f"Solution file format error at line {line_number}: {line2}")

                    # The portion after the colon is the solution file's cost
                    reported_cost_solution = float(parts2[1].strip())

                    if abs(reported_cost_primary - reported_cost_solution) < 1e-9:
                        msg_secondary = "Solution check: Correct."
                    else:
                        solution_mismatch_count += 1
                        msg_secondary = (f"Solution check: Incorrect. "
                                         f"Primary cost: {reported_cost_primary}, "
                                         f"Solution cost: {reported_cost_solution}")

                    # Combine messages
                    fo.write(msg_primary + " | " + msg_secondary + "\n")
                else:
                    # Only primary check
                    fo.write(msg_primary + "\n")

            except ValueError as e:
                # Format or parse error => terminate immediately
                fo.write(f"Line {line_number}: Error: {str(e)}\n")
                print(f"Error: {str(e)}")
                return

            line_number += 1

    # Print summary if we didn't exit early
    print(f"Primary file cost-check failures: {primary_fail_count}")
    if fni2:
        print(f"Solution file mismatches (by cost only): {solution_mismatch_count}")

    print(f"Results written to: {fno}")

    return

def main(argv):
    print('_' * 100)

    # Default file paths
    costfile = 'imp2cost.txt'
    outputfile = 'imp2output.txt'  # The primary solution file
    second_outputfile = ''         # optional second solution file
    log_results = 'cost_check_results.txt'

    # Add parent dir to path if needed
    sys.path.append(os.path.join(os.path.dirname(__file__), '..'))
    
    try:
        opts, _ = getopt.getopt(argv, "hc:o:s:r:", ["cfile=", "ofile=", "sfile=", "rfile="])
    except getopt.GetoptError:
        print('Usage:')
        print('  check_cost.py -c <costfile> -o <primary_outputfile> [-s <second_outputfile>] [-r <results_logfile>]')
        sys.exit(2)

    for opt, arg in opts:
        if opt == '-h':
            print('Usage:')
            print('  check_cost.py -c <costfile> -o <primary_outputfile> [-s <second_outputfile>] [-r <results_logfile>]')
            sys.exit()
        elif opt in ("-c", "--cfile"):
            costfile = arg
        elif opt in ("-o", "--ofile"):
            outputfile = arg
        elif opt in ("-s", "--sfile"):
            second_outputfile = arg
        elif opt in ("-r", "--rfile"):
            log_results = arg
    
    # Read the cost matrix
    loss_matrix, x_indexdict, y_indexdict = read_cost_matrix(fns=costfile)

    # Perform checks
    check_cost(
        fni=outputfile,
        loss_matrix=loss_matrix,
        x_indexdict=x_indexdict,
        y_indexdict=y_indexdict,
        fno=log_results,
        fni2=second_outputfile
    )

if __name__ == "__main__":
    main(sys.argv[1:])
