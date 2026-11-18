#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAX 51
#define LEYENDA "Reponer stock de "
// * mostrar el contenido del archivo
// * mostrar total de archivoProds por categoria
// * mostrar total de archivoProds en la lista
// * mostrar un mensaje en caso de que una categoria tenga un bajo numero de
//   archivoProds

typedef char tString[MAX];

typedef enum {
  PANTALONES,         // 0
  CAMISETAS,           // 1
  CALZADOS,      // 2
  ROPAINTERIOR, // 3
  ACCESORIOS               // 4
} tCategoria;

typedef struct {
  tString nombre;
  float precioUnidad;
  tCategoria categoria;
  int cantidad;
} tProducto;

tProducto producto;

FILE *archivoProds;

// se usa el nombre del producto como campo de control
tProducto campoControlAnt;

// globales
int cantProdsCategoria;
int totalUnidadesCategoria;
int minimoReponer;

// por producto
float costoLote;


void inicializar() {
  archivoProds = fopen("archivoProds.dat", "rb");
  if (archivoProds == NULL) {
    printf("\nNo se pudo abrir el archivo.\n");
    exit(EXIT_FAILURE);
  }

  // se guarda en la variable la 1er estructura
  fread(&producto, sizeof(tProducto), 1, archivoProds);

  // se guarda toda la 1er estructura como campo de control
  campoControlAnt = producto;

  printf("\n\n=== INFORME DE STOCK ===\n\n");
  printf("Informacion del stock:\n");
  printf("Nombre:\tCategoria:\tCantidad en el stock:\tPrecio x Unidad:\n");

  // Se inician los contadores y acumuladores globales en 0
  cantProdsCategoria = 0;
  totalUnidadesCategoria = 0;
  minimoReponer = 0;
}

// Se usa la misma funcion auxiliar que en lista.h para mostrar el nombre
// de la categoria
const char* mostrarCategoria(tCategoria pNombreCategoria) {
  switch (pNombreCategoria) {
    case 0:
      return "Alimentos";
      break;
    case 1:
      return "Bebidas";
      break;
    case 2:
      return "Herramientas";
      break;
    case 3:
      return "Electrodomesticos";
      break;
    case 4:
      return "Ropa";
      break;
    default:
      return "CATEGORIA INVALIDA";
      break;
  }
}

void inicioCorte() {
  // se inician los contadores y acumuladores para el producto en 0
  costoLote = 0.0;
  // Se muestran los datos del producto
  printf("%s\t%s\t%d\t%.2f\n",
      producto.nombre,
      mostrarCategoria(producto.categoria),
      producto.categoria,
      producto.precioUnidad);
}

void procesarLinea() {
  printf("");

  costoLote = producto.cantidad * producto.precioUnidad;
}

void finCorte() {

  campoControlAnt = producto;
}

void procesarArchivo() {
  while (!feof(archivoProds)) {
    inicioCorte();
    while ((!feof(archivoProds) &&
          (campoControlAnt.categoria == producto.categoria))) {
      fread(&producto, sizeof(tProducto), 1, archivoProds);
    }
    finCorte();
  }
}

void finalizar() { fclose(archivoProds); }
