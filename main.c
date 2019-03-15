#include "def.h"

typedef unsigned int u32;


int main(void){

  Grafo grafo = construirGrafo();
  free(grafo);
  return 0;
}
