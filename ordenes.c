#include "def.h"

u32* punteroColores;

char OrdenNatural(Grafo G){
  qsort(G->vertices,G->nVertices,sizeof(Vertice),ComparadorNatural);
}

int ComparadorNatural(const void* a, const void* b){
  if((*(Vertice*)a)->nombre >(*(Vertice*)b)->nombre) return 1;
  if((*(Vertice*)a)->nombre == (*(Vertice*)b)->nombre) return 0;
  return -1;
}

char OrdenWelshPowell(Grafo G){
  qsort(G->vertices,G->nVertices,sizeof(Vertice),ComparadorWelshPowell);
}

int ComparadorWelshPowell(const void* a, const void* b){
  if((*(Vertice*)a)->grado < (*(Vertice*)b)->grado) return 1;
  if((*(Vertice*)a)->grado == (*(Vertice*)b)->grado) return 0;
  return -1;
}

char OrdenRMBCnormal(Grafo G){
  qsort(G->vertices,G->nVertices,sizeof(Vertice),ComparadorRMBCnormal);
}

int ComparadorRMBCnormal(const void* a, const void* b){
  if((*(Vertice*)a)->color > (*(Vertice*)b)->color) return 1;
  if((*(Vertice*)a)->color == (*(Vertice*)b)->color) return 0;
  return -1;
}

char OrdenRMBCrevierte(Grafo G){
  qsort(G->vertices,G->nVertices,sizeof(Vertice),ComparadorRMBCrevierte);
}

int ComparadorRMBCrevierte(const void* a, const void* b){
  if((*(Vertice*)a)->color < (*(Vertice*)b)->color) return 1;
  if((*(Vertice*)a)->color == (*(Vertice*)b)->color) return 0;
  return -1;
}

char OrdenRMBCchicogrande(Grafo G){
  punteroColores = calloc(G->nColores, sizeof(u32));
  for(uint j = 0; j<G->nVertices;j++){
    punteroColores[G->vertices[j]->color]++;
  }
  qsort(G->vertices,G->nVertices,sizeof(Vertice),ComparadorRMBCchicogrande);
}

int ComparadorRMBCchicogrande(const void* a, const void* b){
  if(punteroColores[(*(Vertice*)a)->color] < punteroColores[(*(Vertice*)b)->color]) return 1;
  if(punteroColores[(*(Vertice*)a)->color] == punteroColores[(*(Vertice*)b)->color]) return 0;
  return -1;
}
