#include "def.h"

typedef unsigned int u32;


int main(void){

  Grafo grafo = construirGrafo();
  if(grafo == NULL) return 0;
  leerGrafo(grafo);
  free(grafo);
  return 0;
}
