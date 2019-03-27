#include "def.h"

int Bipartito(Grafo G){
  ResetColores(G);
  uint counter = 0;
  u32 nVertices = G->nVertices;
  bool failFlag = false;
  int dfsCheckInt = dfsCheck(G->vertices[0],0);
  if(dfsCheckInt == nVertices) return 1;
  Greedy(G);
  return 0;
}

int dfsCheck(Vertice v, u32 color){
  if(v->color == color) return 0;
  if(v->color == 1-color) return -1;
  v->color = color;
  int dfsCounter = 1;
  for(uint i = 0; i<v->grado; i++){
    dfsCounter += dfsCheck(v->vecinos[i],1-color);
  }
  return dfsCounter;
}
