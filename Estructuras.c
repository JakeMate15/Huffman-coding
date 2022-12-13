//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Diciembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Funciones/Operaciones para la codificación de Huffman
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include"Estructuras.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
  Imprime el valor de un elemento:
  --------------------------------
  Argumentos:
  Par p: contiene la infomración del elemento extraído del arreglo
*/
void imprimePar(Par p){
    printf("%d %lld\n",p.valor, p.repeticiones);
}

/*
  Describe la navegación en el arbol
  ----------------------------------
  Argumentos:
  int a[]: navegación almacenada
  int n: longitud que lleva
  FILE *arch: archivo de escritura
  Variables a utilizar:
  int i: utilizada para los loops 
*/
void imprimeArregloEnteros(int a[], int n, FILE *arch){
    int i;
    //Va recorriendo todo el número de bits que está pasando el árbol
    for(i=0; i<n; i++){
        if(arch == NULL) printf("%d",a[i]);
        else fprintf(arch,"%d",a[i]);
    }

    fprintf(arch, "\n");
}

/*
  Función que saca el tamaño del archivo
	--------------------------------------
	Argumentos:
	char *arch: contiene la ruta del archivo a analizar 
	Variables utilizadas:
	FILE *archivo: tipo de dato para abrir el archivo y extraer la información
  *return* ll res: devuelve la posición del puntero del archivo (tamaño del archivo)
*/
ll tamArch(char* arch){
    //Abrimos el archivo en modo lectura
    FILE* archivo = fopen(arch,"r");

    if(archivo==NULL){
        printf("No se pudo abrir el archivo\n");
        return -1;
    }

    /*Recorre el puntero de lectura del archivo de inicio a fin
    Agrumentos:
    - archivo: archivo de análisis
    - inicio de la posición
    - SEEK_END constante para señalar el final del archivo
    */
    fseek(archivo,0L,SEEK_END);
    //Devuelve la posición en la que se encuentra el archivo, que será el tamaño del contenido del archivo
    ll res = ftell(archivo);
    //Cerramos el archivo
    fclose(archivo);

    return res;
}

/*
  Proceso para inicializar todo nuestro diccionario con el valor de -1 
	--------------------------------------------------------------------
	Argumentos:
	Pares tablaFrecuencias: estructura que guarda información (carácter/elemento y el no. repeticiones del mismo elemento) 
	Variables utilizadas:
	int i: utilizada para el loop
*/
void arregloPares(Pares tablaFrecuencias){
    int i;

    for(i=0; i<256; i++){
        tablaFrecuencias[i].repeticiones = -1;
    }
}

/*
  Función para sacar la tabla de frecuencias, el tamaño de elementos a comprimir y la obtención del contenido del archivo
	--------------------------------------------------------------------
	Argumentos:
	char * archivo: contiene la ruta del archivo a comprimir
  Pares tablaFrecuencias: nuestro diccionario para guardar los elementos y la cantidad de repeticiones del mismo
  ll *tam: guarda el tamaño de bytes del archivo
	Variables utilizadas:
	FILE *arch: tipo de dato para abrir el archivo y extraer la información
  *return* uc* lectura: devuelve el contenido extraído del archivo
  ll i: utilizada para el loop
  int n: para identificar el byte que es.
*/
uc* frecuencias(char* archivo, Pares tablaFrecuencias, ll* tam){
    //Declaración de funciones
    FILE* arch;
    uc* lectura;
    ll i;
    int n;

    //Sacamos el tamaño del archivo
    *tam = tamArch(archivo);
    
    //Asignamos la memoria para poder guardar los elementos del archivo
    lectura = (unsigned char*) malloc(sizeof(ll) * (*tam));
    if(lectura==NULL){
        printf("No hay memoria disponible para el arreglo");
		exit(1);
    }

    //Abrimos el archivo en modo lectura binaria
    arch = fopen(archivo,"rb");

    /*Recoge toda la información del archivo
    Argumentos:
    - lectura: variable en la que se va a guardar el archivo
    - *tam: valor que contiene el tamaño del archivo, por lo tanto el contenido a leer
    - arch: archivo a leer
    */
    fread(lectura,(*tam),1,arch);

    //Recorre todo el contenido obtenido y va registrando las repeticiones en nuestro diccionario de elementos
    for(i=0; i<(*tam); i++){
        //Ve el byte que es
        n = lectura[i];
        
        //Si no hay registro del elemento, registra el valor e incializa la repetición como 1, en caso de que haya registro va incrementando el no. de repeticiones
        if(tablaFrecuencias[n].repeticiones==-1){
            tablaFrecuencias[n].repeticiones = 1;
            tablaFrecuencias[n].valor = n;
        }
        else{
            tablaFrecuencias[n].repeticiones++;
        }
    }

    //Cerramos el archivo
    fclose(arch);

    return lectura;
}

/*
	Algoritmo de ordenamiento "quickSort" (Función recursiva que se encarga de dividir el arreglo con ayuda del pivotes para ir ordenando)
	------------------------------------------
	Argumentos:
	Pares A, estructura para ordenar conforme a las repeticiones
	int p, posición inicial del arreglo
	int r, posición final del arreglo/tamaño del arreglo
	Variables utilizadas:
	int j, posición del pivote asignado
*/
void quickSort(Pares A, int p, int r){
	int j; //La variable será la parte intermediaria del arreglo
	if(p < r){
		//Asigna el pivote con tal de que los elementos más pequeños están a la izquierda y los mayores a la derecha
		j = pivot(A, p, r);
		quickSort(A, p, j-1);
		quickSort(A, j+1, r);
	}
}

/*
	Algoritmo de ordenamiento "quickSort" (Función que asigna el pivote e intercambia la posición de manera que en el lado izquierdo esten los números menores y en el lado derecho esten los número mayores al pivote)
	------------------------------------------
	Argumentos:
	Pares A, estructura para ordenar conforme a las repeticiones
	int p, posición inicial del arreglo
	int r, posición final del arreglo/tamaño del arreglo
	Variables utilizadas:
	ll piv, valor del pivote asignado en la posición incial
	int i, variable auxiliar asignada en la posición inicial
	*return* int j, variable auxiliar asignada en la posición final y será retornada como la posición que retoma el pivote
*/
int pivot(Pares A, int p, int r){
	//Declaramos el pivote desde el inicio
	ll piv = A[p].repeticiones;
    int i = p, j = r;
	//Mientras no se crucen los indices
	while(i < j){
		//Va recorriendo la posición inicial hacia la derecha cuando el pivote siga siendo mayor o igual al número a comparar, así mismo también verifica que los indices no colisionen
		while(A[i].repeticiones <= piv && i < j){
			i++;
		}
		//Va recorriendo el numero de final a la izquierda cuando el pivote es menor al número a comparar
		while(A[j].repeticiones > piv){
			j--;
		}
		//Verificamos si todavía no se cruzan los indices y se intercambian las posiciones en donde se hayan quedado los dos anteriores loops
		if(i < j){
			intercambiar(A, i, j);	
		}
	}
	//En cuyo caso de que se hayan cruzado, ponemos el pivote en el lugar que le corresponde
	intercambiar(A, p, j);
	//Regresamos la posición en donde quedo, que será el pivote
	return j;
}

/*
	Algoritmo de ordenamiento "quickSort" (Función que sólo realiza el intercambio de números)
	------------------------------------------
	Argumentos:
	Pares A, estructura conforme a las repeticiones a ordenar
	int i, posición 1 a intercambiar
	int j, posición 2 a intercambiar
	Variables utilizadas:
	int temp, variable auxiliar para poder intercambiar el valor sin que se pierda su valor
*/
void intercambiar(Pares A, int i, int j){
	Par temp = A[j];
	A[j] = A[i];
	A[i] = temp;
}

/*
  Verifica cuantos bytes fueron encontrados en el archivo
	-----------------------------------------------------------
	Argumentos:
	Pares A: estructura que referencia al diccionario de elementos extraídos del archivo
	Variables utilizadas:
	*return* int res: devuelve la variable que guarda la cantidad de bytes identificados en el archivo
  int i: utilizada para el loop
*/
int elementosTabla(Pares tablaFrecuencias){
    int res=0;
    int i;

    //Recorre el diccionario
    for(i=0; i<256; i++){
        //En caso de que el número de repeticiones sea mayor a 0 suma el contador
        if(tablaFrecuencias[i].repeticiones>0){
            res++;
        }
    }

    return res;
}

/*
  Pasa en la nueva la información encontrada en el archivo
  --------------------------------------------------------
  Argumentos:
  Pares tablaFrecuencias: estructura que trae la posibilidad de tener valores nulos y la encontrada en el archivo
  Pares nuevaTabla: estructura en donde sólo se guardará la información encontrada en el archivo
*/
void tablaConUtiles(Pares tablaFrecuencias, Pares nuevaTabla, int n){
    int aux=0;
    int i;

    for(i=0; i<256; i++){
        if(tablaFrecuencias[i].repeticiones>0){
            nuevaTabla[aux] = tablaFrecuencias[i];
            aux++;
        }
    }
}

/*
  Imprime la tabla de frecuencias (prueba)
  ----------------------------------------
  Argumentos:
  Pares tablaFrecuencias: contenido sacada del archivo a comprimir
  int n: número de elementos
  Variables a utilizar:
  int i: utilizada para los loops
  int valorTF: valor decimal del elemento
  int n_bits: número de bits
  uc num: valor en unsigned char del elemento
*/
void imprimeTablaFrecuencias(Pares tablaFrecuencias, int n){
    int i,valorTF,n_bits;
    uc num;

    printf("BIN\tRep\n");
    //printf("NumDec\tASCII\tBIN\tRep\n");

    for(i=0; i<n; i++){
        
            valorTF = tablaFrecuencias[i].valor;
            num = valorTF;
            n_bits = sizeof(num)*8;
            

            //printf("%d\t%c\t",valorTF,valorTF);
            imprimeBits(n_bits,num, NULL);
            printf("\t%lld\n",tablaFrecuencias[i].repeticiones);

    }
}

/*
  Imprime los bits del elemento encontrado
  ----------------------------------------
  Argumentos:
  int n_bits: escritura de 8 elementos
  uc: elementos a escribir en bits
  FILE *arch: archivo a la que se le va a hacer la escritura
  Variables a utilizar:
  int i: utilizada para los loops
*/
void imprimeBits(int n_bits, uc numero, FILE *arch){
    int i;

    //Va consultando bit por bit y lo va escribiendo
    for (i=n_bits-1; i>=0; i--)
    	if(arch == NULL) printf("%d",CONSULTARBIT(numero,i));
    	else fprintf(arch ,"%d",CONSULTARBIT(numero,i));
}

/*
	Creación de un nodo metiendo el contenido del elemento (Estructura Par)
	----------------------------
	Argumentos:
	Par datos: estructura que contiene el elemento y el no de repeticiones
	Variables utilizadas:
	*return* NODO aux: devolverá el nodo que contendrá la información de un elemento
*/
NODO nuevoNodo(Par datos){
    //Asignamos memoria
    NODO aux = (NODO)malloc(sizeof(Nodo));
    if(aux == NULL){
        printf("No se ha creado el nodo\n");
        exit(0);
    }
    //Inicializamos variables donde sus ramas serán NULL
    aux->izquierdo = aux->derecho = NULL;
    //Se mete la información de la estructura Par
    aux->info.repeticiones = datos.repeticiones;
    aux->info.valor = datos.valor;

    //imprimePar(datos);

    return aux;
}

/*
	Creación de estructura árbol
	----------------------------
	Argumentos:
	int capacidad: el número de elementos diferentes extraídos del archivo y así crear un número de nodos a utilizar para después realizar su barrido
	Variables utilizadas:
	*return* ARBOL aux: devolverá el una estructura ARBOL inicial, con el número de nodos a utilizar que será igual al número de elementos diferentes a analizar
*/
ARBOL creaArbol(int capacidad){
    //Creamos el ARBOL padre
    ARBOL aux = (ARBOL)malloc(sizeof(Arbol));
    if(aux == NULL){
        printf("No se ha creado el arbol\n");
        exit(0);
    }

    //Instanciamos valores iniciales
    aux->tam = 0;
    //Número de elementos a analizar
    aux->capacidad = capacidad;
    //Se crea los n nodos necesarios para poder analizar
    aux->nodos = (NODO*)malloc(aux->capacidad*sizeof(NODO));

    //printf("%d\t%d\n",aux->tam,capacidad);

    return aux;
}

/*
	Función que realiza intercambio de nodos
	----------------------------------------
	Argumentos:
	NODO *a: primer nodo a intercambiar
  NODO *b: segundo nodo a intercambiar
	Variables utilizadas:
	NODO aux: variable auxiliar para no perder su valor
*/
void intercambioNodos(NODO* a, NODO* b){
    NODO aux = *a;
    *a = *b;
    *b = aux;
}

/*
  Algoritmo recursivo para reubicar un nodo
  -----------------------------------------
  Argumentos:
  ARBOL a: estructura árbol que contiene nuestra información de los elementos
  int indice: posición de nuestro nodo
*/
void intercambioActualMin(ARBOL a, int indice){
  //Inicializamos variables (la posición de nuestro nodo izquierdo y derecho)
    int min = indice;
    int izq = 2*indice+1;
    int derecha = 2*indice+2;

    //En caso de que haya un valor menor en uno de sus nodos hijos se le asigna como el mínimo
    if( izq < a->tam && 
        a->nodos[izq]->info.repeticiones < a->nodos[min]->info.repeticiones){
        min = izq;
    }

    if(derecha < a->tam && a->nodos[derecha]->info.repeticiones < a->nodos[min]->info.repeticiones){
        min = derecha;
    }

    //Mientras haya cambiado el mínimo se hace el intercambio y se repite el proceso
    if(min!=indice){
        intercambioNodos(&a->nodos[min],&a->nodos[indice]);
        intercambioActualMin(a,min);
    }
}

/*
  Verifica que aún haya nodos a analizar
  --------------------------------------
  Argumentos:
  ARBOL a: estructura padre que contiene toda la información de los elementos del archivo
  Variables a utilizar
  *return* valor booleano para corroborar si todavía se tiene que manipular el ARBOL o sí ya está en su estado final
*/
int esTam1(ARBOL a){
    return (a->tam==1);
}

/*
  Función que extraé el nodo raíz del Heap de Mínimos
  ---------------------------------------------------
  Argumentos:
  ARBOL a: estructura arbol que contiene nuestra información de los elementos
  Variables a utilizar:
  *return* NODO aux: será el mínimo extraído del heap de mínimos
*/
NODO extraeMin(ARBOL a){
    NODO aux = a->nodos[0];
    a->nodos[0] = a->nodos[a->tam-1];

    //Vuelve a reacomodar el HEAP de mínimos
    --a->tam;
    intercambioActualMin(a,0);

    return aux;
}

/*
  Función que inserta un NODO en el heap de mínimos
  -------------------------------------------------
  Argumentos:
  ARBOL a: estructura padre que contiene toda la información
  NODO n: NODO que queremos insertar
  Variables utilizadas:
  int i: variable utilizada para el loop
*/
void inserta(ARBOL ar, NODO n){
    ++ar->tam;
    int i = ar->tam-1;

    //Acomodamos el valor en el HEAP de mínimos
    while(i && n->info.repeticiones < ar->nodos[(i-1)/2]->info.repeticiones){
        ar->nodos[i] = ar->nodos[(i-1)/2];
        i=(i-1)/2;
    }

    ar->nodos[i] = n;
}

/*
  Construye un Heap de Mínimos inicial
  ------------------------------------
  Argumentos:
  ARBOL a: estructura que contiene la información a organizar
*/
void construye(ARBOL a){
    int n = a->tam - 1;
    int i;
 
    for (i = (n - 1) / 2; i >= 0; --i){
        intercambioActualMin(a, i);
    }
        
}

/*
  Verifica si es un elemento como tal
  -----------------------------------
  Argumentos: 
  NODO raiz: estructura que contiene información a verificar
  return valor booleano si hay existencia de otros elementos
*/
int esHoja(NODO raiz){
    return !(raiz->izquierdo) && !(raiz->derecho);
}

/*
	Creación de estructura árbol
	----------------------------
	Argumentos:
	int capacidad: el número de elementos diferentes extraídos del archivo y así crear un número de nodos a utilizar para después realizar su barrido
	Variables utilizadas:
	*return* ARBOL aux: devolverá el una estructura ARBOL inicial, con el número de nodos a utilizar que será igual al número de elementos diferentes a analizar
*/
ARBOL construyeArbolRep(Pares datos, int n){
    //Creamos el ARBOL padre inicial que contendrá los n nodos a analizar
    ARBOL ar = creaArbol(n);
    int i;

    //Voy llenando de información al ARBOL obtenida de la estructura Par
    for(i=0; i<n; ++i){
        ar->nodos[i] = nuevoNodo(datos[i]);
    }
    
    ar->tam = n;
    //Organiza como un Heap de mínimos
    construye(ar);

    return ar;
}

/*
  Crea el árbol de huffman, organizandolo conforme al número de repeticiones
  --------------------------------------------------------------------------
  Argumentos:
  Pares datos: estructura que contiene la información extraída del archivo
  int n: referencia el tamaño de elementos encontrados en el archivo
  Variables utilizadas:
  NODO izq; variable auxiliar para referenciar el primer elemento mínimo
  NODO der: variable auxiliar para referenciar el segundo elemento mínimo
  NODO superior: variable que será la intersección de los dos anteriores
  ARBOL a: estructura padre que contiene toda la información de los elementos del archivo
*/
NODO construyeArbolHuffman(Pares datos, int n){
    NODO izq;
    NODO der;
    NODO superior;

    ARBOL a = construyeArbolRep(datos,n);

    while(!esTam1(a)){
      //Extrae los dos mínimos
        izq = extraeMin(a);
        der = extraeMin(a);

      //Sera nuestra información intermedia que contendrá el número de repeticiones de los dos números analizados
        Par p;
        p.valor = 36;
        p.repeticiones = izq->info.repeticiones + der->info.repeticiones;

      //Lo meto dentro de una estructura NODO
        superior = nuevoNodo(p);

      //Asignamos la parte derecha y la parte izquierda
        superior->izquierdo = izq;
        superior->derecho = der;

      //Lo insertamos en el heap
        inserta(a,superior);
    }

    //Devolvemos el NODO que contiene todo el arbol de HUFFMAN
    return extraeMin(a);
}

/*
  Algoritmo recursivo para generar nuestro archivo "tabla de frecuencias"
  -----------------------------------------------------------------------
  Argumentos:
  NODO raiz: estructura nodo que contiene la información a manipular
  int *a: seguimiento en bits sobre el árbol
  int tope: el número de bits que se ha llegado dentro del árbol
  Cadena *dic: variable de almacenar información de la navegación de bits
  int *max: es el número de longitud máxima que se logra formar en el árbol
  FILE *nombreArch: archivo a la que se está escribiendo los datos
*/
void imprimeCodigos(NODO raiz, int *a, int tope, Cadena *dic, int *max, FILE *nombreArch){
  //Asigna la longitud máxima de bits formado si se llega a cumplir
    if(tope>(*max))    *max = tope;

  //En el camino del lado izquierdo se le asigna un cero y va haciendo recursividad en ese camino
    if(raiz->izquierdo){
        a[tope] = 0;
        imprimeCodigos(raiz->izquierdo, a, tope+1,dic,max, nombreArch);
    }

  //En el camino del lado derecho se le asigna un uno y va haciendo recursividad en ese camino
    if(raiz->derecho){
        a[tope] = 1;
        imprimeCodigos(raiz->derecho, a, tope+1,dic,max, nombreArch);
    }

  //En caso de que sea elemento escribe la información
    if(esHoja(raiz)){
      //Escribe el número de repeticiones
        fprintf(nombreArch,"%lld\t", raiz->info.repeticiones);
      //Escribe el byte formado
        imprimeBits(8,raiz->info.valor, nombreArch);
        fprintf(nombreArch,"\t");
        //Escribe el valor en decimal
        fprintf(nombreArch, "%d\t", raiz->info.valor);
        //Escribe la navegación del arbol
        imprimeArregloEnteros(a,tope, nombreArch);
        //Función de copia de la información de la navegación de bits
        arrToString(a,dic[raiz->info.valor].cad,tope);
    }
}

/*
  Saca como resultante un archivo con nuestro diccionario "Tabla de Frecuencias"
  ------------------------------------------------------------------------------
  Argumentos:
  Pares datos: estructura que contiene la información extraída del archivo
  int n: referencia el tamaño de elementos encontrados en el archivo
  Cadena *dic:
  Variables utilizadas:
  int a[100]
*/
void generaDiccionario(Pares datos, int n, Cadena *dic, int *max, char *nombreArch){
    //Obtenemos el arbol de Huufman
    NODO raiz = construyeArbolHuffman(datos,n);
    int a[100], tope = 0;
    FILE *arch = fopen(nombreArch, "w");
    //Generamos nuestro archivo de tabla de frecuencias
    imprimeCodigos(raiz,a,tope,dic,max, arch);
    fclose(arch);
}

/*
  Función de hacer guardar información de la navegación del elemento
  ------------------------
  Argumentos: 
  int *arr: arreglo sobre la navegación sobre el arbol
  char *s: cadena donde tiene la información del elementos
  int n: el número de elementos
  Variables utilizadas:
  int i: utilizada para los loops
  int inidice: valor indexado del elementos
*/
void arrToString(int *arr, char* s, int n){
    int i=0;
    int indice = 0;

    for (i=0; i<n; i++){
        indice += sprintf(&s[indice], "%d", arr[i]);
    }

}

/*
  Recolecta la información de nuestra tabla de frecuencias
  --------------------------------------------------------
  Argumentos: 
  char * destino: cadena a la que se va a concatenar
  size_t tam: longitud a la que se va a manipular
  uc * contiene el contenido/elementos del archivo
  Cadena *diccionario: contiene la navegación de nuestros elementos
  size_t cantCad: tamaño de elementos de manipulación
*/
void concatena(char *destino, size_t tam, uc* lectura, Cadena* diccionario, size_t cantCad){

  //Realiza diagnostico sobre si hay error en la manipulación de la expresión, aborta el programa en caso de que lo haya
    assert(tam>0);
    
    tam--;
    char *p = destino;
    int i=0;


    //Obtienen el contenido de nuestra información guardada anteriormente
    while(cantCad-- > 0){
        size_t len = strlen(diccionario[lectura[i]].cad);
        if(len>=tam){
            len = tam;
        }
        tam-=len;
        memcpy(p,diccionario[lectura[i]].cad,len);
        lectura++;
        p+=len;
    }


    *p = '\0';
}

void generaCadHufman(char* cH, uc* lectura,Cadena *diccionario, ll tam){
    ll i;
    
    concatena(cH,sizeof cH, lectura,diccionario,tam);
}

/*
  Función que asigna memoria a un arreglo tipo "byte"
	---------------------------------------------------
	Argumentos:
	int n: contiene el tamaño que se requiere
	Variables utilizadas:
	*return* byte *nvo: puntero que se devuelve con la memoria asignada
*/
byte * crearEstructura(int n){
  byte * nvo;
  nvo = (byte *) malloc(sizeof(byte)*n);
  if(nvo == NULL){ 
     printf ("No hay espacio en memoria");
     exit(0);
  }
  return nvo;
}

/*
  Función que asigna memoria a un arreglo tipo "int"
	------------------------------------------------------------
	Argumentos:
	int n: contiene el tamaño que se requiere
	Variables utilizadas:
	*return* unsigned char *nvo: puntero que se devuelve con la memoria asignada
*/
int * crearDeci(int n){
  int * nvo;
  nvo = (int *) malloc(sizeof(int)*n);
  if(nvo == NULL){ 
     printf ("No hay espacio en memoria");
     exit(0);
  }
  return nvo;
}

/*
  Convierte nuestra cadena de bits en Decimal
  -------------------------------------------
  Argumentos:
  char byte[8]: contiene la información de un byte (8 bits)
  Variables utilizadas:
  int val[8]: arreglo que contiene el valor número en una posición de byte
  int i: utilizada para los loop
  *return* int resul: número en decimal equivalente
*/
int convertorBinToDec(char byte[8]){
    int val[8] = {128,64,32,16,8,4,2,1}, i, resul=0;
    for(i = 0; i < 8; i++){
        if(byte[i] == '1') resul += val[i];
    }
    return resul;
}

/*
  Función que asigna memoria a un arreglo tipo "unsigned char"
	------------------------------------------------------------
	Argumentos:
	int n: contiene el tamaño que se requiere
	Variables utilizadas:
	*return* unsigned char *nvo: puntero que se devuelve con la memoria asignada
*/
uc * crearCarac(int n){
  unsigned char *nvo;
  nvo = (unsigned char *)malloc(sizeof(unsigned char) * n);
  if(nvo == NULL){
    printf("No hay espacio en memoria");
    exit(0);
  }
  return nvo;
}

/*
  Función que crea el archivo comprimido
  --------------------------------------
  Argumentos:
  char *bytes: contiene la cadena de Huffman (cadena con todos los bits encontrados)
  char *ubicacion: ruta y nombre del archivo en donde se va a guardar el archivo comprimiso
  Variables utilizada:
  byte *cadenas: estructura que guarda bytes (8bits)
  char nvaCadena[8]: auxiliar para la manipulación de la cadena de bits
  ll cantBytes: cantidad de Bytes que hay que manipular
  ll i: utilizadas para los loops
  ll cantCero: caso para la manipulación del último byte
  int *dec: arreglo que contiene el hexadecimal del byte
  uc * carac: arreglo que contiene el elemento del byte
*/
void archComp(char* bytes, char* ubicacion){
    
    byte *cadenas, recolectar;
    char nvaCadena[8] = "";
    ll cantBytes, i, cantCero;
    int *dec;
    uc *carac;

    //Abrimos el archivo en modo escritura
    FILE *arch = fopen(ubicacion,"w");
    if(arch == NULL){
      printf("No se pudo abrir el archivo de compresion!\n");   
      exit(1);             
    } 
    
    //Saca el número de bytes que hay en la cadena + 1 para el que no esta completo (si es el caso)
    cantBytes = (strlen(bytes)/8)+1;

    //Lss dos extras es para almacenar el número de ceros y para verificar si lo hizo o no respectivamente
    cadenas = crearEstructura (cantBytes + 2);
    dec = crearDeci(cantBytes + 2);
    carac = crearCarac(cantBytes + 2);
    //Va insertando los caracteres
    for(i = 0; i < cantBytes; i++){
        strncpy(nvaCadena, bytes + (i*8), 8);
        strcpy(cadenas[i].bits, nvaCadena);
    }

    //Sacamos la cantidad de ceros para llenar el último byte extra
    cantCero = 8 - strlen(cadenas[cantBytes - 1].bits);
    memset(nvaCadena, 0, 8);
    strcat(nvaCadena, cadenas[cantBytes - 1].bits);
    //Llenamos de ceros los que faltan
    for(i = 8 - cantCero ; i < 8; i++){
      strcat(nvaCadena, "0");
    }
    strcpy(cadenas[cantBytes - 1].bits, nvaCadena);
    sprintf(cadenas[cantBytes].bits, "%lld" ,cantCero);
    
    //Verifica si el último byte fue requerido o no
    if(cantCero == 8) strcpy(cadenas[cantBytes + 1].bits, "0");
    else strcpy(cadenas[cantBytes + 1].bits, "1");
    
    //Va insertando los caracteres
    for(i = 0; i <= cantBytes -1; i++){
      if(i < cantBytes){
          dec[i] = convertorBinToDec(cadenas[i].bits);
          carac[i] = (unsigned char)dec[i];
      }else if(i == cantBytes){
          dec[i] = cantCero;
          carac[i] = (unsigned char)dec[i];
      }else{
          dec[i] = atoi(cadenas[i].bits);
          carac[i] = (unsigned char)dec[i];
      }
        if(i < cantBytes) {
          fprintf(arch,"%c", carac[i]);
        } 
    }
    
    //Inserta los dos últimos elementos para manipular el último bute
    fprintf (arch,"%c", cadenas[cantBytes].bits[0]);
    fprintf (arch,"%c", cadenas[cantBytes -1].bits[0]);

    fclose(arch);
}