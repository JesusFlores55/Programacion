#include <stdio.h>
#include <limits.h>

int dividir(int dividendo, int divisor) {
    if (dividendo == INT_MIN && divisor == -1) {
        return INT_MAX;  // Evitar desbordamiento
    }

    int esNegativo = (dividendo < 0) ^ (divisor < 0);  

    long long valorAbsolutoDividendo = (long long) (dividendo < 0 ? -dividendo : dividendo);
    long long valorAbsolutoDivisor = (long long) (divisor < 0 ? -divisor : divisor);

    int cociente = 0;

    while (valorAbsolutoDividendo >= valorAbsolutoDivisor) {
        long long divisorTemporal = valorAbsolutoDivisor, multiplo = 1;

        while (valorAbsolutoDividendo >= (divisorTemporal << 1)) {
            divisorTemporal <<= 1;
            multiplo <<= 1;
        }

        valorAbsolutoDividendo -= divisorTemporal;
        cociente += multiplo;
    }

    if (esNegativo) {
        cociente = -cociente;
    }

    if (cociente < INT_MIN) {
        return INT_MIN;
    }
    if (cociente > INT_MAX) {
        return INT_MAX;
    }

    return cociente;
}

int main() {
    int dividendo, divisor;

    printf("Ingrese el dividendo: ");
    scanf("%d", &dividendo);

    printf("Ingrese el divisor: ");
    scanf("%d", &divisor);

    int resultado = dividir(dividendo, divisor);
    printf("El resultado de %d dividido por %d es: %d\n", dividendo, divisor, resultado);

    return 0;
}

