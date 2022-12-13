//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Diciembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Definición para la decodificación de Huffman
//*****************************************************************

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

struct nodo{
    struct nodo* izq;
    struct nodo* der;
    int esHoja;
    int simbolo;
};

typedef struct nodo Nodo;
typedef struct nodo* NODO;

//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
NODO creaNodo();
void construyeArbol(char* dirDiccionario, NODO raiz);
void descompresion(char * dirCompresion, char* dirDescompresion, NODO arbol);
ll tamArch(char* arch);
uc * generaCad(char * dirCompresion);
char *crearBin(long long int n);
uc *crearCarac(int n);