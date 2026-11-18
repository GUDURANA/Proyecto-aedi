// ARCHIVO DE PRUEBA PARA LAS FUNCIONES DE LA LISTA

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 51

typedef char tString[MAX];

// estructura para los tipos de ropa validos
typedef enum {
    PANTALONES, // 0
    CAMISETAS, // 1
    CALZADOS, // 2
    ROPAINTERIOR, // 3
    ACCESORIOS // 4
} tCategoria;

typedef struct {
    tString nombre;
    float precioUnidad; // se ingresa el precio por unidad
    tCategoria categoria;
    int cantidad;
} tProducto;

typedef struct nodo {
    tProducto datosProd;
    struct nodo *siguiente;
} tListaProds;

FILE * ropa;

bool listaVacia(tListaProds *pLista) {
  return pLista == NULL;
}

void inicializarLista(tListaProds **pLista) {
  *pLista = NULL;
  printf("Creando lista de ropa en el stock...\n");
}

tProducto ingresoDatosProd() {
  tProducto datos;
  int opcionCategoria; // Necesario para el enum

  printf("Ingrese el nombre del producto: ");
  scanf(" %[^\n]", datos.nombre);
  printf("Ingrese el precio del producto: ");
  scanf(" %f", &datos.precioUnidad);
  printf("Categorias validas:\n");
  printf("0 - Pantalones | 1 - Camisetas | 2 - Calzados | "
         "3 - Ropa Interior | 4 - Accesorios\n");
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
    (*pLista) = nuevoProd;
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
    printf("La lista de ropa esta vacia. Los datos ingresados"
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
      for (i = 1; (i < k-1) && ((recorrerLista != NULL)); i++) {
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

void agregarProdFinal(tListaProds **pLista, tProducto pDatosProd) {
  if (listaVacia(*pLista)) {
    printf("La lista de ropa esta vacia. Los datos ingresados"
           " corresponderan al primer producto.\n");
    agregarPrimerProducto(pLista, pDatosProd);
  } else {
    tListaProds *agregarFinal, *recorrerLista;
    recorrerLista = (*pLista);

    while (recorrerLista->siguiente != NULL) {
      recorrerLista = recorrerLista->siguiente;
    }

    agregarFinal = (tListaProds *) malloc(sizeof(tListaProds));
    agregarFinal->datosProd = pDatosProd;
    agregarFinal->siguiente = NULL;
    recorrerLista->siguiente = agregarFinal;
  }
}

// se muestra un submenu con las opciones para agregar ropa
void mostrarOpcionesAgregarProd() {
  printf("\nElija la operacion de agregado a realizar:\n");
  // elegir entre frente o primer posicion de la lista como mensaje
  printf("1. Agregar en el frente de la lista.\n");
  printf("2. Agregar en k-posicion de la lista.\n");
  // elegir entre final o ultima posicion
  printf("3. Agregar en el final de la lista.\n");
  printf("4. Cancelar operacion y volver al menu principal.\n");
}

// auxiliar para las funciones insertarEnK y eliminarEnK
int ingresoK() {
  int kLocal;

  printf("Ingrese un valor para k: ");
  scanf(" %d", &kLocal);

  return kLocal;
}

void agregarNuevoProd(tListaProds **pLista, tProducto pDatosProd) {
  if (listaVacia(*pLista)) {
    printf("\nLa lista de ropa esta vacia. Los datos ingresados"
           " corresponderan al primer producto de la lista.\n");
    agregarPrimerProducto(pLista, pDatosProd);
  } else {
    int opcion;
    do {
      mostrarOpcionesAgregarProd();
      printf("Ingrese la operacion: ");
      scanf(" %d", &opcion);
      if ((opcion <= 0) || (opcion >= 5)) {
        printf("El valor ingresado no corresponde a ninguna de las operaciones"
               " enumeradas. Intente de nuevo.\n");
      }
    }while ((opcion <= 0) || (opcion >= 5));
    switch (opcion) {
      case 1:
        insertarProdEnFrente(pLista, pDatosProd);
        break;
      case 2:
        int k = ingresoK();
        insertarEnK(pLista, pDatosProd, k);
        break;
      case 3:
        agregarProdFinal(pLista, pDatosProd);
        break;
      case 4:
        printf("Volviendo al menu principal...\n");
        return;
    }
  }
}

void eliminarPrimero(tListaProds **pLista) {
  if (listaVacia(*pLista)) {
    printf("\nLa lista de ropa esta vacia. No hay nada que eliminar.\n");
  } else {
    tListaProds *delPrim = (*pLista);
    (*pLista) = (*pLista)->siguiente;

    free(delPrim);
    delPrim = NULL;

    printf("\nPrimer producto de la lista eliminado!\n");
  }
}

void eliminarEnK(tListaProds **pLista, int k) {
  if (k <= 0) {
    printf("El valor ingresado no es un indice valido."
        " Volviendo al menu principal.\n");
    return;
  }

  if (listaVacia(*pLista)) {
    printf("\nLa lista de ropa esta vacia. No hay nada que eliminar.\n");
  } else {
    tListaProds *delProd, *recorrerLista;
    recorrerLista = (*pLista);
    int i;

    if (k == 1) {
      eliminarPrimero(pLista);
    } else {
      for (i = 1; (i < k-1) && (recorrerLista != NULL); i++) {
        recorrerLista = recorrerLista->siguiente;
      }

      // Es necesario revisar que tanto recorrerLista como su siguiente no
      // sean NULL para que no de problemas al momento de conectar
      if ((recorrerLista == NULL) || (recorrerLista->siguiente == NULL)) {
        printf("El valor ingresado no existe como indice dentro de la lista."
               " Regresando al menu principal.\n");
        return;
      }

      delProd = recorrerLista->siguiente;
      // si recorrerLista.siguiente fuese NULL se estaria tratando de
      // conectar con el siguiente de NULL
      recorrerLista->siguiente = delProd->siguiente;
      free(delProd);
      delProd = NULL;

      printf("\nProducto en la posicion %d eliminado!\n", k);
    }
  }
}

void eliminarUltimo(tListaProds **pLista) {
  if (listaVacia(*pLista)) {
    printf("\nLa lista de ropa esta vacia. No hay nada que eliminar.\n");
  } else if ((*pLista)->siguiente == NULL) {
    // en caso de que tenga un solo elemento se llama a eliminarPrimero
    eliminarPrimero(pLista);
  } else {
    tListaProds *delProd, *recorrerLista;
    recorrerLista = (*pLista);
    // se recorre y se para en el penultimo elemento
    while (recorrerLista->siguiente->siguiente != NULL) {
      recorrerLista = recorrerLista->siguiente;
    }

    delProd = recorrerLista->siguiente;
    recorrerLista->siguiente = delProd->siguiente; // apunta a NULL
    free(delProd);
    delProd = NULL;

    printf("\nUltimo producto de la lista, eliminado!\n");
  }
}

void mostrarOpcionesEliminarProd() {
  printf("\nElija la operacion de eliminacion a realizar:\n");
  printf("1. Eliminar en el frente de la lista.\n");
  printf("2. Eliminar en k-posicion de la lista.\n");
  printf("3. Eliminar en el final de la lista.\n");
  printf("4. Cancelar operacion y volver al menu principal.\n");
}

void eliminarProd(tListaProds **pLista) {
  if (listaVacia(*pLista)) {
    printf("La lista esta vacia. No hay nada que eliminar. Volviendo al"
        " menu princpal.\n");
    return;
  } else {
    int opcion;
    do {
      mostrarOpcionesEliminarProd();
      printf("Ingrese la operacion: ");
      scanf(" %d", &opcion);
      if ((opcion <= 0) || (opcion >= 5)) {
        printf("El valor ingresado no corresponde a ninguna de las operaciones"
               " enumeradas. Intente de nuevo.\n");
      }
    }while ((opcion <= 0) || (opcion >= 5));
    switch (opcion) {
      case 1:
        eliminarPrimero(pLista);
        break;
      case 2:
        int k = ingresoK();
        eliminarEnK(pLista, k);
        break;
      case 3:
        eliminarUltimo(pLista);
        break;
      case 4:
        printf("Volviendo al menu principal...\n");
        break;
    }
  }
}

// Funcion auxiliar para mostrar el nombre de la categoria
// recibe el valor de la categoria como argumento y lo compara con los
// casos del switch
const char* mostrarCategoria(tCategoria pNombreCategoria) {
  switch (pNombreCategoria) {
    case 0:
      return "Pantalones";
      break;
    case 1:
      return "Camisetas";
      break;
    case 2:
      return "Calzados";
      break;
    case 3:
      return "Ropa Interior";
      break;
    case 4:
      return "Accesorios";
      break;
    default:
      return "CATEGORIA INVALIDA";
      break;
  }
}

void mostrarListaProds(tListaProds *pLista) {
  if (listaVacia(pLista)) {
    printf("La lista de ropa esta vacia. No hay nada que mostrar.\n");
  } else {
    tListaProds *recorrerLista = pLista;
    printf("\n\n === Mostrando Lista de ropa ===\n\n");
    while (recorrerLista != NULL) {
      printf("Nombre del Producto: %s\n", recorrerLista->datosProd.nombre);
      printf("Precio del producto: %.2f\n",
          recorrerLista->datosProd.precioUnidad);
      printf("Categoria del producto: %s\n",
             mostrarCategoria(recorrerLista->datosProd.categoria));
      printf("\n");
      recorrerLista = recorrerLista->siguiente;
    }
  }
}

// se abre, guarda y cierra la lista todo en una sola funcion
void guardarLista(tListaProds *pLista) {
  if (listaVacia(pLista)) {
    printf("La lista de ropa esta vacia. No hay nada que guardar."
        " Regresando al menu principal.\n");
    return;
  }

  ropa = fopen("ropa.dat", "ab");
  if (ropa == NULL) {
    printf("\nNo se pudo abrir el archivo de la lista de ropa.\n");
    exit(EXIT_FAILURE);
  }

  tListaProds *recorrerLista = pLista;

  while (recorrerLista != NULL) {
    fwrite(&(recorrerLista->datosProd), sizeof(tProducto), 1, ropa);
    recorrerLista = recorrerLista->siguiente;
  }

  printf("\nLista guardada en el archivo!\n");

  fclose(ropa);
}
