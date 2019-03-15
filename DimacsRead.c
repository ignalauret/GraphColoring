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
    //Allocamos lugar para los n Vertices (Punteros a la estructura).
    grafo->vertices = calloc(nVertices,sizeof(Vertice));
    //Allocamos lugar para el array de numeros para el orden de greedy.
    grafo->orden = malloc(nVertices*sizeof(u32));
    //Seteamos el orden inicial como el orden en el que entran.
    for(uint i = 0; i<nVertices; i++) grafo->orden[i] = i;
    grafo->nColores = 0;
  }
  else printf("Error en la creacion del grafo\n");

  //Leemos lineas hasta que ya tengamos nAristas BIEN ESCRITAS.
  //Nota: Saltea las aristas cargadas que ya existian.
  while(counter < nAristas){
    if(fgets(buffer, bufsize, stdin) != NULL) {
      //Escaneamos la linea.
      sscanf(buffer, "%s %s %s", p, vertice1String, vertice2String);
      //Inicio chequeo de valores.
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
      //Fin del chequeo.
      printf("Arista de %u a %u\n",vertice1,vertice2);
      //Solo sumamos al contador de aristas guardadas si no existia la arista.
      counter += agregarArista(grafo,vertice1, vertice2);
      printf("Vertices Restantes: %d\n",cantidadDeVerticesVacios(grafo));
    } else {
      errorFormatoInvalido(grafo);
      return NULL;
    }
  }
  //Devolvemos el grafo construido cuando se hayan leido todas las aristas.
  return grafo;
}

void errorFormatoInvalido(Grafo G){
  //Libero el grafo que habia creado hasta ahora.
  free(G->vertices);
  free(G);
  //Printeo mensaje de error.
  printf("### Formato de Grafo Invalido ###\n### Revisar formato DIMACS ###\n" );
}
