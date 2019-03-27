#include "Rii.h"

/* Arreglo global porque no puedo pasarle otro parametro a las funciones comparadoras */
u32* punteroColores;

/* Toma el grafo y el la funcion de comparacion y ordena los vertices */
void Ordenar(Grafo G, int (*compar)(const void *, const void*)){
  qsort(G->vertices,G->nVertices,sizeof(Vertice),compar);
}

/* Orden natural (Por Nombre de vertice, Creciente) */
char OrdenNatural(Grafo G){
  Ordenar(G,ComparadorNatural);
  return 0;
}

int ComparadorNatural(const void* a, const void* b){
  if((*(Vertice*)a)->nombre >(*(Vertice*)b)->nombre) return 1;
  if((*(Vertice*)a)->nombre == (*(Vertice*)b)->nombre) return 0;
  return -1;
}

/* Orden WelshPowell (Por grado, Decreciente) */
char OrdenWelshPowell(Grafo G){
  Ordenar(G,ComparadorWelshPowell);
  return 0;
}

int ComparadorWelshPowell(const void* a, const void* b){
  if((*(Vertice*)a)->grado < (*(Vertice*)b)->grado) return 1;
  if((*(Vertice*)a)->grado == (*(Vertice*)b)->grado) return 0;
  return -1;
}

/* Orden RMBCnormal (Por colores, Creciente) */
char OrdenRMBCnormal(Grafo G){
  Ordenar(G,ComparadorRMBCnormal);
  return 0;
}

int ComparadorRMBCnormal(const void* a, const void* b){
  if((*(Vertice*)a)->color > (*(Vertice*)b)->color) return 1;
  if((*(Vertice*)a)->color == (*(Vertice*)b)->color) return 0;
  return -1;
}

/* Orden RMBCrevierte (Por colores, Decreciente) */
char OrdenRMBCrevierte(Grafo G){
  Ordenar(G,ComparadorRMBCrevierte);
  return 0;
}

int ComparadorRMBCrevierte(const void* a, const void* b){
  if((*(Vertice*)a)->color < (*(Vertice*)b)->color) return 1;
  if((*(Vertice*)a)->color == (*(Vertice*)b)->color) return 0;
  return -1;
}

/* Orden RMBCchicogrande (Por colores, Cantidad de vertices del color, Decreciente) */
char OrdenRMBCchicogrande(Grafo G){
  /* Creo el arreglo de la cantidad de vertices de cada color global para usar en el comparador */
  punteroColores = calloc(G->nColores, sizeof(u32));
  for(uint j = 0; j<G->nVertices;j++){
    punteroColores[G->vertices[j]->color]++;
  }
  Ordenar(G,ComparadorRMBCchicogrande);
  /* Libero el arreglo */
  free(punteroColores);
  return 0;
}

int ComparadorRMBCchicogrande(const void* a, const void* b){
  if(punteroColores[(*(Vertice*)a)->color] < punteroColores[(*(Vertice*)b)->color]) return 1;
  if(punteroColores[(*(Vertice*)a)->color] == punteroColores[(*(Vertice*)b)->color]) return 0;
  return -1;
}
