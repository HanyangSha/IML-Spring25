import matplotlib.pyplot as plt
import numpy as np
import re
from scipy.optimize import curve_fit

# Read data from file
with open('iml_data.txt', 'r') as file:
    raw_data = file.read()

# Parsing the data
data = {}
for line in raw_data.split('\n'):
    match = re.match(r'n=(\d+), k=(\d+), percentage solvable = ([\d.]+)', line)
    if match:
        n, k, percentage = int(match[1]), int(match[2]), float(match[3])
        if n not in data:
            data[n] = []
        data[n].append((k, percentage))

# Sort data for proper plotting
for n in data:
    data[n].sort()

# Define sigmoid function
def sigmoid(x, a, b):
    return 1 / (1 + np.exp(-a * (x - b)))

# Plot percentage as a function of k for each n with sigmoid fit
plt.figure(figsize=(10, 6))
for n, values in data.items():
    k_values, percentages = zip(*values)
    k_values = np.array(k_values)
    percentages = np.array(percentages)
    
    # Fit sigmoid
    popt, _ = curve_fit(sigmoid, k_values, percentages, p0=[1, np.median(k_values)])
    a_fit, b_fit = popt
    
    # Compute R^2
    y_pred = sigmoid(k_values, *popt)
    ss_res = np.sum((percentages - y_pred) ** 2)
    ss_tot = np.sum((percentages - np.mean(percentages)) ** 2)
    r_squared = 1 - (ss_res / ss_tot)
    
    # Print values
    print(f'n={n}: a={a_fit:.4f}, b={b_fit:.4f}, R^2={r_squared:.4f}')
    
    # Plot data points and connect them with lines
    plt.plot(k_values, percentages, 'o-', label=f'n={n}', markersize=5)
    
    # Plot fitted sigmoid curve
    x_smooth = np.linspace(min(k_values), max(k_values), 100)
    y_smooth = sigmoid(x_smooth, *popt)
    plt.plot(x_smooth, y_smooth, '--', label=f'Fit n={n} (R²={r_squared:.3f})')


plt.xlabel('k')
plt.ylabel('Percentage Solvable')
plt.title('Percentage Solvable vs k for Different n with Sigmoid Fit')
plt.legend()
plt.grid()
plt.show()
