#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 51
#define LEYENDA "Reponer stock de "
// * mostrar el contenido del archivo
// * mostrar total de productos por categoria
// * mostrar total de productos en la lista
// * mostrar un mensaje en caso de que una categoria tenga un bajo numero de
//   productos

typedef char tString[MAX];

typedef enum {
  ALIMENTOS,         // 0
  BEBIDAS,           // 1
  HERRAMIENTAS,      // 2
  ELECTRODOMESTICOS, // 3
  ROPA               // 4
} tCategoria;

typedef struct {
  tString nombre;
  float precio;
  tCategoria categoria;
  int cantidad;
} tProducto;

FILE *productos;

// se usa el nombre del producto como campo de control
tProducto campoControlAnt;

int cantProdsCategoria;
int totalUnidadesCategoria;

void inicializar() {
  productos = fopen("productos.dat", "rb");
  if (productos == NULL) {
    printf("\nNo se pudo abrir el archivo.\n");
    exit(EXIT_FAILURE);
  }


  printf("\n\n=== INFORME DE STOCK ===\n\n");
  printf("Informacion del stock:\n");
  printf("Nombre:\tCategoria:\tCantidad en el stock:\tPrecio x Unidad:\n");
}

void inicioCorte() {}

void procesarLinea() { printf(""); }

void finCorte() {}

void procesarArchivo() {

  while (!feof(productos)) {
    inicioCorte();
    while ((!feof(productos) && ())) {
    }
    finCorte();
  }
}

void finalizar() { fclose(productos); }
