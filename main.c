#include "def.h"

typedef unsigned int u32;


int main(void){

  Grafo grafo = construirGrafo();
  leerGrafo(grafo);
  free(grafo);
  return 0;
}
