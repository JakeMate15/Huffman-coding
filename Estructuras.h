//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Diciembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Definición para la codificación de Huffman
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>

//*****************************************************************
//DEFINICION DE CONSTANTES DEL PROGRAMA
//*****************************************************************
#define PESOBIT(bpos) 1<<bpos
#define CONSULTARBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)

//********************************************************************************
//DECLARACION DE ESTRUCTURAS Y TIPO DE DATOS
//********************************************************************************
typedef long long int ll;
typedef unsigned char uc;

typedef struct{
    uc valor;
    ll repeticiones;
}Par;

typedef Par* Pares;


struct nodoArbol{
    Par info;
    struct nodoArbol *izquierdo; 
    struct nodoArbol *derecho;
};

typedef struct nodoArbol Nodo;
typedef struct nodoArbol* NODO;


struct arbol{
    int tam;
    int capacidad;
    NODO* nodos;
};

typedef struct arbol Arbol;
typedef struct arbol* ARBOL;

typedef struct{
    char cad[100];
}Cadena;

typedef struct {
 char bits[8];
}byte;

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
void imprimeArregloEnteros(int a[], int n, FILE *);
ll tamArch(char* arch);
uc* frecuencias(char* arch, Pares tablaFrecuencias, ll* tam);
void arregloPares(Pares tablaFrecuencias);
void quickSort(Pares A, int p, int r);
int pivot(Pares A, int p, int r);
void intercambiar(Pares A, int i, int j);
int elementosTabla(Pares tablaFrecuencias);
void tablaConUtiles(Pares tablaFrecuencias, Pares nuevaTabla, int n);
void imprimeTablaFrecuencias(Pares tablaFrecuencias, int n);
void imprimeBits(int n_bits, uc numero, FILE *);
//char* concatena(char *destino, size_t tam, Cadena* cadenas, size_t cantCad);
void concatena(char *destino, size_t tam, uc* lectura, Cadena* diccionario, size_t cantCad);

NODO nuevoNodo(Par datos);
ARBOL creaArbol(int capacidad);
void intercambioNodos(NODO* a, NODO* b);
void intercambioActualMin(ARBOL a, int indice);
int esTam1(ARBOL a);
NODO extraeMin(ARBOL a);
void inserta(ARBOL ar, NODO n);
void construye(ARBOL a);
int esHoja(NODO raiz);
ARBOL construyeArbolRep(Pares datos, int n); 
NODO construyeArbolHuffman(Pares datos, int n);
void imprimeCodigos(NODO raiz, int a[], int superior, Cadena *dic, int *max, FILE *);
void generaDiccionario(Pares dato, int n, Cadena *dic, int *max, char *);
void arrToString(int *arr, char* s, int n);
void generaCadHufman(char* cH, uc* lectura, Cadena *diccionario, ll tam);

byte* crearEstructura (int);
int* crearDeci (int);
int convertorBinToDec (char [8]);
void archComp(char* bytes, char* ubicacion);
