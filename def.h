#ifndef def_h_
#define def_h_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    u32 nAristas;
    u32 nVertices;
    u32 nColores;
    struct _Vertice *vertices;
    u32 *orden;
  };

void errorFormatoInvalido(Grafo G);

Grafo construirGrafo();

void AgregarVertice(Grafo G, u32 id);

int CantidadDeVertices(Grafo G);

#endif
