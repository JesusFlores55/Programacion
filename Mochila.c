#include <stdio.h>
#include <string.h>

#define NUM_ITEMS 4
#define MAX_WEIGHT 4

typedef struct {
    char nombre[10];
    char simbolo;
    int peso;
    int valor;
} Articulo;

int main() {
    Articulo articulos[NUM_ITEMS] = {
        {"Guitarra", 'G', 1, 1500},
        {"Estereo",  'E', 4, 3000},
        {"Laptop",   'L', 3, 2000},
        {"iPhone",   'I', 1, 2000}
    };

    int matriz[NUM_ITEMS + 1][MAX_WEIGHT + 1];
    char simbolos[NUM_ITEMS + 1][MAX_WEIGHT + 1];

    // Inicializar matrices
    for (int i = 0; i <= NUM_ITEMS; i++) {
        for (int w = 0; w <= MAX_WEIGHT; w++) {
            matriz[i][w] = 0;
            simbolos[i][w] = ' ';
        }
    }

    // Programación dinámica
    for (int i = 1; i <= NUM_ITEMS; i++) {
        for (int w = 1; w <= MAX_WEIGHT; w++) {
            if (articulos[i - 1].peso <= w) {
                int incluir = articulos[i - 1].valor + matriz[i - 1][w - articulos[i - 1].peso];
                int excluir = matriz[i - 1][w];
                if (incluir > excluir) {
                    matriz[i][w] = incluir;
                    simbolos[i][w] = articulos[i - 1].simbolo;
                } else {
                    matriz[i][w] = excluir;
                    simbolos[i][w] = simbolos[i - 1][w];
                }
            } else {
                matriz[i][w] = matriz[i - 1][w];
                simbolos[i][w] = simbolos[i - 1][w];
            }
        }
    }

    // Imprimir tabla 
    printf("\nTabla de valores y simbolos:\n\n");

    printf("%-10s", "");
    for (int w = 1; w <= MAX_WEIGHT; w++) {
        printf(" W%-6d", w);
    }
    printf("\n");

    for (int i = 1; i <= NUM_ITEMS; i++) {
        printf("%-10s", articulos[i - 1].nombre);
        for (int w = 1; w <= MAX_WEIGHT; w++) {
            printf(" $%-4d%c ", matriz[i][w], simbolos[i][w]);
        }
        printf("\n");
    }

    // Mostrar resultado final
    printf("\nValor maximo que se puede llevar: $%d\n", matriz[NUM_ITEMS][MAX_WEIGHT]);

    // Mostrar artículos seleccionados
    printf("Articulos seleccionados:\n");
    int w = MAX_WEIGHT;
    for (int i = NUM_ITEMS; i > 0 && w > 0; i--) {
        if (matriz[i][w] != matriz[i - 1][w]) {
            printf(" - %s\n", articulos[i - 1].nombre);
            w -= articulos[i - 1].peso;
        }
    }

    return 0;
}


