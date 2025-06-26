#include <stdio.h>
#include <stdlib.h>

// Función para calcular el agua atrapada
int calcularAgua(int* altura, int tamano) {
    if (tamano == 0) return 0;

    int maxIzquierda[tamano];
    int maxDerecha[tamano];
    int aguaTotal = 0;

    // Máximos hacia la izquierda
    maxIzquierda[0] = altura[0];
    for (int i = 1; i < tamano; i++) {
        maxIzquierda[i] = (altura[i] > maxIzquierda[i - 1]) ? altura[i] : maxIzquierda[i - 1];
    }

    // Máximos hacia la derecha
    maxDerecha[tamano - 1] = altura[tamano - 1];
    for (int i = tamano - 2; i >= 0; i--) {
        maxDerecha[i] = (altura[i] > maxDerecha[i + 1]) ? altura[i] : maxDerecha[i + 1];
    }

    // Cálculo de agua atrapada
    for (int i = 0; i < tamano; i++) {
        int aguaEnPosicion = (maxIzquierda[i] < maxDerecha[i] ? maxIzquierda[i] : maxDerecha[i]) - altura[i];
        if (aguaEnPosicion > 0)
            aguaTotal += aguaEnPosicion;
    }

    return aguaTotal;
}

int main() {
    int tamano;

    // Solicitar el tamaño del arreglo
    printf("Ingrese el numero de columnas de elevacion: ");
    scanf("%d", &tamano);

    if (tamano <= 0) {
        printf("El tamano debe ser mayor que 0.\n");
        return 1;
    }

    // Reservar memoria para el arreglo
    int* elevacion = (int*) malloc(tamano * sizeof(int));
    if (elevacion == NULL) {
        printf("No se pudo asignar memoria.\n");
        return 1;
    }

    // Ingresar valores de elevación
    printf("Ingrese las alturas (separadas por espacio):\n");
    for (int i = 0; i < tamano; i++) {
        scanf("%d", &elevacion[i]);
    }

    // Calcular y mostrar el resultado
    int resultado = calcularAgua(elevacion, tamano);
    printf("Cantidad de agua atrapada: %d\n", resultado);

    // Liberar memoria
    free(elevacion);
    return 0;
}

