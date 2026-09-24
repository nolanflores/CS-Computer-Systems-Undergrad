# Nolan Flores
# Oregon State University
# CS 325 - Analysis of Algorithms
# Implementation Assignment 2
# 2/19/2026

import sys

def read_cost_matrix(path):
    """Returns loss_matrix (2-D list), x_index, y_index dicts."""
    loss_matrix = []
    x_idx = {}
    y_idx = {}

    lines = []
    with open(path) as f:
        for ln in f:
            stripped = ln.strip()
            if stripped:
                lines.append(stripped)

    # First line: column headers (* , - , A , T , G , C)
    raw_headers = lines[0].split(',')
    headers = []
    for h in raw_headers:
        headers.append(h.strip())

    y_labels = headers[1:]
    for j in range(len(y_labels)):
        y_idx[y_labels[j]] = j

    # Remaining lines (row symbol, costs...)
    for row_i in range(1, len(lines)):
        raw_parts = lines[row_i].split(',')
        parts = []
        for p in raw_parts:
            parts.append(p.strip())

        row_sym = parts[0]
        x_idx[row_sym] = row_i - 1

        row_costs = []
        for v in parts[1:]:
            row_costs.append(int(v))
        loss_matrix.append(row_costs)

    return loss_matrix, x_idx, y_idx



def align(s1, s2, loss_matrix, x_idx, y_idx):
    m = len(s1)
    n = len(s2)
    gap = '-'

    def cost(a, b):
        return loss_matrix[x_idx[a]][y_idx[b]]

    # dp[i][j] = min cost to align s1[:i] with s2[:j]
    dp = []
    for i in range(m + 1):
        row = []
        for j in range(n + 1):
            row.append(0)
        dp.append(row)

    # Base cases (align each prefix against all gaps)
    for i in range(1, m + 1):
        dp[i][0] = dp[i-1][0] + cost(s1[i-1], gap)
    for j in range(1, n + 1):
        dp[0][j] = dp[0][j-1] + cost(gap, s2[j-1])

    # Fill table
    for i in range(1, m + 1):
        c1 = s1[i-1]
        for j in range(1, n + 1):
            c2 = s2[j-1]
            match  = dp[i-1][j-1] + cost(c1, c2)
            delete = dp[i-1][j]   + cost(c1, gap)
            insert = dp[i][j-1]   + cost(gap, c2)
            dp[i][j] = min(match, delete, insert)

    total_cost = dp[m][n]

    # Backtrack to find the aligned strings
    a1 = []
    a2 = []
    i = m
    j = n
    while i > 0 or j > 0:
        c1 = s1[i-1] if i > 0 else gap
        c2 = s2[j-1] if j > 0 else gap
        if i > 0 and j > 0 and dp[i][j] == dp[i-1][j-1] + cost(c1, c2):
            a1.append(c1)
            a2.append(c2)
            i -= 1
            j -= 1
        elif i > 0 and dp[i][j] == dp[i-1][j] + cost(c1, gap):
            a1.append(c1)
            a2.append(gap)
            i -= 1
        else:
            a1.append(gap)
            a2.append(c2)
            j -= 1

    a1.reverse()
    a2.reverse()
    aligned_s1 = ''.join(a1)
    aligned_s2 = ''.join(a2)
    return aligned_s1, aligned_s2, total_cost


def main():
    loss_matrix, x_idx, y_idx = read_cost_matrix('imp2cost.txt')

    pairs = []
    with open('imp2input.txt') as f:
        for ln in f:
            stripped = ln.strip()
            if stripped:
                pairs.append(stripped)

    results = []
    for pair in pairs:
        s1, s2 = pair.split(',')
        s1 = s1.strip()
        s2 = s2.strip()
        a1, a2, total_cost = align(s1, s2, loss_matrix, x_idx, y_idx)
        results.append(f"{a1},{a2}:{total_cost}")

    with open('imp2output.txt', 'w') as f:
        for line in results:
            f.write(line + '\n')


if __name__ == '__main__':
    main()