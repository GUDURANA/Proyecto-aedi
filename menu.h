#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void mostrarOpcionesMenu();
void mostrarMenu();

bool confirmar();

void mostrarOpcionesMenu() {
  printf("\n*** Bienvenido al programa ***\n");

  printf("\nOperaciones disponibles:\n\n");

  printf("1. Agregar producto al stock.\n");
  printf("2. Eliminar producto del stock.\n");
  printf("3. Crear Informe del stock.\n");
  printf("4. Mostrar Informe del stock.\n");
  printf("xx. Salir del menu y terminar ejecucion del programa.\n");
}

void mostrarMenu() {
  int opcion;
  bool continuar = true;

  do {
    mostrarOpcionesMenu();
    printf("Elija la operacion a realizar: ");
    scanf(" %d", &opcion);

    switch (opcion) {
    case 1:

      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    }
    continuar = confirmar();
  } while (continuar);
}

bool confirmar() {
  char respuesta;

  do {
    printf("¿Desea continuar la ejecucion del programa? S/N");
    scanf(" %c", &respuesta);

    respuesta = tolower(respuesta); // Se convierte en minuscula la respuesta
  } while ((respuesta != 's') && (respuesta != 'n'));

  // Se usa un ternario para evaluar que valor devolver
  return (respuesta == 's') ? true : false;
}
