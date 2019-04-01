#include "Rii.h"

int Bipartito(Grafo G){
  /* Reseteo colores a -1 */
  ResetColores(G);
  u32 counter = 0;
  u32 nVertices = G->nVertices;

  /* Comienzo la recursion en el vertice 0 (Podria ser en cualquiera) */
  int dfsCheckInt = DfsCheck(G->vertices[0],0);

  /* dfsCheck devuelve -1 si estaba pintado del color incorrecto, por lo tanto
     la suma no dara la cantidad de vertices si alguno estuvo mal pintado */
  if(dfsCheckInt == nVertices) return 1;

  /* Sino, no es bipartito. Pinto con Greedy y retorno 0 */
  Greedy(G);
  return 0;
}

/* Recursivo. De ser bipartito, dfsCheck de cualquier vertice deberia devolver
   la cantidad de vertices */
int DfsCheck(Vertice v, u32 color){
  /* Si ya estaba pintado de el color que deberia, no lo cuento */
  if(v->color == color) return 0;
  /* Si ya estaba pintado de el otro color, tenemos un error porlotanto no es bipartito,
     ya que existe una UNICA forma de pintarlo (salvo switch de colores) de dos colores */
  if(v->color == 1-color) return -1;
  /* Como solo tengo 2 colores, entonces si llego aca significa que no estaba pintado. */
  /* Lo pinto */
  v->color = color;
  /* Hago recursion con sus vecinos */
  int dfsCounter = 1;
  for(uint i = 0; i<v->grado; i++){
    dfsCounter += DfsCheck(v->vecinos[i],1-color);
  }
  /* Devuelvo el resultado */
  return dfsCounter;
}
