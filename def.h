#ifndef def_h_
#define def_h_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef unsigned int u32;

typedef struct _Vertice *Vertice;
typedef struct _Grafo *Grafo;
typedef struct _Vecino *Vecino;

  struct _Vertice {
    u32 nombre;
    u32 grado;
    u32 color;
    Vecino vecinos;
  };

  struct _Vecino {
    Vertice vertice;
    Vecino siguienteVecino;
  };

  struct _Grafo {
    u32 nAristas;
    u32 nVertices;
    u32 nColores;
    Vertice *vertices;
    u32 *orden;
  };

void errorFormatoInvalido(Grafo G);

Grafo construirGrafo();

int cantidadDeVerticesVacios(Grafo G);

int agregarArista(Grafo G, u32 v1, u32 v2);

Vertice agregarVertice(Grafo G, u32 id);

bool esVecino(Vertice v, Vertice v2);

void agregarVecino(Vertice v, Vertice vecino);

Vertice vecinoNumero(Vertice v, u32 i);

void printVecinos(Vertice v);

void leerGrafo(Grafo g);

int checkIfNumber(char nummero[]);

#endif
