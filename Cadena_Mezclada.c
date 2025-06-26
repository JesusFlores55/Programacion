#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LONGITUD 30

// Tabla de memorización: -1 = no evaluado, 0 = falso, 1 = verdadero
int memo[MAX_LONGITUD][MAX_LONGITUD][MAX_LONGITUD + 1];

// Función recursiva para verificar si una subcadena puede ser mezclada
bool esMezclaRecursiva(char* cadena1, char* cadena2, int i1, int i2, int longitud) {
    if (memo[i1][i2][longitud] != -1)
        return memo[i1][i2][longitud];

    // Comparar substrings directamente
    if (strncmp(cadena1 + i1, cadena2 + i2, longitud) == 0)
        return memo[i1][i2][longitud] = 1;

    // Verificar que tengan las mismas letras
    int conteo[26] = {0};
    for (int i = 0; i < longitud; i++) {
        conteo[cadena1[i1 + i] - 'a']++;
        conteo[cadena2[i2 + i] - 'a']--;
    }
    for (int i = 0; i < 26; i++) {
        if (conteo[i] != 0)
            return memo[i1][i2][longitud] = 0;
    }

    // Probar todas las particiones posibles
    for (int i = 1; i < longitud; i++) {
        // Sin intercambio
        if (esMezclaRecursiva(cadena1, cadena2, i1, i2, i) &&
            esMezclaRecursiva(cadena1, cadena2, i1 + i, i2 + i, longitud - i)) {
            return memo[i1][i2][longitud] = 1;
        }
        // Con intercambio
        if (esMezclaRecursiva(cadena1, cadena2, i1, i2 + longitud - i, i) &&
            esMezclaRecursiva(cadena1, cadena2, i1 + i, i2, longitud - i)) {
            return memo[i1][i2][longitud] = 1;
        }
    }

    return memo[i1][i2][longitud] = 0;
}

// Función principal que se llama desde el main
bool esCadenaMezclada(char* cadena1, char* cadena2) {
    int longitud = strlen(cadena1);
    if (longitud != strlen(cadena2))
        return false;

    // Inicializar memorización
    for (int i = 0; i < MAX_LONGITUD; i++)
        for (int j = 0; j < MAX_LONGITUD; j++)
            for (int k = 0; k <= MAX_LONGITUD; k++)
                memo[i][j][k] = -1;

    return esMezclaRecursiva(cadena1, cadena2, 0, 0, longitud);
}

int main() {
    char cadena1[31], cadena2[31];

    printf("Ingresa la primera cadena: ");
    scanf("%30s", cadena1);

    printf("Ingresa la segunda cadena: ");
    scanf("%30s", cadena2);

    if (esCadenaMezclada(cadena1, cadena2))
        printf("Resultado: VERDADERO. La segunda cadena puede obtenerse mezclando la primera.\n");
    else
        printf("Resultado: FALSO. La segunda cadena NO puede obtenerse mezclando la primera.\n");

    return 0;
}

