#include "Rii.h"

typedef unsigned int u32;


int main(void){

  Grafo grafo = ConstruccionDelGrafo();
  if(grafo == NULL) return 0;

  u32 colores = Greedy(grafo);
  printf("Greedy pinto con %d colores\n", colores);

  LeerGrafo(grafo);
  OrdenRMBCnormal(grafo);
  LeerGrafo(grafo);
  colores = Greedy(grafo);
  printf("Greedy con Orden RMBCnormal pinto con %u colores\n", colores);

  OrdenNatural(grafo);
  colores = Greedy(grafo);
  printf("Greedy con Orden Natural pinto con %u colores\n", colores);

  OrdenWelshPowell(grafo);
  colores = Greedy(grafo);
  printf("Greedy con Orden WelshPowell pinto con %u colores\n", colores);

  free(grafo);
  return 0;
}
