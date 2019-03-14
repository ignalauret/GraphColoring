#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int u32;

int main(void){

  int bufsize = 80;

  u32 nLados;
  u32 nVertices;
  u32 vertice1;
  u32 vertice2;

  char vertice1String[10];
  char vertice2String[10];
  char nLadosString[10];
  char nVerticesString[10];

  char buffer[bufsize];
  char p[1];
  char edge[4];
  buffer[0] = 'c';

  while (buffer[0] == 'c'){
    if(fgets(buffer, bufsize, stdin) == NULL) {
      printf("Error interno");
      return 0;
    }
      printf("Es un comentario\n");
  }
  printf("Fin de los comentarios\n");
  if(buffer[0] != 'p'){
    printf("Formato invalido de grafo\n");
    return 0;
  }

  sscanf(buffer,"%s %s %s %s",p,edge,nLadosString,nVerticesString);

  nLados = atoi(nLadosString);
  nVertices = atoi(nVerticesString);

  if(nVertices <= 0 || nLados <= 0){
    printf("Numeros invalidos\n");
    return 0;
  }

  if(strncmp(edge,"edge",4) != 0){
    printf("Formato invalido\n");
    return 0;
  }
  printf("Lados: %d, Vertices: %d\n", nLados, nVertices );

  uint counter = 0;

  while(counter < nLados){
    if(fgets(buffer, bufsize, stdin) != NULL) {

      sscanf(buffer, "%s %s %s", p, vertice1String, vertice2String);
      vertice1 = atoi(vertice1String);
      vertice2 = atoi(vertice2String);
      if(strncmp(p,"e",1) != 0){
        printf("Lado mal puesto\n");
        return 0;
      }
      if(vertice1 <= 0 || vertice2 <= 0){
        printf("Numeros incorrectos\n");
        return 0;
      }

      printf("Arista de %u a %u\n",vertice1,vertice2);
      counter++;
    }
  }

  return 0;
}
