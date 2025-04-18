// Simulación de la ecuación de difusión unidimensional en una barra de manera secuencial y por diferencias finitas
// Importar librerías necesarias

#include <stdio.h>
#include <stdlib.h>

// Definición de constantes
#define N 100              // Número de puntos en la barra
#define L 1.0              // Longitud de la barra
#define T_TOTAL 10.0       // Tiempo total de simulación
#define ALPHA 0.0001       // Coeficiente de difusión térmica


// Función principal
int main() {
    double dx = L / (N - 1);  // Espaciado entre puntos
    double dt = (dx * dx) / (2 * ALPHA);  // Paso de tiempo(Condición de estabilidad)
    int steps = (int)(T_TOTAL / dt);  // Número de pasos en el tiempo

    double u[N];           // Temperatura actual
    double u_new[N];       // Temperatura siguiente

    // 1. Inicializar temperatura a 0
    for (int i = 0; i < N; i++) {
        u[i] = 0.0;
    }
    u[N/2] = 100.0; // Punto caliente en el centro de la barra

    // 2. Bucle principal de simulación
    for (int n = 0; n < steps; n++) {
        // Condiciones de frontera fijas
        u_new[0] = 0.0;
        u_new[N-1] = 0.0;

        // Calcular nuevas temperaturas para cada punto interior
        for (int i = 1; i < N - 1; i++) {
            u_new[i] = u[i] + ALPHA * dt / (dx * dx) * (u[i+1] - 2*u[i] + u[i-1]);
        }

        // Actualizar los valores actuales
        for (int i = 0; i < N; i++) {
            u[i] = u_new[i];
        }

        // Imprimir temperatura en el central en cada paso
        printf("t = %.4f, u_centro = %.2f\n", n * dt, u[N/2]);
    }

    // Mostrar la temperatura final
    printf("Distribución final de temperatura:\n");
    for (int i = 0; i < N; i++) {
        printf("x = %.2f\n, u = %.2f\n", i * dx, u[i]);
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>

int main() {
    // Parámetros del problema
    int N = 100;                   // Número de puntos en el espacio
    double L = 1.0;                // Longitud de la barra (metros)
    double dx = L / (N - 1);       // Espaciado en la malla
    double alpha = 0.0001;         // Coeficiente de difusión térmica

    double dt = 0.4 * dx * dx / alpha;  // Paso de tiempo (condición de estabilidad CFL)
    double T = 10.0;              // Tiempo total de simulación (segundos)
    int steps = T / dt;          // Número total de pasos de tiempo

    // Arreglos de temperatura
    double* current = malloc(N * sizeof(double));
    double* next = malloc(N * sizeof(double));

    // Inicialización: toda la barra a 0°C
    for (int i = 0; i < N; i++) {
        current[i] = 0.0;
    }

    // Condición inicial: punto caliente en el centro
    current[N / 2] = 100.0;

    // Condiciones de frontera: extremos fijos en 0°C
    current[0] = 0.0;
    current[N - 1] = 0.0;

    // Simulación temporal
    for (int n = 0; n < steps; n++) {
        // Aplicar diferencias finitas en los puntos internos
        for (int i = 1; i < N - 1; i++) {
            next[i] = current[i] + alpha * dt / (dx * dx) * 
                     (current[i - 1] - 2 * current[i] + current[i + 1]);
        }

        // Aplicar condiciones de frontera (de nuevo, por claridad)
        next[0] = 0.0;
        next[N - 1] = 0.0;

        // Actualizar el arreglo actual
        for (int i = 0; i < N; i++) {
            current[i] = next[i];
        }
    }

    // Imprimir resultados finales
    printf("Distribución final de temperatura:\n");
    for (int i = 0; i < N; i++) {
        printf("x = %.2f\tT = %.2f\n", i * dx, current[i]);
    }

    // Liberar memoria
    free(current);
    free(next);

    return 0;
}
