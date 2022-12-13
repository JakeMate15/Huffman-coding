#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
 char bits[8];
}byte;

byte* crearEstructura (int);
int * crearDeci(int);
int convertorBinToDec(char [8]);
unsigned char *crearCarac(int);
void obtenerCadenaOriginal(unsigned char *, int);
char *crearBin(long long int);

int main()
{
  byte *cadenas, recolectar;
  char *bytes = "1101001100000011", nvaCadena[8] = "";
  int cantBytes, i, cantCero;
  int *dec;
  unsigned char *carac;
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
    sprintf(cadenas[cantBytes].bits, "%d" ,cantCero);
    
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
          printf("%c", carac[i]);
        } 
    }
    
    printf ("%c", cadenas[cantBytes].bits[0]);
    printf ("%c", cadenas[cantBytes -1].bits[0]);
}

byte * crearEstructura(int n){
  byte * nvo;
  nvo = (byte *) malloc(sizeof(byte)*n);
  if(nvo == NULL){ 
     printf ("No hay espacio en memoria");
     exit(0);
  }
  return nvo;
}

int * crearDeci(int n){
  int * nvo;
  nvo = (int *) malloc(sizeof(int)*n);
  if(nvo == NULL){ 
     printf ("No hay espacio en memoria");
     exit(0);
  }
  return nvo;
}

unsigned char * crearCarac(int n){
  unsigned char *nvo;
  nvo = (unsigned char *)malloc(sizeof(unsigned char) * n);
  if(nvo == NULL){
    printf("No hay espacio en memoria");
    exit(0);
  }
  return nvo;
}

int convertorBinToDec(char byte[8]){
    int val[8] = {128,64,32,16,8,4,2,1}, i, resul=0;
    for(i = 0; i < 8; i++){
        if(byte[i] == '1') resul += val[i];
    }
    return resul;
}

char * crearBin(long long int n){
    char * nvo;
    nvo = (char *) malloc(sizeof(char)*n);
    if(nvo == NULL){ 
      printf ("No hay espacio en memoria");
      exit(0);
    }
    return nvo;
}



void obtenerCadenaOriginal(unsigned char *carac, int noBytes){
    int i, j, val[8] = {128, 64, 32, 16, 8, 4, 2, 1}, bytes, pos;
    char *cadena;
    printf("\n%d\n", 8 - (int) carac[noBytes-2]);
    cadena = crearBin((noBytes - 2) * 8);
    for (i = 0; i < noBytes - 2; i++){
      bytes = (int)carac[i];
      if(i == (noBytes - 3) && ((int)carac[noBytes - 1]) == 1){
          for (j = 0; j < (8 - (int)carac[noBytes - 2]); j++){
            printf("%d\n", bytes);
            pos = (i * 8) + j;
            if((bytes - val[j + (int)carac[noBytes - 2]]) >= 0){
              bytes -= val[j + (int)carac[noBytes - 2]];
              cadena[pos] ='1';
            }else{
              cadena[pos] = '0';
            }
          }
      }else{
        for (j = 0; j < 8; j++){
            pos = (i * 8) + j;
            if((bytes - val[j]) >= 0){
              bytes -= val[j];
              cadena[pos] ='1';
            }else{
              cadena[pos] = '0';
            }
        }
      }
    }

    for (i = 0; i < ((noBytes-2) * 8) - (int)carac[noBytes - 2]; i++){
        printf("%c", cadena[i]);
    }
}