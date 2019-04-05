#include "Rii.h"

int Bipartito(Grafo G){
  /* Reseteo colores a -1 */
  ResetColores(G);
  u32 nVertices = G->nVertices;

  Vertice verticeInicial;
  u32 dfsCheckInt = 0;

  /* Corro una vez Bipartito para cada componente conexa */
  while((verticeInicial = checkAllColored(G)) != NULL){
    /* Comienzo la recursion con un vertice que no este pintado aun */
    dfsCheckInt += DfsCheck(verticeInicial,0);
  }

  /* dfsCheck devuelve -1 si estaba pintado del color incorrecto, por lo tanto
     la suma no dara la cantidad de vertices si alguno estuvo mal pintado */
  if(dfsCheckInt == nVertices) return 1;

  /* Sino, no es bipartito. Pinto con Greedy y retorno 0 */
  Greedy(G);
  return 0;
}

/* Retorna el primer vertice no pintado que encuentra */
Vertice checkAllColored(Grafo G){
  for(uint i = 0; i < G->nVertices; i++){
    if(G->vertices[i]->color == (u32)-1) return G->vertices[i];
  }
  return NULL;
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
