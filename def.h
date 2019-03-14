#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;

typedef struct _Vertice *Vertice;
typedef struct _Grafo *Grafo;

  struct _Vertice {
    u32 nombre;
    u32 grado;
    u32 color;
    Vertice *vecinos;
  };

  struct _Grafo {
    u32 nLados;
    u32 nVertices;
    u32 nColores;
    Vertice *vertices;
    u32 *orden;
  };
