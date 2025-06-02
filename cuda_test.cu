#include <stdio.h>

__global__ void testKernel() {
    printf("¡Hola desde la GPU!\n");
}

int main() {
    printf("Ejecutando prueba de CUDA...\n");
    testKernel<<<1, 1>>>();
    cudaDeviceSynchronize();
    
    // Verificar dispositivos CUDA
    int deviceCount = 0;
    cudaGetDeviceCount(&deviceCount);
    printf("Número de dispositivos CUDA: %d\n", deviceCount);
    
    if (deviceCount > 0) {
        for (int i = 0; i < deviceCount; i++) {
            cudaDeviceProp deviceProp;
            cudaGetDeviceProperties(&deviceProp, i);
            printf("Dispositivo %d: %s\n", i, deviceProp.name);
            printf("  Capacidad de cómputo: %d.%d\n", deviceProp.major, deviceProp.minor);
            printf("  Memoria global: %.2f GB\n", 
                    (float)deviceProp.totalGlobalMem / (1024.0f * 1024.0f * 1024.0f));
        }
        printf("¡CUDA está instalado correctamente!\n");
    } else {
        printf("¡No se encontraron dispositivos CUDA!\n");
    }
    
    return 0;
}