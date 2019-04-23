#include "Rii.h"
#include <time.h>

typedef unsigned int u32;


int main(void){
  clock_t tiempoInicio, tiempoFinal;
  double segundos;
  tiempoInicio = clock();
  /******************** Construccion del Grafo****************/
  Grafo grafo = ConstruccionDelGrafo();
  if(grafo == NULL) return 0;
  tiempoFinal = clock();
  segundos = (double)(tiempoFinal - tiempoInicio) / CLOCKS_PER_SEC;
  printf("Grafo Creado en %f segundos\n", segundos );

  /********************** Analisis del grafo **********************/
  if(Bipartito(grafo) == 1) printf("Es Bipartito\n");
  else printf("No es Bipartito\n");
  // RMBCchicogrande(grafo);
  // for(int i = 0; i < NumeroDeVertices(grafo); i++){
  //   printf("%u\n", ColorDelVertice(grafo,i));
  // }



  DestruccionDelGrafo(grafo);
  return 0;
}
