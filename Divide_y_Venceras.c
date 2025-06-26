#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MIN_SIZE 2

void llenarMatriz(int **matriz, int n) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            matriz[i][j] = rand() % 10;
}

void imprimirMatriz(int **matriz, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            printf("%d ", matriz[i][j]);
        printf("\n");
    }
}

int **crearMatriz(int n) {
    int **matriz = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++)
        matriz[i] = (int *)malloc(n * sizeof(int));
    return matriz;
}

void liberarMatriz(int **matriz, int n) {
    for(int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
}

void multiplicacionTradicional(int **A, int **B, int **C, int n) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            C[i][j] = 0;
            for(int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// Divide and Conquer (sin optimizar)
void sumarMatrices(int **A, int **B, int **C, int n) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void restarMatrices(int **A, int **B, int **C, int n) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void multiplicacionDaC(int **A, int **B, int **C, int n) {
    if(n <= MIN_SIZE) {
        multiplicacionTradicional(A, B, C, n);
        return;
    }

    int newSize = n / 2;
    int **A11 = crearMatriz(newSize), **A12 = crearMatriz(newSize);
    int **A21 = crearMatriz(newSize), **A22 = crearMatriz(newSize);
    int **B11 = crearMatriz(newSize), **B12 = crearMatriz(newSize);
    int **B21 = crearMatriz(newSize), **B22 = crearMatriz(newSize);
    int **C11 = crearMatriz(newSize), **C12 = crearMatriz(newSize);
    int **C21 = crearMatriz(newSize), **C22 = crearMatriz(newSize);
    int **M1 = crearMatriz(newSize), **M2 = crearMatriz(newSize);

    for(int i = 0; i < newSize; i++) {
        for(int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+newSize];
            A21[i][j] = A[i+newSize][j];
            A22[i][j] = A[i+newSize][j+newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+newSize];
            B21[i][j] = B[i+newSize][j];
            B22[i][j] = B[i+newSize][j+newSize];
        }
    }

    // C11 = A11*B11 + A12*B21
    multiplicacionDaC(A11, B11, M1, newSize);
    multiplicacionDaC(A12, B21, M2, newSize);
    sumarMatrices(M1, M2, C11, newSize);

    // C12 = A11*B12 + A12*B22
    multiplicacionDaC(A11, B12, M1, newSize);
    multiplicacionDaC(A12, B22, M2, newSize);
    sumarMatrices(M1, M2, C12, newSize);

    // C21 = A21*B11 + A22*B21
    multiplicacionDaC(A21, B11, M1, newSize);
    multiplicacionDaC(A22, B21, M2, newSize);
    sumarMatrices(M1, M2, C21, newSize);

    // C22 = A21*B12 + A22*B22
    multiplicacionDaC(A21, B12, M1, newSize);
    multiplicacionDaC(A22, B22, M2, newSize);
    sumarMatrices(M1, M2, C22, newSize);

    for(int i = 0; i < newSize; i++) {
        for(int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j+newSize] = C12[i][j];
            C[i+newSize][j] = C21[i][j];
            C[i+newSize][j+newSize] = C22[i][j];
        }
    }

    liberarMatriz(A11, newSize); liberarMatriz(A12, newSize);
    liberarMatriz(A21, newSize); liberarMatriz(A22, newSize);
    liberarMatriz(B11, newSize); liberarMatriz(B12, newSize);
    liberarMatriz(B21, newSize); liberarMatriz(B22, newSize);
    liberarMatriz(C11, newSize); liberarMatriz(C12, newSize);
    liberarMatriz(C21, newSize); liberarMatriz(C22, newSize);
    liberarMatriz(M1, newSize);  liberarMatriz(M2, newSize);
}

// Strassen
void multiplicacionStrassen(int **A, int **B, int **C, int n) {
    if(n <= MIN_SIZE) {
        multiplicacionTradicional(A, B, C, n);
        return;
    }

    int newSize = n/2;
    int **A11 = crearMatriz(newSize), **A12 = crearMatriz(newSize);
    int **A21 = crearMatriz(newSize), **A22 = crearMatriz(newSize);
    int **B11 = crearMatriz(newSize), **B12 = crearMatriz(newSize);
    int **B21 = crearMatriz(newSize), **B22 = crearMatriz(newSize);
    int **P1 = crearMatriz(newSize), **P2 = crearMatriz(newSize);
    int **P3 = crearMatriz(newSize), **P4 = crearMatriz(newSize);
    int **P5 = crearMatriz(newSize), **P6 = crearMatriz(newSize);
    int **P7 = crearMatriz(newSize);
    int **tempA = crearMatriz(newSize), **tempB = crearMatriz(newSize);

    for(int i = 0; i < newSize; i++)
        for(int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+newSize];
            A21[i][j] = A[i+newSize][j];
            A22[i][j] = A[i+newSize][j+newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+newSize];
            B21[i][j] = B[i+newSize][j];
            B22[i][j] = B[i+newSize][j+newSize];
        }

    // P1 = (A11 + A22)(B11 + B22)
    sumarMatrices(A11, A22, tempA, newSize);
    sumarMatrices(B11, B22, tempB, newSize);
    multiplicacionStrassen(tempA, tempB, P1, newSize);

    // P2 = (A21 + A22)B11
    sumarMatrices(A21, A22, tempA, newSize);
    multiplicacionStrassen(tempA, B11, P2, newSize);

    // P3 = A11(B12 - B22)
    restarMatrices(B12, B22, tempB, newSize);
    multiplicacionStrassen(A11, tempB, P3, newSize);

    // P4 = A22(B21 - B11)
    restarMatrices(B21, B11, tempB, newSize);
    multiplicacionStrassen(A22, tempB, P4, newSize);

    // P5 = (A11 + A12)B22
    sumarMatrices(A11, A12, tempA, newSize);
    multiplicacionStrassen(tempA, B22, P5, newSize);

    // P6 = (A21 - A11)(B11 + B12)
    restarMatrices(A21, A11, tempA, newSize);
    sumarMatrices(B11, B12, tempB, newSize);
    multiplicacionStrassen(tempA, tempB, P6, newSize);

    // P7 = (A12 - A22)(B21 + B22)
    restarMatrices(A12, A22, tempA, newSize);
    sumarMatrices(B21, B22, tempB, newSize);
    multiplicacionStrassen(tempA, tempB, P7, newSize);

    int **C11 = crearMatriz(newSize), **C12 = crearMatriz(newSize);
    int **C21 = crearMatriz(newSize), **C22 = crearMatriz(newSize);

    sumarMatrices(P1, P4, tempA, newSize);
    restarMatrices(tempA, P5, tempB, newSize);
    sumarMatrices(tempB, P7, C11, newSize);

    sumarMatrices(P3, P5, C12, newSize);
    sumarMatrices(P2, P4, C21, newSize);

    sumarMatrices(P1, P3, tempA, newSize);
    restarMatrices(tempA, P2, tempB, newSize);
    sumarMatrices(tempB, P6, C22, newSize);

    for(int i = 0; i < newSize; i++)
        for(int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j+newSize] = C12[i][j];
            C[i+newSize][j] = C21[i][j];
            C[i+newSize][j+newSize] = C22[i][j];
        }

    liberarMatriz(A11, newSize); liberarMatriz(A12, newSize);
    liberarMatriz(A21, newSize); liberarMatriz(A22, newSize);
    liberarMatriz(B11, newSize); liberarMatriz(B12, newSize);
    liberarMatriz(B21, newSize); liberarMatriz(B22, newSize);
    liberarMatriz(P1, newSize); liberarMatriz(P2, newSize);
    liberarMatriz(P3, newSize); liberarMatriz(P4, newSize);
    liberarMatriz(P5, newSize); liberarMatriz(P6, newSize);
    liberarMatriz(P7, newSize);
    liberarMatriz(tempA, newSize); liberarMatriz(tempB, newSize);
    liberarMatriz(C11, newSize); liberarMatriz(C12, newSize);
    liberarMatriz(C21, newSize); liberarMatriz(C22, newSize);
}

int main() {
    int opcion, n;
    printf("Ingrese el tamaño n (potencia de 2): ");
    scanf("%d", &n);

    int **A = crearMatriz(n), **B = crearMatriz(n), **C = crearMatriz(n);
    llenarMatriz(A, n);
    llenarMatriz(B, n);

    clock_t inicio, fin;
    double tiempo;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Multiplicacion Tradicional\n");
        printf("2. Multiplicacion Divide and Conquer\n");
        printf("3. Multiplicacion Strassen\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                inicio = clock();
                multiplicacionTradicional(A, B, C, n);
                fin = clock();
                tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
                printf("Tiempo tradicional: %.6f segundos\n", tiempo);
                break;
            case 2:
                inicio = clock();
                multiplicacionDaC(A, B, C, n);
                fin = clock();
                tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
                printf("Tiempo DaC: %.6f segundos\n", tiempo);
                break;
            case 3:
                inicio = clock();
                multiplicacionStrassen(A, B, C, n);
                fin = clock();
                tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
                printf("Tiempo Strassen: %.6f segundos\n", tiempo);
                break;
            case 0:
                break;
            default:
                printf("Opcion invalida\n");
        }

    } while(opcion != 0);

    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}

