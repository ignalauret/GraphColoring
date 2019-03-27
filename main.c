#include "Rii.h"

typedef unsigned int u32;


int main(void){

  Grafo grafo = ConstruccionDelGrafo();
  if(grafo == NULL) return 0;

  u32 colores = Greedy(grafo);
  printf("Greedy pinto con %d colores\n", colores);
  LeerGrafo(grafo);

  printf("Orden RMBCnormal\n");
  OrdenRMBCnormal(grafo);
  LeerGrafo(grafo);

  printf("Orden RMBCrevierte\n");
  OrdenRMBCrevierte(grafo);
  LeerGrafo(grafo);

  printf("Orden RMBCchicogrande\n");
  OrdenRMBCchicogrande(grafo);
  LeerGrafo(grafo);

  if(Bipartito(grafo)) printf("Es Bipartito\n");
  else printf("No es Bipartito\n");

  printf("Orden WelshPowell\n");
  OrdenWelshPowell(grafo);
  LeerGrafo(grafo);

  printf("Orden Natural\n");
  OrdenNatural(grafo);
  LeerGrafo(grafo);

  free(grafo);
  return 0;
}
