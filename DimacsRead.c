#include "def.h"



Grafo construirGrafo(){
  //El grafo
  Grafo grafo;
  //Largo maximo de los comentarios = 80.
  int bufsize = 80;

  //Variables para crear el grafo.
  u32 nLados;
  u32 nVertices;

  //Variables para construir el grafo.
  u32 vertice1;
  u32 vertice2;
  char vertice1String[10];
  char vertice2String[10];
  char nLadosString[10];
  char nVerticesString[10];
  uint counter;
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
      return 0;
    }
      printf("Es un comentario.\n");
  }
  printf("Fin de los comentarios.\n");

  //Si salgo del while, entonces no empieza con 'c', chequeamos si es del a forma correcta (DIMACS).
  //Escaneamos la linea a ver si tenemos 4 elementos.
  sscanf(buffer,"%s %s %s %s",p,edge,nLadosString,nVerticesString);

  //Convertimos los strings a numero (u32).
  nLados = atoi(nLadosString);
  nVertices = atoi(nVerticesString);

  //Si no eran numeros, entonces atoi devuelve 0...
  //TODO: Se rompe si le paso un numero seguido de letras y numeros, toma el numero hasta la primer letra. Ej: 55fd98 = 55.
  if(nVertices == 0 || nLados == 0){
    errorFormatoInvalido(grafo);
    return 0;
  }

  //Chequeamos si el segundo string es 'edge' (DIMACS).
  if(strncmp(edge,"edge",4) != 0){
    errorFormatoInvalido(grafo);
    return 0;
  }
  //Chequeamos si el primer string es 'p' (DIMACS).
  if(strncmp(p,"p",1) != 0){
    errorFormatoInvalido(grafo);
    return 0;
  }

  printf("Lados: %d, Vertices: %d\n", nLados, nVertices );
  //Allocamos memoria para el grafo.
  grafo = malloc(1*sizeof(struct _Grafo));
  //Chequeamos si se alloco correctamente.
  if(grafo != NULL) printf("Grafo Creado con exito\n");
  else printf("Error en la creacion del grafo\n");

  while(counter < nLados){
    if(fgets(buffer, bufsize, stdin) != NULL) {

      sscanf(buffer, "%s %s %s", p, vertice1String, vertice2String);
      vertice1 = atoi(vertice1String);
      vertice2 = atoi(vertice2String);
      if(strncmp(p,"e",1) != 0){
        errorFormatoInvalido(grafo);
        return 0;
      }
      if(vertice1 <= 0 || vertice2 <= 0){
        errorFormatoInvalido(grafo);
        return 0;
      }

      printf("Arista de %u a %u\n",vertice1,vertice2);
      counter++;
    }
  }
  return grafo;
}

void errorFormatoInvalido(Grafo G){
  //Libero el grafo que habia creado hasta ahora.
  free(G);
  //Printeo mensaje de error.
  printf("### Formato de Grafo Invalido ###\n### Revisar formato DIMACS ###\n" );
}
