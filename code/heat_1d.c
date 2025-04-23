// Simulación de la ecuación de difusión unidimensional en una barra de manera secuencial y por diferencias finitas

// Importar librerías necesarias
#include <stdio.h>
#include <stdlib.h>

// Definir constantes
#define N 100              // - Número de puntos en la barra
#define L 1.0              // - Longitud de la barra
#define T_TOTAL 50.0       // - Tiempo total de simulación
#define ALPHA 0.0001       // - Coeficiente de difusión térmica


// Definir la función principal
int main() {
    double dx = L / (N - 1);  // - Espacio entre los puntos de la barra
    double dt = 0.5;  // - Paso de tiempo
    int steps = (int) (T_TOTAL / dt);  // - Número de pasos en el tiempo

    // Establcer arreglos para almacenar temperaturas
    double* u = malloc(N * sizeof(double));    // - Temperatura actual
    double* u_new = malloc(N * sizeof(double));      // - Temperatura en el siguiente paso

    // Inicializar temperatura en 0°C
    for (int i = 0; i < N; i++) {
        u[i] = 0.0;
    }

    // Condición inicial: 100°C en el centro de la barra
    for (int i = N/2 - 2; i <= N/2 + 2; i++) {
        u[i] = 100.0;
    } 

    // Simular de la difusión de calor
    for (int n = 0; n < steps; n++) {

        // Establecer las condiciones de frontera fijas: extremos fijos en 0°C
        u_new[0] = 0.0;
        u_new[N - 1] = 0.0;

        // Calcular cada temperatura en el siguiente paso
        for (int i = 1; i < N - 1; i++) {
            u_new[i] = (ALPHA * (dt / (dx * dx)) * (u[i - 1] - 2 * u[i] + u[i + 1])) + u[i]; // calcular la temperatura con el método de diferencias finitas
        }

        // Actualizar los valores de temperatura en cada paso
        for (int i = 0; i < N; i++) {
            u[i] = u_new[i];
        }
    }

    // Mostrar la temperatura final y su respectiva posición
    printf("Distribución final de temperatura:\n");
    for (int i = 0; i < N; i++) {
        printf("x = %.2f, u = %.5f\n", i * dx, u[i]);
    }

    // Liberar memoria de las temperaturas
    free(u);
    free(u_new);

    // Finalizar la simulación
    return 0;
}