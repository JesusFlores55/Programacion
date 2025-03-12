#include <stdio.h>
#include <string.h>

#define MAX_COMBINACIONES 1000  // Colocamos un l�mite para la cantidad de combinaciones

const char* digito_a_letras[] = {
    "",     // Para el d�gito 0 
    "",     // Para el d�gito 1 
    "abc",   // Para el d�gito 2
    "def",   // Para el d�gito 3
    "ghi",   // Para el d�gito 4
    "jkl",   // Para el d�gito 5
    "mno",   // Para el d�gito 6
    "pqrs",  // Para el d�gito 7
    "tuv",   // Para el d�gito 8
    "wxyz"   // Para el d�gito 9
};

// Variable global para almacenar las combinaciones
char resultado[MAX_COMBINACIONES][5];  
int cantidad_combinaciones = 0;  

// Funci�n de backtracking para generar combinaciones
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

// Funci�n principal para manejar la entrada y salida
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

