#ifndef def_h_
#define def_h_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned int u32;

typedef struct _Vertice *Vertice;
typedef struct _Grafo *Grafo;
typedef struct _Vecino *Vecino;

  struct _Vertice {
    u32 nombre;
    u32 hash;
    u32 grado;
    u32 color;
    u32 capacidadVecinos;
    Vertice *vecinos;
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

bool compararChar(char input[], char correct[], int length);

u32 hashFunc(u32 id, u32 v);

u32 Greedy(Grafo G);

#endif
