#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXCAR 51

typedef char tString[MAXCAR];

typedef enum {
  ALIMENTOS,
  BEBIDAS,
  HERRAMIENTAS,
  ELECTRODOMESTICOS,
  ROPA
}tTipo;

typedef struct {
  tString nombre;
  float precio;
  tTipo tipo;
  int cantidad;
}tProducto;


typedef struct nodo {
  tProducto datosProducto;
  struct nodo *siguiente;
}tListaProd;

FILE * archivoStock;

tProducto ingresoDatosProducto();

void mostrarTiposProducto();

bool listaVacia(tListaProd *);

void inicializarLista(tListaProd *);

void agregarNuevoProducto(tListaProd *, tProducto);
void guardarLista();

void eliminarUltimoProducto(tListaProd **);

bool listaVacia(tListaProd *pLista) {
  return pLista == NULL;
}

void inicializarLista(tListaProd *pLista) {
  pLista = NULL;
}

tProducto ingresoDatosProducto() {
  tProducto datos;
  bool validarTipo = false;

  printf("Ingrese el nombre del producto: ");
  scanf(" %[^\n]", datos.nombre);
  printf("Ingrese el precio del producto: ");
  scanf(" %f", &datos.precio);
  // para el tipo conviene mostrar un printf que muestre los tipos disponibles
  printf("Ingrese el tipo de producto: ");
  scanf(" %d", &datos.tipo);
  printf("Ingrese la cantidad del producto: ");
  scanf(" %d", &datos.cantidad);

  return datos;
}

void agregarNuevoProducto(tListaProd *pLista, tProducto pDatos) {
  tListaProd *nuevoProd = (tListaProd *) malloc(sizeof(tListaProd));
  nuevoProd->datosProducto = pDatos;
  nuevoProd->siguiente = pLista;
  pLista = nuevoProd;
}

void eliminarUltimoProducto(tListaProd **pLista) {
  if (listaVacia(*pLista)) {
    printf("La lista esta vacia. No hay ningun producto para eliminar.\n");
  } else {
    tListaProd **eliminarProd = pLista;

  }
}
