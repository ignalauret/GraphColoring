#include "Rii.h"

/* Devuelve el numero de vertices */
u32 NumeroDeVertices(Grafo G){
  return G->nVertices;
}

/* Devuelve el numero de aristas */
u32 NumeroDeAristas(Grafo G){
  return G->nAristas;
}

/* Devuelve el numero de colores */
u32 NumeroDeColores(Grafo G){
  return G->nColores;
}

/* Devuelve el grado del vertice i-esimo */
u32 NumeroDeVecinos(Grafo G, u32 i){
  return G->vertices[i]->grado;
}

/* Devuelve el nombre del vertice i-esimo */
u32 NombreDelVertice(Grafo G, u32 i){
  return G->vertices[i]->nombre;
}

/* Devuelve el color del vertice i-esimo */
u32 ColorDelVertice(Grafo G, u32 i){
  /* Verifico el indice */
  if(i > NumeroDeVertices(G)) return -1;
  return G->vertices[i]->color;
}

/* Devuelve el grado del vertice i-esimo */
u32 GradoDelVertice(Grafo G, u32 i){
  /* Verifico el indice */
  if(i > NumeroDeVertices(G)) return -1;
  return G->vertices[i]->grado;
}

/* Busca el vecino j-esimo del vertice i-esimo y devuelve su nombre */
u32 NombreJotaesimoVecino(Grafo G, u32 i, u32 j){
  Vertice c = G->vertices[i];
  Vertice vecino = c->vecinos[j];
  return vecino->nombre;
}

/* Busca el vecino j-esimo del vertice i-esimo y devuelve su color */
u32 ColorJotaesimoVecino(Grafo G, u32 i, u32 j){
  /* Verifico los indices */
  if(i > NumeroDeVertices(G) || j > NumeroDeVecinos(G,i)) return -1;
  Vertice c = G->vertices[i];
  Vertice vecino = c->vecinos[j];
  return vecino->color;
}

/* Chequea si un vertice esta en la lista de vecinos de otro. */
bool EsVecino(Vertice v1, Vertice v2){
  for (uint i = 0; i < v1->grado; i++) {
    if ( v1->vecinos[i] == v2 ) return true;
  }
  return false;
}

/* Recorre el grafo llamando a las funciones para imprimir datos */
void LeerGrafo(Grafo G){
  /* Recorro todo el arreglo de vertices. */
  for(uint i = 0; i<G->nVertices;i++){
    PrintVecinos(G->vertices[i]);
  }
}

/* Imprime datos sobre el vertice por consola */
void PrintVecinos(Vertice v){
  if(v == NULL) return;
  /* Si existe printea el grado, nombre y vecinos */
  printf("Vertice numero: %u Grado: %u Color: %u \nSus vecino son:", v->nombre , v->grado, v->color);
  for (uint i = 0; i < v->grado; i++) {
    u32 act = v->vecinos[i]->nombre;
    printf(" %u", act);
  }
  printf("\n\n");
}
