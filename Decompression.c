//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
//Curso: Análisis y Diseño de Algoritmos
//(C) Diciembre 2022
//ESCOM-IPN
//Equipo: LOS TOSTADOS
//Algoritmo: Decodificaciónde Huffman
//Compilación: "gcc Decompression.c EstructurasDes.c tiempo.x -o d.exe" (tiempo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)
//Ejecución: "./d.exe formato de guardado del archivo" (Linux y MAC OS)
//*****************************************************************

//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tiempo.h"
#include "EstructurasDes.h"

//*****************************************************************
//PROGRAMA PRINCIPAL 
//*****************************************************************
int main(int argc, char * argv[]){

    //******************************************************************	
    //Variables del main
    //******************************************************************
    double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para la medición de tiempos
    char diccionario[] = "salidas/frecuencias.txt"; //Ruta y Nombre del archivo donde agarra los datos obtenidos en la compresión
    char dirCompresion[] = "salidas/compresion.dat"; //Ruta y Nombre del archivo que se va a descomprimir
    char dirDescompresion[] = "salidas/descompresion."; //Ruta y Nombre del Archivo resultante

    //******************************************************************	
    //Recepción y decodificación de argumentos
    //******************************************************************	
    //Si no se introducen exactamente 2 argumentos (Cadena de ejecución y formato)
    if (argc!=2) 
    {
      printf("\nIndique el formato del archivo - Ejemplo: [user@equipo]$ %s [png|jpg|etc]\n",argv[0]);
      exit(1);
    }

    //Concatenamos el formato del archivo a guardar
    strcat(dirDescompresion, argv[1]);

    //******************************************************************	
		//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
		//******************************************************************	
		uswtime(&utime0, &stime0, &wtime0);

    //Creamos la estructura que contendrá la información de la tabla de frecuencias    
    NODO arbol = creaNodo();
    //Construimos el árbol conforme a la tabla de frecuencias
    construyeArbol(diccionario,arbol);
    //Directamente descomprime y crea el archivo resultante
    descompresion(dirCompresion, dirDescompresion, arbol);

    //******************************************************************	
		//Evaluar los tiempos de ejecución 
		//******************************************************************
		uswtime(&utime1, &stime1, &wtime1);

    //Cálculo del tiempo de ejecución del programa
		printf("\n");
		printf("Archivo de resultado = %s\n", dirDescompresion);
		printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
		printf("real (Tiempo total exponencial)  %.10e s\n",  wtime1 - wtime0);
		printf("\n");

    return 0;
}