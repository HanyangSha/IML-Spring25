import matplotlib.pyplot as plt
import numpy as np
import re
from scipy.optimize import curve_fit

# Read data from file
with open('error_bound_sampling.txt', 'r') as file:
    raw_data = file.read()

# Parsing the data
data = {}
for line in raw_data.split('\n'):
    match = re.match(r'n=(\d+),\s*k=(\d+),\s*percentage solvable\s*=\s*(\d+\.\d+),\s*variance\s*=\s*(\d+\.\d+),\s*error bound\s*=\s*(\d+\.\d+)', line)
    if match:
        n, k = int(match.group(1)), int(match.group(2))
        percentage, variance, error_bound = map(float, match.group(3, 4, 5))
        if n not in data:
            data[n] = []
        data[n].append((k, percentage, variance, error_bound))

# Sort data for proper plotting
for n in data:
    data[n].sort()

# Define sigmoid function
# def sigmoid(x, a, b):
#     return 1 / (1 + np.exp(-a * (x - b)))
def sigmoid(x, A, a, b):
    return A / (1 + np.exp(-a * (x - b)))

# Plot for each n
for n in [9, 10]:
    if n in data:
        k_values, percentages, variances, error_bounds = zip(*data[n])
        k_values = np.array(k_values)
        percentages = np.array(percentages)
        
        # Fit sigmoid function
        popt, _ = curve_fit(sigmoid, k_values, percentages, maxfev=5000)
        # A, a, b = popt
        # fitted_values = sigmoid(k_values, A, a, b)
        a, b = popt
        fitted_values = sigmoid(k_values, a, b)

        # Compute R^2 value
        residuals = percentages - fitted_values
        ss_res = np.sum(residuals**2)
        ss_tot = np.sum((percentages - np.mean(percentages))**2)
        r_squared = 1 - (ss_res / ss_tot)
        
        print(f'n={n}: a={a:.4f}, b={b:.4f}, R^2={r_squared:.4f}')

        plt.figure(figsize=(10, 6))
        plt.plot(k_values, percentages, marker='o', linestyle='-', label='Percentage Solvable')
        plt.plot(k_values, variances, marker='s', linestyle='--', label='Variance')
        plt.plot(k_values, error_bounds, marker='^', linestyle='-.', label='Error Bound')
        plt.plot(k_values, fitted_values, linestyle='dotted', label=f'Fitted Sigmoid (a={a:.2f}, b={b:.2f}, R²={r_squared:.4f})')
        
        plt.xlabel('k')
        plt.ylabel('Values')
        plt.title(f'Data for n={n}')
        plt.legend()
        plt.grid()
        plt.show()
