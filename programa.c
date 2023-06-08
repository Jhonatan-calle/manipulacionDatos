/* Proyecto Final Integrador - Algoritmo: IntegradorII 
	Universidad Nacional de Río Cuarto. Facultad de Cs. Exactas, Físico-Químicas Y Naturales, Departamento de Computación.
	Introducción a la Algorítmica y Programación (3300).  
	Autores, Daniel Sebastian Medina, DNI: 43131849, Jhonatan Calle Galeano, DNI: 95665394. */

/*Bibliotecas*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#if defined(_WIN32) || defined (_WIN64)
   #include <windows.h>
#endif

/*Colores*/
#define RESET_COLOR "\x1b[0m"
#define ROJO_T      "\x1b[31m"
#define VERDE_T     "\x1b[32m"
#define AMARILLO_T  "\x1b[33m"
#define AZUL_T      "\x1b[34m"
#define AZUL_F      "\x1b[44m"
#define CYAN_T      "\x1b[36m"
#define CYAN_F      "\x1b[46m"

/*Léxico*/
	#define MaxCadena 30 //Máximo valor que puede almacenar una cadena.
	#define MaxArreglo 1000 //Cantidad de posiciones que puede del arreglo. Significa que tiene 1000 lugares.Desde i0 hasta i999.
typedef struct{ //Tipo creado contiene los datos que se pueden almacenar de un socio. 
		char nombre[MaxCadena];
		int dni;
		int edad;
}TElem;
typedef struct{ //Tipo creado contiene los datos que se pueden almacenar para un archivo.
		char nombre[MaxCadena];
		int dni;
		int edad;
		int borrado;
}TElemArchivo;
typedef TElem TArreglo[MaxArreglo]; //Tipo TArreglo
typedef struct{ //TData
	TArreglo a;
	int cant;
}TData;
typedef struct TDoblete{ //Doblete Lista
	TElem info; //EL campo info es de nombre, dni,edad;
	struct TDoblete *next;
}TLista;

/*Variables que se utilizarán el el algoritmo principal*/
TData arr; //arreglo
TElem nuevo; 
TLista *pun; //puntero a TLista
int rta,op,pos,i,n,dni; 
FILE* file; 
FILE* g; //Archivo

/*Perfiles de funciones y acciones*/
int Vacia (TData a);
int Llena (TData a);
void InsertarFinal(TData *a, TElem dat);
void SuprimirPrimero (TData *a);
void Mostrar (TData a);
void AgregarDatosArreglo (TData *a, FILE* f, int MaxArr);
void AgregarDatosArchivo (TData a, FILE* *g);
void BusquedaPorDni (TData a, int *dni);
int MayoresAlPrimero (TData a);
void Ordenar(TData *a);
TLista* MostrarMenores(TData a, TLista* pun,int n);
int mayor(TData a, int i);

/*Inicio del algoritmo principal*/
int main(){
	printf(CYAN_F "Bienvenido al programa para cargar socios" RESET_COLOR "\n");
	//El archivo se abre cuando inicia el programa y se cierra cuando finaliza este.
	file = fopen("personas.dat","r+b"); //Se abre el archivo binario en modo de lectura.
	if (file!=NULL){ //si se pudo abrir
		printf(VERDE_T "Se abrió correctamente el archivo ""personas.dat""" RESET_COLOR "\n"); 
	}
	else{ //si no se pudo abrir
		printf(ROJO_T "No se pudo abrir, error: %s" RESET_COLOR "\n",strerror(errno));
	}
	AgregarDatosArreglo(&arr,file,MaxArreglo);
	do{
		do{
			printf(AZUL_F "   Menú de opciones.   " RESET_COLOR "\n");
			printf(AZUL_T "1.-" RESET_COLOR "Insertar al final.\n");
			printf(AZUL_T "2.-" RESET_COLOR "Suprimir el primero.\n");
			printf(AZUL_T "3.-" RESET_COLOR "Mostrar todos.\n");
			printf(AZUL_T "4.-" RESET_COLOR "Mostrar menores.\n");
			printf(AZUL_T "5.-" RESET_COLOR "Buscar por DNI.\n");
			printf(AZUL_T "6.-" RESET_COLOR "Mayores al primero.\n");
			printf(AZUL_T "7.-" RESET_COLOR "Edad mayor.\n");
			printf(AZUL_T "8.-" RESET_COLOR "Guardar y salir.\n");
			printf(CYAN_T "Ingrese una opción para continuar:" RESET_COLOR "\n");
			scanf("%i",&op);
			getchar();
			if ((op<1) || (op>8)){
				printf(ROJO_T "El número ingresado no es válido. Ingrese nuevamente" RESET_COLOR "\n");
			}
	} while (!((op>=1) && (op<=8)));		
		if (op==1){
			system("cls||clear"); //Limpia el terminal de linux o windows
			if (Llena(arr)){
				printf(AMARILLO_T "No se pueden ingresar más nombres. La lista está completa" RESET_COLOR "\n");
			}else{
				printf("Ingrese el nuevo nombre a insertar en la lista de socios\n"); scanf("%s", nuevo.nombre); getchar();
				printf("Ingrese el dni de %s \n",nuevo.nombre); scanf("%i",&nuevo.dni);  getchar();
				printf("Ingrese la edad de %s\n",nuevo.nombre); scanf("%i",&nuevo.edad); getchar();
				InsertarFinal(&arr,nuevo);
			}
		} else if (op==2){
			system("cls||clear"); //Limpia el terminal de linux
			SuprimirPrimero(&arr);
		} else if (op==3){
			system("cls||clear"); //Limpia el terminal de linux
			Mostrar(arr);
		}else if (op==4){
			system("cls||clear"); //Limpia el terminal de linux
			n=0; //Precondicion para que funcione la recursividad
    	pun=NULL;
    	pun = MostrarMenores(arr,pun,n);
    	if (pun==NULL){
      	printf(AMARILLO_T "No hay menores de edad para mostrar" RESET_COLOR "\n");
    	}else{
    			printf(CYAN_T "Mostrando menores de edad:" RESET_COLOR "\n");
      			while(pun!=NULL){
        			printf("Nombre:%s\n",pun->info.nombre);
  			      printf("DNI:%i\n",pun->info.dni);
        			printf("Edad:%i\n",pun->info.edad);
							printf(CYAN_T "--------------------------- " RESET_COLOR "\n");
        			pun=pun->next;
      			}	
    		}
		} else if (op==5){
			system("cls||clear"); //Limpia el terminal de linux
				if (Vacia(arr)){
					printf(AMARILLO_T "No hay elementos en la lista de socios. No se puede buscar." RESET_COLOR "\n");
				}else{
					Ordenar(&arr); //El arreglo debe estar ordenado y no vacío para buscar dicotomicamente.
					BusquedaPorDni(arr,&dni);
				}
		}else if (op==6){
			system("cls||clear"); //Limpia el terminal de linux
			rta = MayoresAlPrimero(arr);
			if (rta==1){
				printf("Hay 3 o más socios mayores que el primero de la lista.\n");
			} else {
				printf("No hay 3 socios mayores que el primero de la lista.\n");
			}
		} else if (op==7){ 
			system("cls||clear"); //Limpia el terminal de linux
			if (Vacia(arr)){
				printf(AMARILLO_T "La lista está vacía. No se puede calcular el mayor"RESET_COLOR "\n");
			}else{
				arr.cant=arr.cant-1; //precondicion para funcion mayor
				i=0; //Inicializar el i en 0 para que funcione correctamente funcion mayor.
				pos = mayor(arr,i);
				printf("El/La mayor es %s y tiene %i años \n",arr.a[pos].nombre, arr.a[pos].edad);
				arr.cant=arr.cant+1; //Dejo la cantidad como estaba
			}
		}else if (op==8){ 
			AgregarDatosArchivo(arr, &g);
			errno = fclose(file); //Cerrar el archivo f
			if (errno==0) {
				printf(VERDE_T "El archivo se cerró correctamente." RESET_COLOR "\n");
			} else{
				printf(ROJO_T "Error en el cierre del archivo. \n Error: %s" RESET_COLOR "\n", strerror(errno));
			}
			printf(VERDE_T "Se guardaron los datos correctamente en el nuevo archivo." RESET_COLOR "\n");
			printf(CYAN_F "El programa ha finalizado." RESET_COLOR "\n");
		}
		} while (!(op==8)); 
	return 0;
}

/*Función vacia, devuelve 1 si el arreglo está vacío y devuelve 0 si no lo está*/
int Vacia (TData a){
/*Inicio*/
	if (a.cant==0) {
		return 1; //Está vacía
	}else{
		return 0; //No está vacía
	}
}

/*Función llena, retorna 1 si el arreglo está completo y retorna 0 si no lo está*/
int Llena (TData a){  //m representa el maximo del arreglo y se recibe como parametro.
/*Léxico local*/
	int m;
/*Inicio*/
	m=MaxArreglo;
	if (a.cant == m){
		return 1; //Está completo
	}else{
		return 0; //No está completo
	}
}

/*Acción InsertarFinal, recibe el arreglo y el dato nuevo a ingresar como parametro, y lo ingresa al final del arreglo*/
void InsertarFinal(TData *a, TElem dat){
/*Inicio*/
		(*a).a[(*a).cant] = dat;//Se carga el nuevo socio en el arreglo.
		(*a).cant = (*a).cant+1; //Se incrementa una unidad en la cantidad.
		printf(VERDE_T "%s se agregó correctamente al final de la lista de socios" RESET_COLOR "\n",dat.nombre);
}

/*Accion SuprimirPrimero, recibe el arreglo como parámetro y elimina la primer posición*/
void SuprimirPrimero (TData *a){
/*Léxico local*/
	int i;
	TElem aux;
/*Inicio*/
	if (Vacia(*a)){ //si está vacía, no se puede eliminar
		printf(AMARILLO_T "No se puede eliminar ya que la lista de socios está vacía." RESET_COLOR "\n");
	}else{
		i=0;
		aux = (*a).a[0]; //Para mostrar quién se eliminó de la lista.
		while (i<(*a).cant){
			(*a).a[i] = (*a).a[i+1]; //Cambia de posición el nombre en el arreglo.
			i++; 
		}
		(*a).cant = (*a).cant-1; //Se decrementa una unidad.
		printf(ROJO_T "Se ha eliminado a %s de la lista de socios" RESET_COLOR "\n",aux.nombre);
	}
}

/*Acción Mostrar, visualiza por pantalla los elementos del arreglo*/ 
void Mostrar (TData a){
/*Léxico local*/
	int i;
/*Inicio*/
	if (Vacia(a)){ //Si está vacía no muestra
		printf(AMARILLO_T "No hay elementos para mostar. La lista está vacía." RESET_COLOR "\n");
	} else{
		i=0;
		printf(CYAN_T "Mostrando la lista de socios:" RESET_COLOR "\n");
		while (i<a.cant){
			printf("Nombre:%s\n",a.a[i].nombre);
			printf("DNI:%i\n",a.a[i].dni);
			printf("Edad:%i\n",a.a[i].edad);
			printf(CYAN_T "--------------------------- " RESET_COLOR "\n");
			i=i+1;
		}
	}
}

/*En esta acción se agregan datos al arreglo desde un archivo que será pasado como dato en un parametro*/

void AgregarDatosArreglo (TData *a, FILE* f, int MaxArr){
/*Léxico local*/
	int cant,i;
	TElemArchivo aux;
/*Inicio*/
		(*a).cant =0;
		cant=0;
		while(fread(&aux,sizeof(TElemArchivo),1,f) != 0 ){  //mientras no sea el final del archivo
			if (aux.borrado == 0) { //si el campo borrado es falso
				cant=cant+1; //Contador de registros validos para el arreglo.
			}
		}
		if (cant>MaxArr){
			printf(AMARILLO_T "No se cargarán todos los socios, ya que la cantidad de socios excede la capacidad máxima." RESET_COLOR "\n");
		}
		fseek (f,0,SEEK_SET); //Reubica el cursor en el primer registro posición 0
		i=0;//Ubicar el i para cargar desde primera posición.
		while((fread(&aux,sizeof(TElemArchivo),1,f) != 0 )&&(i<MaxArr)){  //mientras no sea el final del archivo
			if (aux.borrado == 0) { //si el campo borrado es falso
				strcpy((*a).a[i].nombre, aux.nombre); //copiar en el arreglo
				(*a).a[i].edad = aux.edad;
				(*a).a[i].dni=aux.dni;
				(*a). cant = (*a).cant+1; //Si se agrega uno nuevo se incrementa la cantidad.
				printf(CYAN_T "%s se agregó a la lista de socios." RESET_COLOR "\n",(*a).a[i].nombre);
				i=i+1;
			}
		}
}


/*En esta acción se agregan datos al archivo desde un arreglo que será pasado como resultado en un parametro*/
void AgregarDatosArchivo (TData a, FILE* *g){
/*Léxico local*/
	TElemArchivo aux; 
	int errno,i;
/*Inicio*/
	*g = fopen("nuevo.dat","w+b"); //Se crea un nuevo archivo para cargar los datos del arreglo.
		if (*g!=NULL) {
			printf(VERDE_T "Se creó correctamente el archivo ""nuevo.dat""" RESET_COLOR "\n");
		} else{
				printf(VERDE_T "Error en la apertura \n Error: %s" RESET_COLOR "\n" ,strerror(errno));
		}
	if (Vacia(a)){ //Si no hay socios cargados
		printf(AMARILLO_T "No se agregaron datos al archivo. No hay socios cargados." RESET_COLOR "\n");
	}
		i=0;	
		while (i<a.cant) { 
			strcpy(aux.nombre, a.a[i].nombre);
			aux.dni = a.a[i].dni;
			aux.edad = a.a[i].edad;
			aux.borrado=0; //El borrado es verdadero para ingresar al archivo
			fwrite(&aux, sizeof(aux),1,*g);
			i++;
		}
		fclose(*g);
}

/*Está accion busca el dni a través de la búsqueda binaria(El arreglo debe estar ordenado)*/
void BusquedaPorDni (TData a, int *dni){
/*Léxico local*/
	int k,inf,sup;
/*Inicio*/
		printf(AMARILLO_T "La lista de socios está ordenada por DNI" RESET_COLOR "\n");
		printf("Ingrese el dni a buscar\n");
		scanf("%i",&(*dni));
		if ((*dni<a.a[0].dni) || (*dni>a.a[a.cant-1].dni)){   //Mientras este dentro del rango de la primer y última posición
			printf(AMARILLO_T "El dni no se encuentra en la lista" RESET_COLOR "\n"); 
		} else if ((a.a[0].dni <= *dni) && (*dni <= a.a[a.cant-1].dni)){
			inf = 0;
			sup = a.cant-1;  //Ya que empieza desde la pos 0;
			while ((inf<sup)) {
				k = (inf+sup)/2;
				if	(*dni>a.a[k].dni){ 
					inf = k+1; //Der
				} else if (*dni<=a.a[k].dni){
					sup = k; //izq
				}
			}
			if (a.a[inf].dni == *dni){ 
				printf(VERDE_T "Se encontró la persona con el mismo DNI:" RESET_COLOR "\n");
				printf("Nombre: %s \n",a.a[inf].nombre); 
    			printf("DNI: %i \n",a.a[inf].dni);
    			printf("Edad: %i \n",a.a[inf].edad);
			}else if (a.a[inf].dni != *dni){
	 			printf(AMARILLO_T "No se encontró persona con ese DNI" RESET_COLOR "\n");
			}
		}
}

/*Funcion MayoresAlPrimero determina si hay 3 o más personas en el arreglo que sean de mayor edad que el primero del arreglo*/
int MayoresAlPrimero (TData a){
/*Léxico local*/
	#define Max 3
	int i,cantMay;
/*Inicio*/
	if (a.cant == 0){
		return 0;
	} else if (a.cant!=0){
			cantMay = 0;
			i=1; //Desde segunda posición
			while (i<a.cant){
				if (a.a[i].edad > a.a[0].edad){
					cantMay=cantMay+1;
				}
				i++;
			}
	if (cantMay >= Max){
		return 1;
	}else{
		return 0;
	}
	}
}

/*Acción Ordenar, ordena los elementos del arreglo de menor a mayor por DNI mediante el método insertion sort*/
void Ordenar(TData *a){ 
/*Léxico local*/	 
	int i,j;
	TElem aux;
/*Inicio*/
	i=1; //i comienza en 1 porque empezamos así empezariamos desde la segunda posicion del arreglo, como lo requiere insertion sort
	while ((i<(*a).cant)){
		aux = (*a).a[i];
		j = i-1;
		while ((j>=0) && ((*a).a[j].dni>aux.dni)){ //Cambia la condicion,ahora es menor igual que 0 con respecto a insertion sort.
			(*a).a[j+1] = (*a).a[j];	
			j=j-1;
		}
		(*a).a[j+1] = aux;
		i=i+1;
	}
}

/*Función que determina la posicion en el arreglo de la persona mas grande para despues ser mostrada en el algoritmo principal
en el caso de haber dos con la misma edad sólo muestra el último que ingresó a la lista*/
int mayor(TData a, int i){
/*Inicio*/
	if(a.cant==0){  
		return (i);
	}else if (a.cant>0){
		if (a.a[a.cant].edad>a.a[i].edad){
 			i = a.cant;
        }
        a.cant = a.cant-1;
        mayor(a,i);
	}
}

/*Función que calcula recursivamente y devuelve una lista simplemente encadenada con los menores de edad*/
TLista* MostrarMenores(TData a, TLista* pun,int n){
  TLista* aux;
  if (n>a.cant){
     return pun;
  }else{
    if (a.a[n-1].edad < 18)
    {
      aux = (TLista*) malloc (sizeof(TLista));
      strcpy(aux->info.nombre,a.a[n-1].nombre);
      aux->info.dni = a.a[n-1].dni;
      aux->info.edad = a.a[n-1].edad;
      aux->next=pun;
      pun=aux;
    }
    MostrarMenores(a,pun,n+1);
  }
 }