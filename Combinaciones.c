#include <stdio.h>
#include <string.h>

#define MAX_COMBINACIONES 1000  // Colocamos un límite para la cantidad de combinaciones

const char* digito_a_letras[] = {
    "",     // Para el dígito 0 
    "",     // Para el dígito 1 
    "abc",   // Para el dígito 2
    "def",   // Para el dígito 3
    "ghi",   // Para el dígito 4
    "jkl",   // Para el dígito 5
    "mno",   // Para el dígito 6
    "pqrs",  // Para el dígito 7
    "tuv",   // Para el dígito 8
    "wxyz"   // Para el dígito 9
};

// Variable global para almacenar las combinaciones
char resultado[MAX_COMBINACIONES][5];  
int cantidad_combinaciones = 0;  

// Función de backtracking para generar combinaciones
void retroceder(const char* digitos, int indice, char* camino, int longitud_camino) {
    if (digitos[indice] == '\0') {
        camino[longitud_camino] = '\0';  
        strcpy(resultado[cantidad_combinaciones], camino);  
        cantidad_combinaciones++; 
        return;
    }

    int digito = digitos[indice] - '0';  
    const char* letras = digito_a_letras[digito];
    
    int i;  
    for (i = 0; letras[i] != '\0'; i++) {
        camino[longitud_camino] = letras[i];  
        retroceder(digitos, indice + 1, camino, longitud_camino + 1);  
    }
}

// Función principal para manejar la entrada y salida
void combinacionesDeLetras(char* digitos) {
    if (digitos[0] == '\0') {
        printf("[]\n");
        return;
    }

    char camino[5];  
    cantidad_combinaciones = 0; 
    retroceder(digitos, 0, camino, 0);

    // Imprimir las combinaciones
    printf("[");
    int i;  
    for (i = 0; i < cantidad_combinaciones; i++) {
        if (i > 0) printf(", ");
        printf("\"%s\"", resultado[i]);
    }
    printf("]\n");
}

int main() {
    char digitos[10];

    printf("Introduce un numero de digitos entre 2 y 9: ");
    scanf("%s", digitos);

    combinacionesDeLetras(digitos);

    return 0;
}

