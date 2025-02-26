#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define Maximo 10


bool Palindromo(int x) {
    if (x < 0) return false;  // Los números negativos no pueden ser palíndromos

    int pila[Maximo];  
    int top = -1;           
    int original = x;   
    int num_digitos = 0;   

	// Iniciamos pila
    while (x > 0) {
        pila[++top] = x % 10;  
        x /= 10;              
        num_digitos++;
    }

    // Comparamos los dígitos con los que estan en la pila
    x = original; 
	int i; 
    for ( i = 0; i < num_digitos / 2; i++) {
        if (pila[top--] != x % 10) {  
            return false;  
        }
        x /= 10; 
    }

    return true;  
}

int main() {
	
	int numero; 
	printf("Ingrese un numero:");
	scanf("%d", &numero);
	
	if (Palindromo(numero)) { 
		printf("Es un palindromo");
	} else {
		printf("No es un palindromo");	
	}
	return 0;
}

