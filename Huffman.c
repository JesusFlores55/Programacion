#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARACTERES 256
#define MAX_LONGITUD_CODIGO 1000

typedef struct Nodo {
    char caracter;
    int frecuencia;
    struct Nodo *izquierda, *derecha;
} Nodo;

typedef struct {
    Nodo* datos[MAX_CARACTERES];
    int tamanio;
} MonticuloMinimo;

Nodo* crearNodo(char caracter, int frecuencia) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->caracter = caracter;
    nodo->frecuencia = frecuencia;
    nodo->izquierda = nodo->derecha = NULL;
    return nodo;
}

void intercambiar(Nodo** a, Nodo** b) {
    Nodo* temp = *a;
    *a = *b;
    *b = temp;
}

void ajustarMonticulo(MonticuloMinimo* monticulo, int i) {
    int menor = i, izquierda = 2*i + 1, derecha = 2*i + 2;
    if (izquierda < monticulo->tamanio && monticulo->datos[izquierda]->frecuencia < monticulo->datos[menor]->frecuencia)
        menor = izquierda;
    if (derecha < monticulo->tamanio && monticulo->datos[derecha]->frecuencia < monticulo->datos[menor]->frecuencia)
        menor = derecha;
    if (menor != i) {
        intercambiar(&monticulo->datos[i], &monticulo->datos[menor]);
        ajustarMonticulo(monticulo, menor);
    }
}

MonticuloMinimo* construirMonticulo(int frecuencias[]) {
    MonticuloMinimo* monticulo = (MonticuloMinimo*)malloc(sizeof(MonticuloMinimo));
    monticulo->tamanio = 0;
    for (int i = 0; i < MAX_CARACTERES; i++) {
        if (frecuencias[i] > 0)
            monticulo->datos[monticulo->tamanio++] = crearNodo(i, frecuencias[i]);
    }
    for (int i = monticulo->tamanio / 2 - 1; i >= 0; i--)
        ajustarMonticulo(monticulo, i);
    return monticulo;
}

Nodo* extraerMinimo(MonticuloMinimo* monticulo) {
    Nodo* minimo = monticulo->datos[0];
    monticulo->datos[0] = monticulo->datos[--monticulo->tamanio];
    ajustarMonticulo(monticulo, 0);
    return minimo;
}

void insertarMonticulo(MonticuloMinimo* monticulo, Nodo* nodo) {
    int i = monticulo->tamanio++;
    while (i && nodo->frecuencia < monticulo->datos[(i - 1) / 2]->frecuencia) {
        monticulo->datos[i] = monticulo->datos[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    monticulo->datos[i] = nodo;
}

Nodo* construirArbolHuffman(int frecuencias[]) {
    MonticuloMinimo* monticulo = construirMonticulo(frecuencias);
    while (monticulo->tamanio > 1) {
        Nodo* izquierda = extraerMinimo(monticulo);
        Nodo* derecha = extraerMinimo(monticulo);
        Nodo* combinado = crearNodo('$', izquierda->frecuencia + derecha->frecuencia);
        combinado->izquierda = izquierda;
        combinado->derecha = derecha;
        insertarMonticulo(monticulo, combinado);
    }
    return extraerMinimo(monticulo);
}

void generarCodigos(Nodo* raiz, char* codigo, int profundidad, char codigos[][MAX_LONGITUD_CODIGO]) {
    if (raiz->izquierda == NULL && raiz->derecha == NULL) {
        codigo[profundidad] = '\0';
        strcpy(codigos[(unsigned char)raiz->caracter], codigo);
        return;
    }
    if (raiz->izquierda) {
        codigo[profundidad] = '0';
        generarCodigos(raiz->izquierda, codigo, profundidad + 1, codigos);
    }
    if (raiz->derecha) {
        codigo[profundidad] = '1';
        generarCodigos(raiz->derecha, codigo, profundidad + 1, codigos);
    }
}

void comprimirArchivo(const char* entrada, const char codigos[][MAX_LONGITUD_CODIGO], long* bitsOriginales, long* bitsCodificados) {
    FILE *archivoEntrada = fopen(entrada, "r");
    FILE *archivoSalida = fopen("Codificado.txt", "w");
    int caracter;
    *bitsOriginales = *bitsCodificados = 0;
    while ((caracter = fgetc(archivoEntrada)) != EOF) {
        fputs(codigos[(unsigned char)caracter], archivoSalida);
        *bitsOriginales += 8;
        *bitsCodificados += strlen(codigos[(unsigned char)caracter]);
    }
    fclose(archivoEntrada);
    fclose(archivoSalida);
}

void decodificarArchivo(Nodo* raiz, const char* archivoCodificado) {
    FILE *archivo = fopen(archivoCodificado, "r");
    Nodo* actual = raiz;
    int bit;
    while ((bit = fgetc(archivo)) != EOF) {
        if (bit == '0')
            actual = actual->izquierda;
        else
            actual = actual->derecha;

        if (actual->izquierda == NULL && actual->derecha == NULL) {
            putchar(actual->caracter);
            actual = raiz;
        }
    }
    fclose(archivo);
}

void guardarTablaCodigos(const char codigos[][MAX_LONGITUD_CODIGO]) {
    FILE* archivo = fopen("TablaCodigos.txt", "w");
    if (!archivo) {
        printf("No se pudo crear TablaCodigos.txt\n");
        return;
    }

    for (int i = 0; i < MAX_CARACTERES; i++) {
        if (codigos[i][0] != '\0') {
            if (i == '\n') {
                fprintf(archivo, "'\\n': %s\n", codigos[i]);
            } else if (i == '\t') {
                fprintf(archivo, "'\\t': %s\n", codigos[i]);
            } else if (i == ' ') {
                fprintf(archivo, "'espacio': %s\n", codigos[i]);
            } else if (i < 32 || i > 126) {
                fprintf(archivo, "'ASCII %d': %s\n", i, codigos[i]);
            } else {
                fprintf(archivo, "'%c': %s\n", i, codigos[i]);
            }
        }
    }

    fclose(archivo);
}

int main() {
    FILE* archivoEntrada = fopen("Entrada.txt", "r");
    if (!archivoEntrada) {
        printf("No se pudo abrir Entrada.txt\n");
        return 1;
    }

    int frecuencias[MAX_CARACTERES] = {0};
    int caracter;
    while ((caracter = fgetc(archivoEntrada)) != EOF)
        frecuencias[(unsigned char)caracter]++;
    fclose(archivoEntrada);

    Nodo* raiz = construirArbolHuffman(frecuencias);

    char codigos[MAX_CARACTERES][MAX_LONGITUD_CODIGO] = {0};
    char temporal[MAX_LONGITUD_CODIGO];
    generarCodigos(raiz, temporal, 0, codigos);

    long bitsOriginales, bitsCodificados;
    comprimirArchivo("Entrada.txt", codigos, &bitsOriginales, &bitsCodificados);

    printf("Original: %ld bits\n", bitsOriginales);
    printf("Comprimido: %ld bits\n", bitsCodificados);
    printf("Tasa de compresion: %.2f%%\n", 100.0 * bitsCodificados / bitsOriginales);

    guardarTablaCodigos(codigos);  // Guardar la tabla de códigos en archivo

    printf("\nTexto decodificado:\n");
    decodificarArchivo(raiz, "Codificado.txt");

    return 0;
}
