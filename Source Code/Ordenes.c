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
  for(u32 j = 0; j<G->nVertices;j++){
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

/* Cambia el color de los vertices del grafo de color i a j, y viceversa */
char SwitchColores(Grafo G, u32 i, u32 j){
  if(i > NumeroDeColores(G) || j > NumeroDeColores(G)) return 1;
  for(u32 h = 0; h < G->nVertices; h++){
    if(G->vertices[h]->color == i) G->vertices[h]->color = j;
    else if(G->vertices[h]->color == j) G->vertices[h]->color = i;
  }
  return 0;
}

/* Intercambia los vertices de las posiciones i,j en el grafo G*/
char SwitchVertices(Grafo G, u32 i, u32 j){
  //Checkea si i,j estan fuera de los valores correctos, retorna 1
  if(i >= G->nVertices || j >= G->nVertices) return 1;
  //Sino, realiza el swap:
  Vertice temp = G->vertices[i];
  G->vertices[i] = G->vertices[j];
  G->vertices[j] = temp;
  return 0;
}
