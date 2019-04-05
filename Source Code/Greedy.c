#include "Rii.h"

u32 Greedy(Grafo G){
  u32 nVertices = G->nVertices;
  Vertice verticesUsados[nVertices];
  u32 nColores = 0;
  /* Main Loop, una vez por cada vertice. */
  for(u32 i = 0; i<nVertices; i++){
    Vertice vertice = G->vertices[i];
    bool coloresUsados[nColores+1];
    /* Inicializo arreglo de bools de colores usados en false. */
    for(u32 j = 0; j<nColores+1; j++){
      coloresUsados[j] = false;
    }
    /* Seteo los colores usados por los vecinos a True y el resto queda en False. */
    for(u32 h = 0; h<i; h++){
      Vertice verticeObservado = verticesUsados[h];
      coloresUsados[verticeObservado->color] |= EsVecino(vertice,verticeObservado);
    }
    u32 color = 0;
    /* Busco el primer color que este en false o hasta llegar al ultimo color. */
    while(coloresUsados[color] && color<nColores) color++;
    /* Pinto el vertice y lo agrego en los vertices usados. */
    vertice->color = color;
    verticesUsados[i] = vertice;
    /* Si lo pinte del ultimo color, agregue un nuevo color por lo tanto incremento el contador. */
    if(color == nColores) nColores++;
  }
  G->nColores = nColores;
  /* Retorno la cantidad de colores final. */
  return nColores;
}
