#include "Rii.h"

/* Agrega un Vertice con un id al grafo si este no existe y lo devuelve.
   Si existe, solo lo devuelve. */
Vertice AgregarVertice(Grafo grafo, u32 id){
  u32 nVertices = grafo->nVertices;
  u32 posicion = HashFunc(id,nVertices);
  /* Como use calloc, si no existe el vertice el puntero tendra el valor 0. */
  if(grafo->vertices[posicion] == 0){
    /* Alloco memoria para el vertice. */
    Vertice nuevoVertice = malloc(sizeof(struct VerticeSt));
    /* Seteo valores. */
    nuevoVertice->nombre = id;
    nuevoVertice->grado = 0;
    nuevoVertice->color = 0;
    /* Alloco memoria para la lista de vecinos. */
    nuevoVertice->vecinos = (Vertice*)malloc(sizeof(Vertice));
    nuevoVertice->capacidadVecinos = 1;
    /* Guardo el vertice en el Grafo, incremento los vertices cargados y lo devuelvo. */
    grafo->vertices[posicion] = nuevoVertice;
    grafo->nVerticesCargados++;
    return nuevoVertice;
  }
  /* Si no es 0, me fijo si es este mismo vertice que ya fue guardado. */
  if(grafo->vertices[posicion]->nombre == id){
    /* Si ya existe, solo lo retorno. */
    return grafo->vertices[posicion];
  }
  /*Si no lo es, busco el vertice hasta encontrarlo o encontrar un vertice en desuso.
  NOTA: Si el vertice ya hubiera sido guardado, no podria estar despues de un vertice vacio,
  ya que hubiera ocupado ese cundo fue creado (Porque nunca se borran vertices)*/
  for(uint i = 1;i<nVertices;i++){
    /* Si encuentro uno vacio lo creo aca. */
    if(grafo->vertices[(posicion+i)%nVertices] == 0){
      /* Alloco memoria para el vertice. */
      Vertice nuevoVertice = malloc(sizeof(struct VerticeSt));
      /* Seteo valores. */
      nuevoVertice->nombre = id;
      nuevoVertice->grado = 0;
      nuevoVertice->color = 0;
      /* Alloco memoria para la lista de vecinos. */
      nuevoVertice->vecinos = (Vertice*)malloc(sizeof(Vertice));
      nuevoVertice->capacidadVecinos = 1;
      /* Guardo el vertice en el Grafo, incremento los vertices cargados y lo devuelvo. */
      grafo->vertices[(posicion+i)%nVertices] = nuevoVertice;
      grafo->nVerticesCargados++;
      return nuevoVertice;
    }
    /* Si encuentro el vertice lo devuelvo. */
    if(grafo->vertices[(posicion+i)%nVertices]->nombre == id){
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
int AgregarArista(Grafo G, u32 v1, u32 v2){
  /* Agrego vertices. */
  Vertice vertice1 = AgregarVertice(G,v1);
  Vertice vertice2 = AgregarVertice(G,v2);
  /* Verifico si alguno dio NULL */
  if(vertice1 == NULL || vertice2 == NULL) return -1;
  /* Chequeo si ya son vecinos. Si lo son, la arista ya existia -> retorno. */
  if(EsVecino(vertice1,vertice2)){
    printf("Error arista [%u,%u] ya existente\n",vertice1->nombre, vertice2->nombre);
    PrintVecinos(vertice1);
    return 0;
  }
  /* Si no eran vecinos, los agrego como vecinos. */
  AgregarVecino(vertice1,vertice2);
  AgregarVecino(vertice2,vertice1);
  return 1;
}

/* Funcion que realmente agrega el vecino al vertice del grafo. */
void AgregarVecino(Vertice vertice, Vertice vecino){
  u32 grado = vertice->grado;
  if(grado == vertice->capacidadVecinos) {
    /* Si el arreglo se lleno, duplico su tamaño */
    vertice->capacidadVecinos *=2;
    /* Realloco el arreglo completo */
    vertice->vecinos = realloc( vertice->vecinos, vertice->capacidadVecinos * sizeof(Vertice));
  }
  /* Agrego el vecino y sumo uno al grado */
  vertice->vecinos[grado] = vecino;
  vertice->grado++;
}

//TODO: Por ahora solo tomo modulo. Implementar funcon Hash.
u32 HashFunc(u32 id, u32 v){
  return id%v;
}

/* Resetea el color de todos los vertices a -1 */
void ResetColores(Grafo G){
  u32 nVertices = G->nVertices;
  /* Recorro todos los vertices del grafo */
  for(u32 i = 0; i<nVertices; i++){
    Vertice vertice = G->vertices[i];
    u32 nVecinos = vertice->grado;
    /* Recorro todos los vecinos del vertice */
    for(uint j = 0; j<nVecinos; j++){
      vertice->vecinos[j]->color = -1;
    }
  }
}
