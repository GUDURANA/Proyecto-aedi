// #include <windows.h>
#include "mostrar.h"// tad usado en la funcion

typedef char sTring[20];
// la estructura para los productos a ingresar
typedef struct{
	sTring Descripcion;
	float Precio;
	int Tipo;
	int Cantidad;
}registro;
// el registro y la variable
registro regProducto;

tDatos producto;// lo uso en INGRESAR PRODUCTO elTAD
tLista * listaProducto; // uso una lista para los productos

FILE * PRODUCTOS;// mi archivo

void ingresarProducto(tDatos);
void ingresarProducto2(tDatos);
void eliminarProducto();
void eliminarPrimerProducto();

void cargarArchivo(tDatos);
void guardarArchivo(tLista*);
void mostrarArchivo();

void inicializar();
void inicioCorte();
void procesoCorte();
void unProducto();
void finCorte();
void finalizar();

int Menu();

int codTipoAnt, totalProductos, tipoProductoTotal;

int main(){
	int numero= 0;
	inicializarLista();
	do{
		numero = Menu();
	}while(numero <= 7);
	return 0;
}

int Menu(){
	/*system("cls");*/
	int pDato;
	tDatos productos; // lo uso para el TAD - INGRESAR PRODUCTO ESTATICO
	printf("\n1- Ingresar Producto \n");
	printf("2- Ingresar Producto estaticos \n");
	printf("3- Eliminar Producto\n");
	printf("4- Mostrar Producto\n");
	printf("5- Guardar archivo y ordenarlo \n");
	printf("6- Mostrar Archivo\n");
	printf("7- Cargar Archivo\n");
	printf("8- Salir\n");
	printf("Opciones: ");
	scanf("%d", &pDato);
	fflush(stdin);
	switch(pDato){
		case 1:// lo hago de forma dinamica
			    ingresarProducto(producto);
		    	break;
		case 2: // elementos estaticos para la preasentacion DESORDENADO
		        strcpy(productos.descripcion,"Gaseosa ");
		        productos.precio=2500;
		        productos.cantidad=5;
		        //1-Comida2-Bebidas3-Limpieza4-Fruta/Verdura5-Productos del hogar
		        productos.tipo=2;
		        ingresarProducto2(productos);
		               
				strcpy(productos.descripcion,"Fuyi ");
		        productos.precio=2000;
		        productos.cantidad=8;
		        productos.tipo=3;
		        ingresarProducto2(productos);
		        		        
				strcpy(productos.descripcion,"Naranjas ");
		        productos.precio=2000;
		        productos.cantidad=8;
		        productos.tipo=4;
		        ingresarProducto2(productos);
		        
				strcpy(productos.descripcion,"HARINA ");
		        productos.precio=2000;
		        productos.cantidad=8;
		        productos.tipo=1;
		        ingresarProducto2(productos);
		        
				strcpy(productos.descripcion,"ACEITE MOTOR");
		        productos.precio=5000;
		        productos.cantidad=2;
		        productos.tipo= 5;
		        ingresarProducto2(productos);
		        		        
				strcpy(productos.descripcion,"Papa ");
		        productos.precio=3000;
		        productos.cantidad=8;
		        productos.tipo=4;
		        ingresarProducto2(productos);
				
				strcpy(productos.descripcion,"Fideos ");
		        productos.precio=2000;
		        productos.cantidad=8;
		        productos.tipo=1;
		        ingresarProducto2(productos);
		        
		        strcpy(productos.descripcion,"Jabon ");
		        productos.precio=2000;
		        productos.cantidad=8;
		        productos.tipo=5;
		        ingresarProducto2(productos);
		        
		        strcpy(productos.descripcion,"Lavandina ");
		        productos.precio=5500;
		        productos.cantidad=8;
		        productos.tipo=5;
		        ingresarProducto2(productos);
		        
				strcpy(productos.descripcion,"MORRON");
		        productos.precio=3000;
		        productos.cantidad=2;
		        productos.tipo=4;
		        ingresarProducto2(productos);
	            break;
		case 3:
			   eliminarProducto();
			   break;
		case 4:
		       mostrarProductos(listaProducto);
			   break;
		case 5:
			   guardarArchivo(listaProducto);
		   	   break;
		case 6:
		    	inicializar();
		    	procesoCorte();
			    finalizar();
			    break;
		case 7:
			    cargarArchivo(producto);
		    	break;
		case 8:    	
			   printf("\n PROGRAMA FINALIZADO!!!\n");
			   break;
	}
	return pDato;
}


void eliminarPrimerProducto() {
	tLista  * nodoSuprimir;
	nodoSuprimir = listaProducto;
	listaProducto = listaProducto->siguiente;/*uso mi elem que es mi varible  de tdatos*/
	printf("\nPrimer elemento eliminado: %s\n", nodoSuprimir->producto.descripcion);
	free( nodoSuprimir );/*libeo el primer elemento*/
	nodoSuprimir = NULL;
}

void eliminarProducto(){// se utliluiza la funcion elieminar K
	tLista * aux;
	tLista * nodoSuprimir;
	int i,k;
	if(listaVacia(listaProducto)){
		printf("\n No hay productos a eliminar\n");
	}else{
		  aux = listaProducto;
		  printf("\n Producto a eliminar en la posicion: \n");
		  scanf("%d", &k);
		  //elimino el primero
		if(k==1){
			eliminarPrimerProducto();
		  }else{
		  
		 // elimino el segundo
		  for(i=1; i<k-1; i++){
			aux = aux->siguiente;
		  }
		  nodoSuprimir = aux->siguiente;
		  aux->siguiente = nodoSuprimir -> siguiente;
		  printf("Producto Eliminado: %s", nodoSuprimir->producto.descripcion);
		  free(nodoSuprimir);
		  nodoSuprimir = NULL;	
		  }
		  
	}
	
}
//la funcion ordena luego guarda
void guardarArchivo(tLista * pLista){
	int i, contar=0;// para contar los productos antes de guadarlos
	PRODUCTOS = fopen("ListaProductos.dat" ,"wb");
	tLista * aux;
	
	if(listaVacia(aux)){
		printf("No hay productos en la lista");
	}else{
		for(i=0; i<6 ; i++){
			aux = pLista;
			while(aux != NULL){
				if(i == aux->producto.tipo){
				
					strcpy(regProducto.Descripcion, aux->producto.descripcion);
					regProducto.Cantidad = aux->producto.cantidad;
					regProducto.Tipo = aux->producto.tipo;
					regProducto.Precio = aux->producto.precio;
					contar=contar+1;
					fwrite(&regProducto, sizeof(registro),1,PRODUCTOS);
				}
				aux = aux->siguiente;
			}
			
			free(aux);
		}
	}
	fclose(PRODUCTOS);
printf("\nProductos guardados!!! %d\n",contar);
}
void cargarArchivo(tDatos pdato){
	tLista * nuevoNodo;
	nuevoNodo = malloc (sizeof(tLista));
	nuevoNodo -> producto;
	
	PRODUCTOS = fopen("ListaProductos.dat", "rb");
	fread(&regProducto, sizeof(registro),1,PRODUCTOS);
	
	while(!feof(PRODUCTOS)){
		strcpy(nuevoNodo->producto.descripcion, regProducto.Descripcion);
		nuevoNodo->producto.cantidad = regProducto.Cantidad;
		nuevoNodo->producto.tipo = regProducto.Tipo;
		nuevoNodo->producto.precio = regProducto.Precio;
		
		nuevoNodo->siguiente = listaProducto;
        listaProducto = nuevoNodo;
        fread(&regProducto, sizeof(registro),1,PRODUCTOS);
    }
	
	fclose(PRODUCTOS);
}

void mostrarArchivo(){
	PRODUCTOS = fopen("ListaProductos.dat", "rb");
	fread(&regProducto, sizeof(registro),1,PRODUCTOS);
	while(!feof(PRODUCTOS)){
		printf("%s \t%d \t %d \t\t\t %2.f\n", regProducto.Descripcion, 
		regProducto.Tipo ,regProducto.Cantidad ,regProducto.Precio );
		fread(&regProducto, sizeof(registro),1,PRODUCTOS);
	}
	fclose(PRODUCTOS);
}

void inicializar(){
	 PRODUCTOS = fopen("ListaProductos.dat", "rb");
	 fread(&regProducto, sizeof(registro),1,PRODUCTOS);
	 codTipoAnt = regProducto.Tipo;
	 totalProductos = 0;
	 
}
void procesoCorte(){
	
	while(!feof(PRODUCTOS)){
		inicioCorte();
		
		while(!feof(PRODUCTOS) && regProducto.Tipo == codTipoAnt){
			unProducto();
			fread(&regProducto, sizeof(registro),1,PRODUCTOS);
		}
		finCorte();
	}
}

void unProducto(){
	printf("\t%s \t%d \t%d \t\t%2.f\n", regProducto.Descripcion , regProducto.Tipo ,regProducto.Cantidad ,regProducto.Precio );
	tipoProductoTotal = tipoProductoTotal + regProducto.Cantidad;
}

void inicioCorte(){
	printf("\tDescripcion\tTipo\tCantidad\tPrecio \n");
	tipoProductoTotal = 0;
}

void finCorte(){
	printf("\nCantidad Total de Productos tipo %d: %d\n", codTipoAnt, tipoProductoTotal);
	totalProductos = totalProductos + tipoProductoTotal;
	codTipoAnt = regProducto.Tipo;
}

void finalizar(){
	printf("\nCantidad Total de Productos: %d\n", totalProductos);
	fclose(PRODUCTOS);
}
