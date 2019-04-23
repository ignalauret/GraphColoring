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
char RMBCnormal(Grafo G){
  //Alocamos el arreglo donde vamos a poner el resultado final:
  Vertice * arregloTemp = calloc(G->nVertices, sizeof(Vertice));
  //Si hay un problema para crearlo retornamos -1
  if(arregloTemp == NULL) return -1;
  //Creamos un arreglo de tamaño de la cantidad de colores
  punteroColores = calloc(G->nColores+1, sizeof(u32));
  //Si hay un problema para crearlo retornamos -1
  if(punteroColores == NULL) return -1;
  //Y recorremos todos los vertices incrementando en 1
  //la posicion del arreglo de su numero de color:
  //(Ya estaba inicializado en 0)
  for(u32 j = 0; j<G->nVertices; j++){
    punteroColores[G->vertices[j]->color+1]++;
  }
  //Realizamos el arreglo de sumas parciales para
  //Tener el index donde debe empezar cada color:
  for(u32 j = 1; j<G->nColores+1; j++){
    punteroColores[j] = punteroColores[j] + punteroColores[j-1];
  }
  //Ahora recorremos todos los vertices y los ponemos
  //En el arreglo que creamos al principio, pero ya
  //En la posicion correcta, incrementando el valor
  //Donde va a ir el siguiente vertice del mismo color
  for(u32 j = 0; j<G->nVertices; j++){
    u32 index = punteroColores[G->vertices[j]->color];
    punteroColores[G->vertices[j]->color]++;
    arregloTemp[index] = G->vertices[j];
  }
  //Liberamos lo que habia antes
  free(G->vertices);
  //Lo referenciamos al nuevo arreglo
  G->vertices = arregloTemp;
  //liberamos el arreglo de los colores
  free(punteroColores);
  return 0;
}

/* Orden RMBCrevierte (Por colores, Decreciente) */
char RMBCrevierte(Grafo G){
  //Alocamos el arreglo donde vamos a poner el resultado final:
  Vertice * arregloTemp = calloc(G->nVertices, sizeof(Vertice));
  //Si hay un problema para crearlo retornamos -1
  if(arregloTemp == NULL) return -1;
  //Creamos un arreglo de tamaño de la cantidad de colores
  punteroColores = calloc(G->nColores+1, sizeof(u32));
  //Si hay un problema para crearlo retornamos -1
  if(punteroColores == NULL) return -1;
  //Y recorremos todos los vertices incrementando en 1
  //la posicion del arreglo de su numero de color:
  //(Ya estaba inicializado en 0)
  for(u32 j = 0; j<G->nVertices; j++){
    punteroColores[G->vertices[j]->color+1]++;
  }
  //Realizamos el arreglo de sumas parciales para
  //Tener el index donde debe empezar cada color:
  for(u32 j = 1; j<G->nColores+1; j++){
    punteroColores[j] = punteroColores[j] + punteroColores[j-1];
  }
  //Ahora invertimos las posiciones para que la posicion 0 quede en el n
  //La posicion 1 en el n-1 y asi..
  for(u32 j = 0; j<G->nColores; j++){
    punteroColores[j] = (G->nVertices - 1) - punteroColores[j];
  }
  //Recorremos la lista de vertices poniendo cada uno en su
  //Lugar en el arreglo nuevo, pero esta vez decrementamos
  //El indice donde va a ir el siguiente vertice del mismo
  //color: ( n, n-1, n-2 ... )
  for(u32 j = 0; j<G->nVertices; j++){
    u32 index = punteroColores[G->vertices[j]->color];
    punteroColores[G->vertices[j]->color]--;
    arregloTemp[index] = G->vertices[j];
  }
  //Liberamos lo que habia antes
  free(G->vertices);
  //Lo referenciamos al nuevo arreglo
  G->vertices = arregloTemp;
  //liberamos el arreglo de los colores
  free(punteroColores);
  return 0;
}


/* Orden RMBCchicogrande (Por colores, Cantidad de vertices del color, Decreciente) */
char RMBCchicogrande(Grafo G){
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
  if(punteroColores[(*(Vertice*)a)->color] > punteroColores[(*(Vertice*)b)->color]) return 1;
  if(punteroColores[(*(Vertice*)a)->color] == punteroColores[(*(Vertice*)b)->color]){
    if((*(Vertice*)a)->color > (*(Vertice*)b)->color) return 1;
    if((*(Vertice*)a)->color == (*(Vertice*)b)->color) return 0;
    return -1;
  }
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

/* Intercambia los vertices de las posiciones i,j en el grafo G */
char SwitchVertices(Grafo G, u32 i, u32 j){
  //Checkea si i,j estan fuera de los valores correctos, retorna 1
  if(i >= G->nVertices || j >= G->nVertices) return 1;
  //Sino, realiza el swap:
  Vertice temp = G->vertices[i];
  G->vertices[i] = G->vertices[j];
  G->vertices[j] = temp;
  return 0;
}
