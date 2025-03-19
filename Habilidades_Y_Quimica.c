#include <stdio.h>
#include <stdlib.h>

// Función de comparación para ordenar en orden ascendente
int comparar(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Función principal para dividir los jugadores en equipos de 2
int dividirJugadores(int *habilidad, int n) {
    qsort(habilidad, n, sizeof(int), comparar);     // Ordenamos la lista de habilidades

    // Calculamos la suma de las habilidades para que este balanceada 
    int sumaObjetivo = habilidad[0] + habilidad[n - 1];
    int quimicaTotal = 0;
    
	//Se van formando los equipos 
    int i;
    for (i = 0; i < n / 2; i++) {
        if (habilidad[i] + habilidad[n - 1 - i] != sumaObjetivo) {
            return -1; // No es posible formar equipos balanceados
        }
        quimicaTotal += habilidad[i] * habilidad[n - 1 - i];
    }

    return quimicaTotal;
}

// Funcion principal 
int main() {
    int habilidades1[] = {3, 2, 5, 1, 3, 4};
    int habilidades2[] = {3, 4};
    int habilidades3[] = {1, 1, 2, 3};
    int habilidades4[] = {2, 3, 6, 5, 4, 7};  
    int habilidades5[] = {5, 6, 2, 8, 9, 10}; 

    int n1 = sizeof(habilidades1) / sizeof(habilidades1[0]);
    int n2 = sizeof(habilidades2) / sizeof(habilidades2[0]);
    int n3 = sizeof(habilidades3) / sizeof(habilidades3[0]);
    int n4 = sizeof(habilidades4) / sizeof(habilidades4[0]);
    int n5 = sizeof(habilidades5) / sizeof(habilidades5[0]);

    printf("Resultado 1: %d\n", dividirJugadores(habilidades1, n1)); 
    printf("Resultado 2: %d\n", dividirJugadores(habilidades2, n2)); 
    printf("Resultado 3: %d\n", dividirJugadores(habilidades3, n3)); 
    printf("Resultado 4: %d\n", dividirJugadores(habilidades4, n4)); 
    printf("Resultado 5: %d\n", dividirJugadores(habilidades5, n5)); 

    return 0;
}
