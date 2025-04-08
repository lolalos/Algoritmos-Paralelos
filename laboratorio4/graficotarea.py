import matplotlib.pyplot as plt

# Datos
nro_hilos = [1, 2, 3, 4, 5, 6, 7, 8]
speedup = [0.99836, 1.9404, 2.8598, 3.7562, 3.7728, 3.7308, 3.7455, 3.7599]
eficiencia = [0.99836, 0.97018, 0.95327, 0.93906, 0.75457, 0.62179, 0.53507, 0.46999]

# Crear subplots
fig, axs = plt.subplots(1, 2, figsize=(14, 6))

# Gráfico de Speedup
axs[0].plot(nro_hilos, speedup, marker='o', color='orange', label='Speedup (Sp)')
axs[0].set_title('Speedup vs Número de Hilos')
axs[0].set_xlabel('Número de Hilos')
axs[0].set_ylabel('Speedup (Sp)')
axs[0].grid(True)
axs[0].legend()

# Gráfico de Eficiencia
axs[1].plot(nro_hilos, eficiencia, marker='o', color='green', label='Eficiencia (E)')
axs[1].set_title('Eficiencia vs Número de Hilos')
axs[1].set_xlabel('Número de Hilos')
axs[1].set_ylabel('Eficiencia (E)')
axs[1].grid(True)
axs[1].legend()

# Ajustar diseño
plt.tight_layout()
plt.show()
