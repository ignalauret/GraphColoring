#include "def.h"

typedef unsigned int u32;


int main(void){

  Grafo grafo = construirGrafo();
  if(grafo == NULL) return 0;
  u32 colores = Greedy(grafo);
  printf("Greedy pinto con %d colores\n", colores);
  leerGrafo(grafo);
  free(grafo);
  return 0;
}
