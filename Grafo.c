#include "def.h"

//Agrega un Vertice con un id al grafo si este no existe y lo devuelve.
//Si existe, solo lo devuelve.
Vertice agregarVertice(Grafo grafo, u32 id){
  //Como use calloc, si no existe el vertice el puntero tendra el valor 0.
  if(grafo->vertices[id] == 0){
    //Alloco memoria para el vertice.
    Vertice nuevoVertice = malloc(sizeof(struct _Vertice));
    //Seteo valores.
    nuevoVertice->nombre = id;
    nuevoVertice->grado = 0;
    nuevoVertice->color = 0;
    //Alloco memoria para la lista de vecinos.
    nuevoVertice->vecinos = malloc(sizeof(Vecino));
    //Guardo el vertice en el Grafo y lo devuelvo.
    grafo->vertices[id] = nuevoVertice;
    printf("Vertice Creado.\n");
    return nuevoVertice;
  }
  //Si ya existe, solo lo retorno.
  printf("Vertice Existente.\n");
  return grafo->vertices[id];
}

/*Llamada con la entrada de consola de nueva arista.
  Agrega los dos vertices y la arista si no existen ya.
  Devuelve 1 si la agrega y 0 si ya existia.*/
int agregarArista(Grafo G, u32 v1, u32 v2){
  //Agrego vertices.
  Vertice vertice1 = agregarVertice(G,v1);
  Vertice vertice2 = agregarVertice(G,v2);
  //Chequeo si ya son vecinos. Si lo son, la arista ya existia -> retorno.
  if(esVecino(G->vertices[v1],vertice2) || esVecino(G->vertices[v2],vertice1)){
    printf("Error arista ya existente\n");
    return 0;
  }
  //Si no eran vecinos, los agrego como vecinos.
  agregarVecino(G->vertices[v1],vertice2);
  agregarVecino(G->vertices[v2],vertice1);
  return 1;
}

//Funcion que realmente agrega el vecino al vertice del grafo.
void agregarVecino(Vertice vertice, Vertice vecino){
  //Alloco memoria para el nuevo vecino.
  Vecino nuevoVecino = malloc(sizeof(struct _Vecino));
  //Seteo valores.
  nuevoVecino->vertice = vecino;
  nuevoVecino->siguienteVecino = vertice->vecinos;
  //Guardo el vecino y aumento el grado del vertice porque tiene un nuevo vecino.
  vertice->vecinos = nuevoVecino;
  vertice->grado++;
}

//Chequea si un vertice esta en la lista de vecinos de otro.
bool esVecino(Vertice v1, Vertice v2){
  Vecino vecino = v1->vecinos;
  //Mientras existan mas vecinos en la lista que no haya revisado, continuo buscando.
  while(vecino != NULL){
    //Si encuentro a v2 en la lista de vecinos, listo.
    if(vecino->vertice == v2) break;
    vecino = vecino->siguienteVecino;
  }
  //Si es null, significa que termino el while sin encontrar nada. Sino, encontro algo.
  return vecino != NULL;
}

//Devuelve el vecino numero i del vertice si existe o null si no.
Vertice vecinoNumero(Vertice v, u32 i){
  u32 counter = 0;
  Vecino vecino = v->vecinos;
  //Recorro la lista de vecinos hasta que se acabe (== null) o hasta llegar al indice buscado.
  while(vecino != NULL && counter < i){
    vecino = vecino->siguienteVecino;
    counter++;
  }
  //Si llegue al final significa que no encontre nada.
  if(vecino == NULL) return NULL;
  //Si encontre algo, tiene que ser porque el contador lo detuvo -> encontre el vecino i.
  return vecino->vertice;
}

//Devuelve la cantidad de vertices que no hayan sido cargados en un grafo.
int cantidadDeVerticesVacios(Grafo G){
  int counter = 0;
  int size = G->nVertices;
  //Recorro todo el arreglo de vertices buscando los que no hayan sido inicializados.
  for(uint i = 0; i<size;i++){
    //Como use calloc, vertice no inicializado <-> vertice == 0.
    if(G->vertices[i] == 0){
      counter++;
    }
  }
  return counter;
}

//Imprime informacion sobre el grafo por consola.
void leerGrafo(Grafo G){
  //Recorro todo el arreglo de vertices.
  for(uint i = 0; i<G->nVertices;i++){
    printVecinos(G->vertices[i]);
  }
}

void printVecinos(Vertice v){
  if(v == NULL) return;
  printf("Vertice numero: %d Grado: %d Vecinos:\n", v->nombre , v->grado);
  Vecino actual = v->vecinos;
  //Si el primer vecino es null -> no tiene vecinos.
  if(actual == NULL) {
    printf("No tiene vecinos\n");
    return;
  }
  //Recorro la lista de vecinos imprimiendo sus nombres.
  while( actual->siguienteVecino != NULL ) {
    u32 listo = actual->vertice->nombre;
    printf("%d\n", listo );
    actual = actual->siguienteVecino;
  }
}
