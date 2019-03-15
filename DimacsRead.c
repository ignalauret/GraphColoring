#include "def.h"



Grafo construirGrafo(){
  //El grafo
  Grafo grafo;
  //Largo maximo de los comentarios = 80.
  int bufsize = 80;

  //Variables para crear el grafo.
  u32 nAristas;
  u32 nVertices;

  //Variables para construir el grafo.
  u32 vertice1;
  u32 vertice2;
  char vertice1String[10];
  char vertice2String[10];
  char nAristasString[10];
  char nVerticesString[10];
  uint counter = 0;
  //Variables para guardar el texto.
  char buffer[bufsize];
  char p[1];
  char edge[4];
  //Para que la primer linea (en blanco porque todavia no leyo nada) entre al while.
  buffer[0] = 'c';

  //Mientras empiece con 'c' el renglon (DIMACS), lo consideramos comentario y no hacemos nada.
  while (buffer[0] == 'c'){
    //Leo la siguiente linea, si es Null algo anduvo mal.
    if(fgets(buffer, bufsize, stdin) == NULL) {
      printf("Error en la lectura.");
      return NULL;
    }
      printf("Es un comentario.\n");
  }
  printf("Fin de los comentarios.\n");

  //Si salgo del while, entonces no empieza con 'c', chequeamos si es del a forma correcta (DIMACS).
  //Escaneamos la linea a ver si tenemos 4 elementos.
  sscanf(buffer,"%s %s %s %s",p,edge,nAristasString,nVerticesString);

  //Convertimos los strings a numero (u32).
  nAristas = atoi(nAristasString);
  nVertices = atoi(nVerticesString);

  //Si no eran numeros, entonces atoi devuelve 0...
  //TODO: Se rompe si le paso un numero seguido de letras y numeros, toma el numero hasta la primer letra. Ej: 55fd98 = 55.
  if(nVertices == 0 || nAristas == 0){
    errorFormatoInvalido(grafo);
    return NULL;
  }

  if(nAristas > nVertices*(nVertices-1) /2){
    printf("Demasiadas Aristas\n");
    return NULL;
  }

  //Chequeamos si el segundo string es 'edge' (DIMACS).
  if(strncmp(edge,"edge",4) != 0){
    errorFormatoInvalido(grafo);
    return NULL;
  }
  //Chequeamos si el primer string es 'p' (DIMACS).
  if(strncmp(p,"p",1) != 0){
    errorFormatoInvalido(grafo);
    return NULL;
  }

  printf("Aristas: %d, Vertices: %d\n", nAristas, nVertices );
  //Allocamos memoria para el grafo.
  grafo = malloc(sizeof(struct _Grafo));
  //Chequeamos si se alloco correctamente.
  if(grafo != NULL) {
    printf("Grafo Creado con exito.\n");
    grafo->nAristas = nAristas;
    grafo->nVertices = nVertices;
    grafo->vertices = calloc(nVertices,sizeof(Vertice));
    grafo->orden = malloc(nVertices*sizeof(u32));
    grafo->nColores = 0;
  }
  else printf("Error en la creacion del grafo\n");

  while(counter < nAristas){
    if(fgets(buffer, bufsize, stdin) != NULL) {

      sscanf(buffer, "%s %s %s", p, vertice1String, vertice2String);
      vertice1 = atoi(vertice1String);
      vertice2 = atoi(vertice2String);

      if(strncmp(p,"e",1) != 0){
        errorFormatoInvalido(grafo);
        return NULL;
      }

      if(vertice1 <= 0 || vertice2 <= 0){
        errorFormatoInvalido(grafo);
        return NULL;
      }

      printf("Arista de %u a %u\n",vertice1,vertice2);

      counter += agregarArista(grafo,vertice1, vertice2);
      printf("Vertices Restantes: %d\n",cantidadDeVertices(grafo));
    } else {
      errorFormatoInvalido(grafo);
      return NULL;
    }
  }
  return grafo;
}

Vertice agregarVertice(Grafo grafo, u32 id){
  if(grafo->vertices[id] == 0){
    Vertice nuevoVertice = malloc(sizeof(struct _Vertice));
    nuevoVertice->nombre = id;
    nuevoVertice->grado = 1;
    nuevoVertice->color = 0;
    nuevoVertice->vecinos = malloc(sizeof(Vecino));
    grafo->vertices[id] = nuevoVertice;
    printf("Vertice Creado.\n");
    return nuevoVertice;
  }
  grafo->vertices[id]->grado++;
  printf("Vertice Existente.\n");
  return grafo->vertices[id];
}

int agregarArista(Grafo G, u32 v1, u32 v2){
  Vertice vertice1 = agregarVertice(G,v1);
  Vertice vertice2 = agregarVertice(G,v2);
  if(esVecino(G->vertices[v1],vertice2) || esVecino(G->vertices[v2],vertice1)){
    printf("Error arista ya existente\n");
    return 0;
  }
  agregarVecino(G->vertices[v1],vertice2);
  agregarVecino(G->vertices[v2],vertice1);
  return 1;
}

void agregarVecino(Vertice vertice, Vertice vecino){
  Vecino nuevoVecino = malloc(sizeof(struct _Vecino));
  nuevoVecino->vertice = vecino;
  nuevoVecino->siguienteVecino = vertice->vecinos;
  vertice->vecinos = nuevoVecino;
}

bool esVecino(Vertice v1, Vertice v2){
  Vecino vecino = v1->vecinos;
  while(vecino != NULL){
    if(vecino->vertice == v2) break;
    vecino = vecino->siguienteVecino;
  }
  return vecino != NULL;
}

Vertice vecinoNumero(Vertice v, u32 i){
  u32 counter = 0;
  Vecino vecino = v->vecinos;

  while(vecino != NULL && counter < i){
    vecino = vecino->siguienteVecino;
    counter++;
  }
  if(vecino == NULL) return NULL;
  return vecino->vertice;
}

int cantidadDeVertices(Grafo G){
  int counter = 0;
  int size = G->nVertices;
  for(uint i = 0; i<size;i++){
    if(G->vertices[i] == 0){
      counter++;
    }
  }
  return counter;
}

void leerGrafo(Grafo G){
  for(uint i = 0; i<G->nVertices;i++){
    printVecinos(G->vertices[i]);
  }
}

void printVecinos(Vertice v){
  if(v == NULL) return;
  Vecino actual = v->vecinos;
  if(actual == NULL) {
    printf("No hay nada\n");
    return;
  }
  printf("Los vecinos de %d son:\n", v->nombre );
  while( actual->siguienteVecino != NULL ) {
    u32 listo = actual->vertice->nombre;
    printf("%d\n", listo );
    actual = actual->siguienteVecino;
  }
}

void errorFormatoInvalido(Grafo G){
  //Libero el grafo que habia creado hasta ahora.
  free(G->vertices);
  free(G);
  //Printeo mensaje de error.
  printf("### Formato de Grafo Invalido ###\n### Revisar formato DIMACS ###\n" );
}
