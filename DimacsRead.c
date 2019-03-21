#include "def.h"

//Funcion principal de lectura del grafo por standard input en formato DIMACS.
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
  }

  //Si salgo del while, entonces no empieza con 'c', chequeamos si es del a forma correcta (DIMACS).
  //Escaneamos la linea a ver si tenemos 4 elementos.
  sscanf(buffer,"%s %s %s %s",p,edge,nAristasString,nVerticesString);

  //Convertimos los strings a numero (u32).
  nAristas = checkIfNumber(nAristasString);
  nVertices = checkIfNumber(nVerticesString);

  //Si no eran numeros, entonces atoi devuelve 0...
  //TODO: Se rompe si le paso un numero seguido de letras y numeros, toma el numero hasta la primer letra. Ej: 55fd98 = 55.
  if(nVertices == -1 || nAristas == -1){
    errorFormatoInvalido(grafo);
    return NULL;
  }

  //Chequeamos si las aristas son correctas.
  if(nAristas > nVertices*(nVertices-1) /2){
    printf("Demasiadas Aristas\n");
    return NULL;
  }

  //Chequeamos si el segundo string es 'edge' (DIMACS).
  if(!compararChar(edge,"edge",4)){
    errorFormatoInvalido(grafo);
    return NULL;
  }

  //Chequeamos si el primer string es 'p' (DIMACS).
  if(!compararChar(p,"p",1)){
    errorFormatoInvalido(grafo);
    return NULL;
  }

  printf("Aristas: %d, Vertices: %d\n", nAristas, nVertices );

  //Allocamos memoria para el grafo.
  grafo = malloc(sizeof(struct _Grafo));
  //Chequeamos si se alloco correctamente.
  if(grafo != NULL) {
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
  else {
    printf("Error en la creacion del grafo\n");
    return NULL;
  }

  //Leemos lineas hasta que ya tengamos nAristas BIEN ESCRITAS.
  //Nota: Saltea las aristas cargadas que ya existan.
  while(counter < nAristas){
    if(fgets(buffer, bufsize, stdin) != NULL) {
      //Escaneamos la linea.
      sscanf(buffer, "%s %s %s", p, vertice1String, vertice2String);

      //Inicio chequeo de valores.
      vertice1 = checkIfNumber(vertice1String);
      vertice2 = checkIfNumber(vertice2String);
      if(vertice1 == -1 || vertice2 == -1){
        errorFormatoInvalido(grafo);
        return NULL;
      }
      if(!compararChar(p,"e",1)){
        errorFormatoInvalido(grafo);
        return NULL;
      }
      //Fin del chequeo.

      //Solo sumamos al contador de aristas guardadas si no existia la arista.
      int incremento = agregarArista(grafo,vertice1, vertice2);
      if(incremento == -1){
        errorFormatoInvalido(grafo);
        return NULL;
      }
      counter += incremento;
    } else {
      errorFormatoInvalido(grafo);
      return NULL;
    }
  }
  //Devolvemos el grafo construido cuando se hayan leido todas las aristas.
  return grafo;
}

//Printea que se produjo un error y limpia la memoria que se haya utilizado.
void errorFormatoInvalido(Grafo G){
  //Libero el grafo que habia creado hasta ahora.
  if(G != NULL && G->vertices != NULL) free(G->vertices);
  free(G);
  //Printeo mensaje de error.
  printf("### Formato de Grafo Invalido ###\n### Revisar formato DIMACS ###\n" );
}

/*Devuelve -1 si no es un numero, o el numero si lo es.
NOTA: Tuvimos que hacerlo de esta forma porque solo con el atoi,
que devuelve 0 si no es un numero, no permitia ingresar el vertice 0*/
int checkIfNumber(char numero[]){
  /*TempNumero donde guardo el string precedido de un '1'.
  Si era un numero, sigue siendo un numero. Si no lo era, atoi devuelve un 1, ya que lee
  de izquierda a derecha buscando numeros.*/
  char tempNumero[11];
  tempNumero[0] = '1';
  //Copio el resto del string.
  for(uint i = 0;i<10;i++){
    tempNumero[i+1] = numero[i];
  }
  //Chequeo si da 1. Si no da, devuelvo el atoi del original.
  if(atoi(tempNumero) == 1) return -1;
  return atoi(numero);
}


bool compararChar(char input[], char correct[], int length){
  return (strncmp(input,correct,length) == 0);
}
