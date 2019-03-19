#include "def.h"

//Agrega un Vertice con un id al grafo si este no existe y lo devuelve.
//Si existe, solo lo devuelve.
Vertice agregarVertice(Grafo grafo, u32 id){
  u32 nVertices = grafo->nVertices;
  u32 posicion = hashFunc(id,nVertices);
  //Como use calloc, si no existe el vertice el puntero tendra el valor 0.
  if(grafo->vertices[posicion] == 0){
    //Alloco memoria para el vertice.
    Vertice nuevoVertice = malloc(sizeof(struct _Vertice));
    //Seteo valores.
    nuevoVertice->nombre = id;
    nuevoVertice->grado = 0;
    nuevoVertice->color = 0;
    //Alloco memoria para la lista de vecinos.
    nuevoVertice->vecinos = malloc(sizeof(Vecino));
    //Guardo el vertice en el Grafo y lo devuelvo.
    grafo->vertices[posicion] = nuevoVertice;
    printf("Vertice Creado.\n");
    return nuevoVertice;
  }
  //Si no es 0, me fijo si es este mismo vertice que ya fue guardado.
  if(grafo->vertices[posicion]->nombre == id){
    //Si ya existe, solo lo retorno.
    printf("Vertice Existente.\n");
    return grafo->vertices[posicion];
  }
  /*Si no lo es, busco el vertice hasta encontrarlo o encontrar un vertice en desuso.
  NOTA: Si el vertice ya hubiera sido guardado, no podria estar despues de un vertice vacio,
  ya que hubiera ocupado ese cundo fue creado (Porque nunca se borran vertices)*/
  for(uint i = 1;i<nVertices;i++){
    //Si encuentro uno vacio lo creo aca.
    if(grafo->vertices[(posicion+i)%nVertices] == 0){
      //Alloco memoria para el vertice.
      Vertice nuevoVertice = malloc(sizeof(struct _Vertice));
      //Seteo valores.
      nuevoVertice->nombre = id;
      nuevoVertice->grado = 0;
      nuevoVertice->color = 0;
      //Alloco memoria para la lista de vecinos.
      nuevoVertice->vecinos = malloc(sizeof(Vecino));
      //Guardo el vertice en el Grafo y lo devuelvo.
      grafo->vertices[(posicion+i)%nVertices] = nuevoVertice;
      printf("Vertice Creado en posicion %d.\n",posicion+i);
      return nuevoVertice;
    }
    //Si encuentro el vertice lo devuelvo.
    if(grafo->vertices[(posicion+i)%nVertices]->nombre == id){
      printf("Vertice Existente\n");
      return grafo->vertices[(posicion+i)%nVertices];
    }
  }
  /*Si el counter se acabo y no encontre ni vacio ni el vertice, significa que ya no tengo
  espacio, por lo tanto esta queriendo agregar mas vertices de la cuenta*/
  printf("No puedes agregar mas de %d vertices\n", nVertices);
  return NULL;
}


/*Llamada con la entrada de consola de nueva arista.
  Agrega los dos vertices y la arista si no existen ya.
  Devuelve 1 si la agrega y 0 si ya existia.*/
int agregarArista(Grafo G, u32 v1, u32 v2){
  //Agrego vertices.
  Vertice vertice1 = agregarVertice(G,v1);
  Vertice vertice2 = agregarVertice(G,v2);
  printf("1\n");
  if(vertice1 == NULL || vertice2 == NULL) return -1;
  //Chequeo si ya son vecinos. Si lo son, la arista ya existia -> retorno.
  if(esVecino(vertice1,vertice2) || esVecino(vertice2,vertice1)){
    printf("Error arista ya existente\n");
    return 0;
  }
  printf("2\n");
  //Si no eran vecinos, los agrego como vecinos.
  agregarVecino(vertice1,vertice2);
  agregarVecino(vertice2,vertice1);
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

//TODO: Por ahora solo tomo modulo. Implementar funcon Hash.
u32 hashFunc(u32 id, u32 v){
  return id%v;
}
