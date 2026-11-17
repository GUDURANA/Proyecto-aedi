#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void inicializar();
void procesarArchivo();
void finalizar();

void inicioCorte();
void unGrupo(); // CAMBIAR EL NOMBRE
void finCorte();

FILE * archivoStock;

void inicializar() {
  archivoStock = fopen("listaProductos.dat", "rb");
  if (archivoStock == NULL) {
    printf("No se pudo abrir el archivo.\n");
    exit(EXIT_FAILURE);
  }
}

void procesarArchivo() {
  while (!feof(archivoStock)) {
    inicioCorte();
    while ((!archivoStock)) {

    }
    finCorte();
  }
}

void finalizar() {
  printf("\nArchivo cerrado.\n");
}
