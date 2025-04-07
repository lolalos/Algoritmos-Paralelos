import matplotlib.pyplot as plt

threads = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
times = [83.01, 42.95, 29.48, 25.10, 27.37, 26.58, 26.21, 25.90, 27.14, 26.68]

# Calculate speedup
speedup = [times[0] / t for t in times]

# Calculate efficiency
efficiency = [s / t for s, t in zip(speedup, threads)]

# Create the first plot: Speedup vs. Number of Threads
plt.figure(figsize=(12, 6))
plt.subplot(1, 2, 1)  # Create a 1x2 grid, and this is the first subplot
plt.plot(threads, speedup, marker='o')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup')
plt.title('Speedup vs. Number of Threads (N=3000)')
plt.grid(True)

# Create the second plot: Efficiency vs. Number of Threads
plt.subplot(1, 2, 2)  # Create a 1x2 grid, and this is the second subplot
plt.plot(threads, efficiency, marker='o')
plt.xlabel('Number of Threads')
plt.ylabel('Efficiency')
plt.title('Efficiency vs. Number of Threads (N=3000)')
plt.grid(True)

plt.tight_layout()  # Adjust subplot parameters for a tight layout
plt.show()
