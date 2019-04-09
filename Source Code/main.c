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
  if(Bipartito(grafo)) printf("Es Bipartito\n");
  OrdenNatural(grafo);
  u32 colores = Greedy(grafo);
  printf("Greedy con Orden Natural pinto con %u colores\n", colores);

  OrdenWelshPowell(grafo);
  colores = Greedy(grafo);
  printf("Greedy con Orden WelshPowell pinto con %u colores\n", colores);

  // tiempoInicio = clock();
  // for(uint i = 0; i < 3000; i++){
  //   Greedy(grafo);
  // }
  // tiempoFinal = clock();
  // segundos = (double)(tiempoFinal - tiempoInicio) / CLOCKS_PER_SEC;
  // printf("3000 Greedy en %f segundos\n", segundos );

  DestruirGrafo(grafo);
  return 0;
}
