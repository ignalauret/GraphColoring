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
    nuevoVertice->vecinos = (Vertice*)malloc(sizeof(Vertice));
    nuevoVertice->capacidadVecinos = 1;
    //Guardo el vertice en el Grafo y lo devuelvo.
    grafo->vertices[posicion] = nuevoVertice;
    return nuevoVertice;
  }
  //Si no es 0, me fijo si es este mismo vertice que ya fue guardado.
  if(grafo->vertices[posicion]->nombre == id){
    //Si ya existe, solo lo retorno.
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
      nuevoVertice->vecinos = (Vertice*)malloc(sizeof(Vertice));
      nuevoVertice->capacidadVecinos = 1;
      //Guardo el vertice en el Grafo y lo devuelvo.
      grafo->vertices[(posicion+i)%nVertices] = nuevoVertice;
      return nuevoVertice;
    }
    //Si encuentro el vertice lo devuelvo.
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
int agregarArista(Grafo G, u32 v1, u32 v2){
  //Agrego vertices.
  Vertice vertice1 = agregarVertice(G,v1);
  Vertice vertice2 = agregarVertice(G,v2);
  if(vertice1 == NULL || vertice2 == NULL) return -1;
  //Chequeo si ya son vecinos. Si lo son, la arista ya existia -> retorno.
  if(esVecino(vertice1,vertice2) || esVecino(vertice2,vertice1)){
    printf("Error arista ya existente\n");
    return 0;
  }
  //Si no eran vecinos, los agrego como vecinos.
  agregarVecino(vertice1,vertice2);
  agregarVecino(vertice2,vertice1);
  return 1;
}


//Funcion que realmente agrega el vecino al vertice del grafo.
void agregarVecino(Vertice vertice, Vertice vecino){
  u32 i = vertice->grado;
  if(i == vertice->capacidadVecinos) {
    //Si el arreglo se lleno, duplico su tamaño
    vertice->capacidadVecinos *=2;
    //Realoco el arreglo completo
    vertice->vecinos = realloc( vertice->vecinos, vertice->capacidadVecinos * sizeof(Vertice));
  }
  //Agrego el vecino y sumo uno al grado
  vertice->vecinos[i] = vecino;
  vertice->grado++;
}


//Chequea si un vertice esta en la lista de vecinos de otro.
bool esVecino(Vertice v1, Vertice v2){
  for (int i = 0; i < v1->capacidadVecinos; i++) {
    if ( v1->vecinos[i] == v2 ) return true;
  }
  return false;
}

//RETORNA NOMBRE VECINO JESTI
u32 NombreJotaesimoVecino(Grafo G, u32 i, u32 j){
  Vertice c = G->vertices[i];
  Vertice vecino = c->vecinos[j];
  return vecino->nombre;
}

//RETORNA COLOR VECINO JESTI
u32  ColorJotaesimoVecino(Grafo G, u32 i, u32 j){
  Vertice c = G->vertices[i];
  Vertice vecino = c->vecinos[j];
  return vecino->color;
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
  //Si no existe printea el grado, nombre y vecinos
  printf("Vertice numero: %d Grado: %d Color: %d \nVecinos:", v->nombre , v->grado, v->color);
  for (int i = 0; i < v->capacidadVecinos; i++) {
    u32 act = v->vecinos[i]->nombre;
    printf(" %d", act);
  }
  printf("\n\n");
}

//TODO: Por ahora solo tomo modulo. Implementar funcon Hash.
u32 hashFunc(u32 id, u32 v){
  return id%v;
}

void ResetColores(Grafo G){
  u32 nVertices = G->nVertices;
  for(uint i = 0; i<nVertices; i++){
    Vertice vertice = G->vertices[i];
    u32 nVecinos = vertice->grado;
    for(uint j = 0; j<nVecinos; j++){
      vertice->vecinos[j]->color = 0;
    }
  }
}
