#include <thread>
#include <iostream>

// Implementación de hilos 
void func()
{
    // Función de ejecución de hilo 
    std::cout << "Hola desde el hilo!" << std::endl;
}

int main ()
{
    // Crea y ejecuta la función en un hilo 
    std::thread hilo0(func);
    hilo0.join(); // Espera a que el hilo termine
    return 0;
}