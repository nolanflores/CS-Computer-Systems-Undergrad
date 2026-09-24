import random
import time
from imp2align import read_cost_matrix, align

COST_FILE = 'imp2cost.txt'
ALPHABET  = ['A', 'G', 'T', 'C']
LENGTHS   = [500, 1000, 2000, 4000, 5000]
NUM_PAIRS = 10

def gen_sequence(length, rng):
    seq = []
    for _ in range(length):
        seq.append(rng.choice(ALPHABET))
    return ''.join(seq)

def main():
    rng = random.Random(time.time())
    loss_matrix, x_idx, y_idx = read_cost_matrix(COST_FILE)

    print(f"{'Length':>8}  {'Avg Time (s)':>14}  {'Min (s)':>10}  {'Max (s)':>10}")
    print('-' * 50)

    with open('emp_results.txt', 'w') as f:
        f.write('length,avg_time\n')
        for length in LENGTHS:
            times = []
            for _ in range(NUM_PAIRS):
                s1 = gen_sequence(length, rng)
                s2 = gen_sequence(length, rng)
                t0 = time.perf_counter()
                align(s1, s2, loss_matrix, x_idx, y_idx)
                t1 = time.perf_counter()
                times.append(t1 - t0)

            avg = sum(times) / len(times)
            print(f"{length:>8}  {avg:>14.4f}  {min(times):>10.4f}  {max(times):>10.4f}")
            f.write(f'{length},{avg}\n')

    print('\nResults saved to emp_results.txt')

if __name__ == '__main__':
    main()