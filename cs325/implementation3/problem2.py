import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import gurobipy as gp
from gurobipy import GRB

# Load and prepare the data
data = pd.read_csv("Corvallis.csv", delimiter=";")

# We use the 'day' column (days since May 1, 1952) as d_i and the 'average' column as T_i.
d_values = data['day.1'].values
T_values = data['average'].values

# Define the periods for the two sinusoidal components.
P_season = 365.25              # period for the annual cycle
P_solar = 365.25 * 10.7        # period for the solar cycle

### Code for linear programming ###
model = gp.Model("temperature_fit")

# Variables: x0..x5 unbounded, E >= 0
x0 = model.addVar(lb=-GRB.INFINITY, name="x0")
x1 = model.addVar(lb=-GRB.INFINITY, name="x1")
x2 = model.addVar(lb=-GRB.INFINITY, name="x2")
x3 = model.addVar(lb=-GRB.INFINITY, name="x3")
x4 = model.addVar(lb=-GRB.INFINITY, name="x4")
x5 = model.addVar(lb=-GRB.INFINITY, name="x5")
E  = model.addVar(lb=0.0, name="E")

# Objective: minimize E
model.setObjective(E, GRB.MINIMIZE)

# Precompute trig values
cos_season = np.cos(2 * np.pi * d_values / P_season)
sin_season = np.sin(2 * np.pi * d_values / P_season)
cos_solar  = np.cos(2 * np.pi * d_values / P_solar)
sin_solar  = np.sin(2 * np.pi * d_values / P_solar)

# Constraints: |T(di) - Ti| <= E  for each data point
for i in range(len(d_values)):
    pred = (x0 + x1 * d_values[i]
            + x2 * cos_season[i] + x3 * sin_season[i]
            + x4 * cos_solar[i]  + x5 * sin_solar[i])
    model.addConstr( pred - E <= T_values[i],  name=f"upper_{i}")
    model.addConstr(-pred - E <= -T_values[i], name=f"lower_{i}")

model.optimize()
###################################

x0 = x0.X; x1 = x1.X; x2 = x2.X
x3 = x3.X; x4 = x4.X; x5 = x5.X; E = E.X

print("Optimal solution found:")
print(f"x0 = {x0}")
print(f"x1 = {x1}  (daily drift in °C)")
print(f"x2 = {x2}")
print(f"x3 = {x3}")
print(f"x4 = {x4}")
print(f"x5 = {x5}")
print(f"Minimum maximum absolute deviation (E) = {E}")
print(f"Estimated annual drift (x1 * 365.25) = {x1 * 365.25} °C/year")
print(f"Estimated drift per century (x1 * 365.25 * 100) = {x1 * 365.25 * 100:.4f} °C/century")
trend_direction = "warming" if x1 > 0 else "cooling"
print(f"This represents a {trend_direction} trend.")

# Plot the D and T values
plt.figure(figsize=(14, 6))
plt.plot(d_values, T_values, 'ro', markersize=2, alpha=0.5, label="Data points")
plt.xlabel("Day (since May 1, 1952)")
plt.ylabel("Temperature (°C)")

# Plot the fitted model
d_values_sorted = np.sort(d_values)
T_model_values = (x0 + x1 * d_values_sorted
                  + x2 * np.cos(2 * np.pi * d_values_sorted / P_season)
                  + x3 * np.sin(2 * np.pi * d_values_sorted / P_season)
                  + x4 * np.cos(2 * np.pi * d_values_sorted / P_solar)
                  + x5 * np.sin(2 * np.pi * d_values_sorted / P_solar))
plt.plot(d_values_sorted, T_model_values, 'b-', linewidth=1.5, label="Fitted model")

# Plot the linear trend
T_trend_values = x0 + x1 * d_values_sorted
plt.plot(d_values_sorted, T_trend_values, 'g-', linewidth=2, label=f"Linear trend (x1={x1:.6f} °C/day)")

plt.title("Temperature Fit with Seasonal and Solar Components (Corvallis, OR)")
plt.legend()
plt.tight_layout()
plt.savefig("temperature_fit.png", dpi=150)
print("Plot saved as 'temperature_fit.png'")
plt.show()