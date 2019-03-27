#include "def.h"

typedef unsigned int u32;


int main(void){

  Grafo grafo = construirGrafo();
  if(grafo == NULL) return 0;

  u32 colores = Greedy(grafo);
  printf("Greedy pinto con %d colores\n", colores);
  leerGrafo(grafo);

  printf("Orden RMBCnormal\n");
  OrdenRMBCnormal(grafo);
  leerGrafo(grafo);

  printf("Orden RMBCrevierte\n");
  OrdenRMBCrevierte(grafo);
  leerGrafo(grafo);

  printf("Orden RMBCchicogrande\n");
  OrdenRMBCchicogrande(grafo);
  leerGrafo(grafo);

  ResetColores(grafo);
  if(Bipartito(grafo)) printf("Es Bipartito\n");
  else printf("No es Bipartito\n");

  printf("Orden WelshPowell\n");
  OrdenWelshPowell(grafo);
  leerGrafo(grafo);

  printf("Orden Natural\n");
  OrdenNatural(grafo);
  leerGrafo(grafo);


  free(grafo);
  return 0;
}
