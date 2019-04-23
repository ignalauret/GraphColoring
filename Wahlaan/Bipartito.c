#include "Rii.h"

int Bipartito(Grafo G){
  /* Reseteo colores a -1 */
  ResetColores(G);
  u32 nVertices = G->nVertices;
  Vertice inicio;
  /* Mientras no esten todos pintados, llamo con un vertice no pintado, que deberia
  estar en una componente conexa no pintada */
  while((inicio = checkAllColored(G)) != NULL)
    /* Si da -1 en alguno, es porque alguna componente no es bipartita, termino. */
    if(pintarBipartito(nVertices,G,inicio) == -1){
      Greedy(G);
      return 0;
    }
  /* Si termine el while significa que ya esta todo pintado sin errores, retorno 1 */
  return 1;
}


int pintarBipartito(u32 nVertices, Grafo G, Vertice inicio){
  /* Creo arreglo de vertices e inicializo todos en null */
  Vertice verticesBFS[nVertices];
  for(u32 i = 1; i < nVertices; i++) verticesBFS[i] = NULL;
  /* Empiezo con mi vertice inicio */
  verticesBFS[0] = inicio;
  inicio->color = 0;
  /* Empiezo el contador en 1 porque ya agregue el primero */
  u32 verticesAgregados = 1;

  /* Voy recorriendo mi arreglo de vertices */
  for(u32 i = 0; i < nVertices; i++){
    /* Si llegue a un lugar sin nada, signiifca que se acabo la componente, me voy */
    if(verticesBFS[i] == NULL) return 0;
    /* Recorro los vecinos */
    for(u32 j = 0; j < verticesBFS[i]->grado; j++){
      /* Si es de un color distinto, no es bipartito ya que hay una unica forma de pintarlo de 2 colores */
      if(verticesBFS[i]->color == verticesBFS[i]->vecinos[j]->color) return -1;
      /* Si no fue pintado aun, lo pinto y lo agrego a la lista */
      if(verticesBFS[i]->vecinos[j]->color == (u32)-1){
        verticesBFS[i]->vecinos[j]->color = 1 - verticesBFS[i]->color;
        verticesBFS[verticesAgregados] = verticesBFS[i]->vecinos[j];
        verticesAgregados++;
      }
      /* Como solo hay 2 colores, la otra opcion es que este pintado de distinto color, en ese caso no hago nada. */
    }
  }
  /* Si todo anduvo bien, retorno 0 */
  return 0;
}

/* Retorna el primer vertice no pintado que encuentra */
Vertice checkAllColored(Grafo G){
  for(u32 i = 0; i < G->nVertices; i++){
    if(G->vertices[i]->color == (u32)-1) return G->vertices[i];
  }
  return NULL;
}
