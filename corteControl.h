#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#define MAX 51
#define LEYENDA "Reponer stock de: "
// * mostrar el contenido del archivo
// * mostrar total de archivoProds por categoria
// * mostrar total de archivoProds en la lista
// * mostrar un mensaje en caso de que una categoria tenga un bajo numero de
//   archivoProds

tProducto producto;

FILE *archivoProds;

// se usa toda la estructura como campo de control
tProducto campoControlAnt;

// M: Mujer | H: Hombre | X: Unisex

// globales
// acumuladores
int cantTotalRopaH;
int cantTotalRopaM;
int cantTotalRopaX;

int cantTotalLotesH;
int cantTotalLotesM;
int cantTotalLotesX;

// contadores
tProducto prodMinimo; // estructura que contiene los datos del producto con
                      // menor cantidad de unidades

int totalLotesAdulto;
int totalLotesNinio;

// acumuladores
int totalPantalones;
int totalCamisetas;
int totalcalzados;
int totalRopaInterior;
int totalSombreros;

// por producto
// contadores
int cantUnidadesRopaH;
int cantUnidadesRopaM;
int cantUnidadesRopaX;

int totalRopaAdultoEnLote; // usan cantidad
int totalRopaNinioEnLote;

void inicializar() {
  archivoProds = fopen("archivoRopas.dat", "rb");
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
  printf("Genero:\tCategoria:\tCantidad en el stock:\tPrecio x Unidad:\n");

  // Se inician los contadores y acumuladores globales en 0
  cantTotalRopaH = 0;
  cantTotalRopaM = 0;
  cantTotalRopaX = 0;

  cantTotalLotesH = 0;
  cantTotalLotesM = 0;
  cantTotalLotesX = 0;

  totalPantalones = 0;
  totalCamisetas = 0;
  totalcalzados = 0;
  totalRopaInterior = 0;
  totalSombreros = 0;

  // se guarda la 1er cantidad ingresada como el minimo
  prodMinimo = producto;

  totalLotesAdulto = 0;
  totalLotesNinio = 0;
}

void inicioCorte() {
  // se inician los contadores y acumuladores para el producto en 0

  totalRopaAdultoEnLote = 0;
  totalRopaNinioEnLote = 0;

  cantUnidadesRopaH = 0;
  cantUnidadesRopaM = 0;
  cantUnidadesRopaX = 0;
}

void procesarRegistro() {
  int opcionCategoria = producto.categoria;

  switch (opcionCategoria) {
  case 0:
    totalPantalones += producto.cantidad;
    break;
  case 1:
    totalCamisetas += producto.cantidad;
    break;
  case 2:
    totalcalzados += producto.cantidad;
    break;
  case 3:
    totalRopaInterior += producto.cantidad;
    break;
  case 4:
    totalSombreros += producto.cantidad;
    break;
  default:
    printf("CATEGORIA INVALIDA\n");
    break;
  }

  switch (producto.genero) {
    case 'h':
      cantUnidadesRopaH += producto.cantidad;
      break;
    case 'm':
      cantUnidadesRopaM += producto.cantidad;
      break;
    case 'x':
      cantUnidadesRopaX += producto.cantidad;
      break;
  }

  if (prodMinimo.cantidad > producto.cantidad) {
    prodMinimo = producto;
  }

  if (producto.paraAdulto) {
    totalRopaAdultoEnLote++;
    totalLotesAdulto++;
  } else {
    totalRopaNinioEnLote++;
    totalLotesNinio++;
  }

  // Se muestran los datos del producto
  printf("%c\t\t%s\t%d\t%.2f\n",
      producto.genero,
      // Se usa la misma funcion auxiliar que en lista.h para mostrar el nombre
      mostrarCategoria(producto.categoria),
      producto.cantidad,
      producto.precioUnidad);
}

void finCorte() {
  switch (campoControlAnt.genero) {
    case 'h':
      cantTotalRopaH += cantUnidadesRopaH;
      break;
    case 'm':
      cantTotalRopaM += cantUnidadesRopaM;
      break;
    case 'x':
      cantTotalRopaX += cantUnidadesRopaX;
      break;
  }

  printf("Cantidad de Unidades de Ropa %s: %d\n",
      mostrarGenero(campoControlAnt.genero),
      // se usa un ternario para saber que subtotal mostrar
      (campoControlAnt.genero == 'h') ? cantTotalRopaH :
      (campoControlAnt.genero == 'm') ? cantTotalRopaM :
      cantTotalRopaX);
  printf("Cantidad de ropa para %s en el lote: %d\n",
      (campoControlAnt.paraAdulto == true) ? "Adultos" : "Ninios",
      (campoControlAnt.paraAdulto == true) ? totalRopaAdultoEnLote :
      totalRopaNinioEnLote);

  campoControlAnt = producto;
}

void procesarArchivo() {
  while (!feof(archivoProds)) {
    inicioCorte();
    while ((!feof(archivoProds) &&
          (campoControlAnt.genero == producto.genero))) {
      procesarRegistro();
      fread(&producto, sizeof(tProducto), 1, archivoProds);
    }
    finCorte();
  }
}

void finalizar() {
  printf("Total de lotes por edad:\n");
  printf("Adultos: %d\n", totalLotesAdulto);
  printf("Ninios: %d\n", totalLotesNinio);

  printf("Cantidad total de productos por genero:\n");
  printf("Hombres: %d\n", cantTotalRopaH);
  printf("Mujeres: %d\n", cantTotalRopaM);
  printf("Unisex: %d\n", cantTotalRopaX);

  printf("Cantidad total de Unidades por Categoria:\n");
  printf("Pantalones: %d\n", totalPantalones);
  printf("Camisetas: %d\n", totalCamisetas);
  printf("Calzados: %d\n", totalcalzados);
  printf("Ropa Interior: %d\n", totalRopaInterior);
  printf("Sombreros: %d\n", totalSombreros);

  printf("%s %s de %s\n",
      LEYENDA,
      mostrarCategoria(prodMinimo.categoria),
      mostrarGenero(prodMinimo.genero));
  fclose(archivoProds);
}

void realizarInforme() {
  inicializar();
  procesarArchivo();
  finalizar();
}
