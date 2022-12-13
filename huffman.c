//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Diciembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Algoritmo: Codificación voraz de Huffman
//Compilación: "gcc huffman.c Estructuras.c tiempo.x  -o huffman" (tiempo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)
//Ejecución: "./huffman ruta_y_nombre_archivo" (Linux y MAC OS)
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
#include "Estructuras.h"

//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main(int argc, char * argv[]){

    //******************************************************************	
    //Variables del main
    //******************************************************************
    double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
    char compresion[] = "salidas/compresion.dat"; //Variable de la ruta y nombre del archivo para poder guardar el archivo comprimido
    char docFrecuencias[] = "salidas/frecuencias.txt"; //Variable de la ruta y nombre del archivo para poder guardar nuestro diccionario
    ll tamArchivo;
    uc* lectura;
    Par tablaFrecuencias[256];
    Pares tablaUtiles;
    Cadena diccionarioHuffman[256];
    char *cadenaHufman;
    int i,n;
    int longMaxima=0;

    //******************************************************************	
    //Recepción y decodificación de argumentos
    //******************************************************************	
    //Si no se introducen exactamente 2 argumentos (Cadena de ejecución y rutaYNombreArchivo)
    if (argc!=2) 
    {
      printf("\nIndique el directorio del algoritmo - Ejemplo: [user@equipo]$ %s archLec/hola.txt\n",argv[0]);
      exit(1);
    } 


    //******************************************************************	
		//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
		//******************************************************************	
		uswtime(&utime0, &stime0, &wtime0);

    //Inicializamos nuestro diccionario (repeticiones)
    arregloPares(tablaFrecuencias);
    //Obtiene el tamaño, el contenido y la tabla de frecuencias del archivo
    lectura = frecuencias(argv[1],tablaFrecuencias,&tamArchivo);
    //Ordenamos conforme al número de repeticiones
    quickSort(tablaFrecuencias,0,255);

    //Obtenemos el tamaño de bytes identificados en el archivo
    n = elementosTabla(tablaFrecuencias);
    //Creamos una nueva estructura que contendrá la información jugosa
    tablaUtiles = (Pares)malloc(sizeof(Par)*n);
    //Pasamos sólo los elementos verificados a nuestra nueva estructura
    tablaConUtiles(tablaFrecuencias,tablaUtiles,n);
    
    //Generamos nuestro archivo de tabla de frecuencias
    generaDiccionario(tablaUtiles,n,diccionarioHuffman,&longMaxima, docFrecuencias);
    printf("\n");

    //Asignamos memoria para generar la cadena para la compresión (cadena que contendrá todos los bits)
    cadenaHufman = (char*)malloc(sizeof(char)*longMaxima*tamArchivo);
    concatena(cadenaHufman,longMaxima*tamArchivo,lectura,diccionarioHuffman,tamArchivo);
    
    //Función que crea el archivo comprimido
    archComp(cadenaHufman,compresion);

    //******************************************************************	
		//Evaluar los tiempos de ejecución 
		//******************************************************************
		uswtime(&utime1, &stime1, &wtime1);
		
		//Cálculo del tiempo de ejecución del programa
		printf("\n");
		printf("Para el archivo = %s\n", argv[1]);
		printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
		printf("real (Tiempo total exponencial)  %.10e s\n",  wtime1 - wtime0);
		printf("\n");

    return 0;
}
 