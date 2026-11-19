#include "corteControl.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool confirmar() {
  char respuesta;

  do {
    printf("¿Desea continuar la ejecucion del programa? S/N: ");
    scanf(" %c", &respuesta);

    respuesta = tolower(respuesta); // Se convierte en minuscula la respuesta
  } while ((respuesta != 's') && (respuesta != 'n'));
  if (respuesta == 'n') {
    printf("Terminando ejecucion del programa...\n");
  }

  // Se usa un ternario para evaluar que valor devolver
  return (respuesta == 's') ? true : false;
}

void mostrarOpcionesMenu() {
  printf("\n*** Bienvenido al programa ***\n");

  printf("\nOperaciones disponibles:\n\n");

  printf("1. Agregar producto al stock.\n");
  printf("2. Eliminar producto del stock.\n");
  printf("3. Mostrar lista de productos.\n");
  printf("4. Guardar lista en archivo (.dat).\n");
  printf("5. Mostrar Informe del stock.\n");
  printf("6. Salir del menu y terminar ejecucion del programa.\n");
}

void mostrarMenu(tListaProds **pLista) {
  int opcion;
  bool continuar = true;
  tProducto datos;
  do {
    mostrarOpcionesMenu();
    printf("Elija la operacion a realizar: ");
    scanf(" %d", &opcion);

    // agregar do while que obligue a ingresar una opcion valida
    switch (opcion) {
    case 1:
      datos = ingresoDatosProd();
      agregarNuevoProd(pLista, datos);
      break;
    case 2:
      eliminarProd(pLista);
      break;
    case 3:
      mostrarListaProds(*pLista);
      break;
    case 4:
      guardarLista(*pLista);
      break;
    case 5:
      realizarInforme();
      break;
    case 6:
      printf("Terminando ejecucion del programa...\n");
      continuar = false;
      return;
    default:
      printf("El valor ingresado no corresponde a ninguna operacion.\n");
      break;
    }
    continuar = confirmar();
  } while (continuar);
}
