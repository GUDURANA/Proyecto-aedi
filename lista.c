// ARCHIVO DE PRUEBA PARA LAS FUNCIONES DE LA LISTA

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 51

typedef char tString[MAX];

// estructura para los tipos de productos validos
typedef enum {
    ALIMENTOS, // 0
    BEBIDAS, // 1
    HERRAMIENTAS, // 2
    ELECTRODOMESTICOS, // 3
    ROPA // 4
} tCategoria;

typedef struct {
    tString nombre;
    float precio;
    tCategoria categoria;
    int cantidad;
} tProducto;

typedef struct nodo {
    tProducto datosProd;
    struct nodo *siguiente;
} tListaProds;

tProducto ingresoDatosProd() {
  tProducto datos;
  int opcionCategoria; // Necesario para el enum

  printf("Ingrese el nombre del producto: ");
  scanf(" %[^\n]", datos.nombre);
  printf("Ingrese el precio del producto: ");
  scanf(" %f", &datos.precio);
  // para el tipo conviene mostrar un printf que muestre los tipos disponibles
  printf("Categorias validas:\n");
  printf("0 - Alimentos | 1 - Bebidas | 2 - Herramientas | "
         "3 - Electrodomesticos | 4 - Ropa\n");
  printf("Ingrese la categoria del producto: ");
  scanf(" %d", &opcionCategoria);
  printf("Ingrese la cantidad del producto: ");
  scanf(" %d", &datos.cantidad);

  datos.categoria = opcionCategoria; // Se asigna el valor ingresado

  return datos;
}

bool listaVacia(tListaProds *pLista) {
  return pLista == NULL;
}

// Funcion auxiliar para mostrar el nombre de la categoria
// recibe el valor de la categoria como argumento y lo compara con los
// casos del switch
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

void mostrarListaProds(tListaProds *pLista) {
  if (listaVacia(pLista)) {
    printf("La lista de productos esta vacia. No hay nada que mostrar.\n");
  } else {
    // renombrar variable auxiliar
    tListaProds *aux = pLista;
    printf("\n\n === Mostrando Lista de Productos ===\n\n");
    while (aux != NULL) {
      printf("Nombre del Producto: %s\n", pLista->datosProd.nombre);
      printf("Precio del producto: %.2f\n", pLista->datosProd.precio);
      printf("Categoria del producto: %s\n",
             mostrarCategoria(pLista->datosProd.categoria));
      printf("\n");
      aux = aux->siguiente;
    }
  }
}
