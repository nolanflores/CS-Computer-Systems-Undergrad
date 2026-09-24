import matplotlib.pyplot as plt
import numpy as np
import gurobipy as gp
from gurobipy import GRB

# Define the data points
points = [(1, 3), (2, 5), (3, 7), (5, 11), (7, 14), (8, 15), (10, 19)]

### Code for linear programming ###
model = gp.Model("minimax_regression")

# Variables: a, b unbounded; E >= 0
a = model.addVar(lb=-GRB.INFINITY, name="a")
b = model.addVar(lb=-GRB.INFINITY, name="b")
E = model.addVar(lb=0.0, name="E")

# Objective: minimize E
model.setObjective(E, GRB.MINIMIZE)

# Constraints: for each point, |a*xi + b - yi| <= E
for i, (xi, yi) in enumerate(points):
    model.addConstr( a * xi + b - E <= yi,  name=f"upper_{i}")
    model.addConstr(-a * xi - b - E <= -yi, name=f"lower_{i}")

model.optimize()
###################################

a_val = a.X
b_val = b.X
E_val = E.X

# display the results
print("Optimal a:", a_val)
print("Optimal b:", b_val)
print("Optimal t (max absolute deviation):", E_val)

# Plot the data points and the regression line
x_vals = [x for (x, y) in points]
y_vals = [y for (x, y) in points]
x_line = np.linspace(min(x_vals), max(x_vals), 200)

plt.figure()
plt.plot(x_vals, y_vals, 'ro', label="Data points")
plt.plot(x_line, a_val * x_line + b_val, 'b-', label=f"Regression line: y = {a_val:.4f}x + {b_val:.4f}")
plt.legend()
plt.title("Minimax Linear Regression")
plt.xlabel("x")
plt.ylabel("y")
plt.tight_layout()

# Save the plot
plt.savefig("regression_plot.png")
print("Plot saved as regression_plot.png")
plt.show()