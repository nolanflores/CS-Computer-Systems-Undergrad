#!/usr/bin/env python3
# plot_runtime.py

import math
import matplotlib.pyplot as plt

lengths   = [500, 1000, 2000, 4000, 5000]
avg_times = [0.1139, 0.4762, 2.1145, 8.7031, 13.9582]

# ── Compute slope via linear regression on log-log data ───────────────────────
log_x = [math.log(l) for l in lengths]
log_y = [math.log(t) for t in avg_times]

n = len(log_x)
sum_x  = sum(log_x)
sum_y  = sum(log_y)
sum_xx = sum(x*x for x in log_x)
sum_xy = sum(log_x[i]*log_y[i] for i in range(n))

slope     = (n*sum_xy - sum_x*sum_y) / (n*sum_xx - sum_x**2)
intercept = (sum_y - slope*sum_x) / n

print(f"Empirical exponent (slope): {slope:.4f}")

# ── Plot ──────────────────────────────────────────────────────────────────────
fig, ax = plt.subplots(figsize=(7, 5))

ax.scatter(lengths, avg_times, color='steelblue', zorder=5, label='Measured avg time')
ax.plot(lengths, avg_times, color='steelblue', linewidth=1.2)

fit_y = [math.exp(intercept) * (l ** slope) for l in lengths]
ax.plot(lengths, fit_y, color='tomato', linestyle='--',
        label=f'Fitted line (slope={slope:.2f})')

ax.set_xscale('log')
ax.set_yscale('log')
ax.set_xlabel('Sequence length (n)', fontsize=12)
ax.set_ylabel('Average alignment time (s)', fontsize=12)
ax.set_title('Sequence Alignment Runtime (log-log scale)', fontsize=13)
ax.legend()
ax.grid(True, which='both', linestyle='--', alpha=0.5)

plt.tight_layout()
plt.savefig('runtime_plot.png', dpi=150)
print("Plot saved to runtime_plot.png")