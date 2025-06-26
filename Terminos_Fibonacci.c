//Flores Zavaleta Jesus Manuel
#include <stdio.h>
#include <stdlib.h>

// Función para verificar si un número es primo
int esPrimo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i*i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

// Función para generar la secuencia de Fibonacci hasta K, omitiendo posiciones primas
int generarFibonacciFiltrado(int fib[], int k) {
    int a = 0, b = 1, c, i = 1, idx = 0;
    while (a <= k) {
        if (!esPrimo(i)) {
            fib[idx++] = a;
        }
        c = a + b;
        a = b;
        b = c;
        i++;
    }
    return idx; // número de elementos en la secuencia filtrada
}

int main() {
	
    //Datos Reales: 6/5/2004 
    int dia = 6, mes = 5, anio = 2004;
    int K = dia * 100 + mes * 10 + (anio % 100); 
    printf("K calculado: %d\n", K);

    //Generar la secuencia de Fibonacci filtrada
    int fib[100]; // Tamaño suficiente
    int n = generarFibonacciFiltrado(fib, K);

    printf("Secuencia de Fibonacci filtrada:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    //Encontrar la combinación óptima (estrategia Greedy)
    int suma = 0, count = 0;
    printf("Terminos usados:\n");
    for (int i = n - 1; i >= 0 && K > 0; i--) {
        if (fib[i] <= K) {
            K -= fib[i];
            printf("%d ", fib[i]);
            count++;
        }
    }
    printf("\nCantidad minima de terminos: %d\n", count);

    return 0;
}

