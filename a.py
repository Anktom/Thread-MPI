import matplotlib.pyplot as plt

# Dados
num_processes_threads = [1, 2, 3, 4]

# Médias MPI
mpi_times = [0.156, 0.1778, 0.255, 0.2772]

# Médias Threads
thread_times = [0.040, 0.01334, 0.01212, 0.04512]

# Gráfico
plt.figure(figsize=(10, 6))

plt.plot(num_processes_threads, mpi_times, label='MPI', marker='o')
plt.plot(num_processes_threads, thread_times, label='Threads', marker='o')

plt.xlabel('Number of Processes/Threads')
plt.ylabel('Execution Time (s)')
plt.title('Execution Time vs Number of Processes/Threads')
plt.legend()
plt.grid(True)
plt.savefig('execution_time_comparison.png')
plt.show()
