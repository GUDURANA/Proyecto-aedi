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

bool listaVacia(tListaProds *pLista) {
  return pLista == NULL;
}

void inicializarLista(tListaProds **pLista) {
  *pLista = NULL;
  printf("Creando lista de productos en el stock...\n");
}

tProducto ingresoDatosProd() {
  tProducto datos;
  int opcionCategoria; // Necesario para el enum

  printf("Ingrese el nombre del producto: ");
  scanf(" %[^\n]", datos.nombre);
  printf("Ingrese el precio del producto: ");
  scanf(" %f", &datos.precio);
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

// Doble puntero para evitar variables globales de desarrollar
// se puede cambiar si hace que el codigo sea muy dificil
void agregarPrimerProducto(tListaProds **pLista, tProducto pDatosProd) {
  if (!listaVacia(*pLista)) {
    printf("La lista no esta vacia. No se puede agregar al informacion"
           " del producto. Regresando al menu principal.\n");
  } else {
    tListaProds *nuevoProd = (tListaProds *) malloc(sizeof(tListaProds));
    nuevoProd->datosProd = pDatosProd;
    nuevoProd->siguiente = NULL;
    (*pLista) = nuevoProd;
    printf("1er Producto agregado a la lista!\n");
  }
}

// pensar en un mejor nombre para esta funcion
void insertarProdEnFrente(tListaProds **pLista, tProducto pDatosProd) {
  if (listaVacia(*pLista)) {
    printf("La lista esta vacia. Los datos ingresados corresponderan al"
           " primer producto.\n");
    agregarPrimerProducto(pLista, pDatosProd);
  } else {
    tListaProds *nuevoProd = (tListaProds *) malloc(sizeof(tListaProds));
    nuevoProd->datosProd = pDatosProd;
    nuevoProd->siguiente = *pLista;
    (*pLista)->siguiente = nuevoProd;
    printf("Nuevo producto ingresado en el frente de la lista!\n");
  }
}

void insertarEnK(tListaProds **pLista, tProducto pDatosProd, int k) {
  // Se evalua que el indice pasado no sea un numero negativo
  if (k <= 0) {
    printf("El valor ingresado no es un indice valido."
           " Volviendo al menu principal.\n");
    return;
  }

  if (listaVacia(*pLista)) {
    printf("La lista de productos esta vacia. Los datos ingresados"
           " corresponderan al primer producto.\n");
    agregarPrimerProducto(pLista, pDatosProd);
  } else {
    tListaProds *nuevoProd, *recorrerLista;
    recorrerLista = (*pLista);
    int i;

    // Si es 1 se empuja el valor que esta en el frente
    if (k == 1) {
      printf("Insertando datos del nuevo producto en el frente de la lista\n");
      insertarProdEnFrente(pLista, pDatosProd);
    } else {

      // Condiciones del loop:
      // se detiene en la posicion anterior a k
      // Para en caso de que la lista no tenga mas elementos
      for (i = 1; (i < k - 1) && ((recorrerLista != NULL)); i++) {
        recorrerLista = recorrerLista->siguiente;
      }

      // En caso de que el loop haya terminado porque recorrerLista paso a NULL
      // se muestra un mensaje de error y se sale de la funcion
      if (recorrerLista == NULL) {
        printf("El valor ingresado no existe como indice dentro de la lista."
               " Regresando al menu principal.\n");
        return;
      }

      nuevoProd = (tListaProds *) malloc(sizeof(tListaProds));
      nuevoProd->datosProd = pDatosProd;
      nuevoProd->siguiente = recorrerLista->siguiente;
      recorrerLista->siguiente = nuevoProd;

      printf("Producto agregado en la posicion %d de la lista!\n", k);
    }
  }
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

int main() {
  return 0;
}
