#ifndef Rii_h_
#define Rii_h_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef unsigned int u32;

typedef struct VerticeSt *Vertice;
typedef struct GrafoSt *Grafo;

  struct VerticeSt {
    u32 nombre;
    u32 hash;
    u32 grado;
    u32 color;
    u32 capacidadVecinos;
    Vertice *vecinos;
  };

  struct GrafoSt {
    u32 nAristas;
    u32 nVertices;
    u32 nVerticesCargados;
    u32 nColores;
    Vertice *vertices;
  };


/* DimacsRead.c */
Grafo ConstruccionDelGrafo();

void ErrorLecturaLinea(Grafo G, u32 counter);

void ErrorPrimeraLinea(Grafo G);

int CheckIfNumber(char nummero[]);

bool CompararChar(char input[], char correct[], int length);


/* GrafoConstruccion.c */

int AgregarArista(Grafo G, u32 v1, u32 v2);

Vertice AgregarVertice(Grafo G, u32 id);

void AgregarVecino(Vertice v, Vertice vecino);

u32 HashFunc(u32 id, u32 v);

void ResetColores(Grafo G);

/* GrafoInformacion.c */

u32 NumeroDeVertices(Grafo G);

u32 NumeroDeAristas(Grafo G);

u32 NumeroDeColores(Grafo G);

u32 NumeroDeVecinos(Grafo G, u32 i);

bool EsVecino(Vertice v, Vertice v2);

u32 NombreJotaesimoVecino(Grafo G, u32 i, u32 j);

u32 ColorJotaesimoVecino(Grafo G, u32 i, u32 j);

void PrintVecinos(Vertice v);

void LeerGrafo(Grafo g);




/* Greedy.c */

u32 Greedy(Grafo G);


/* Bipartito.c */
int Bipartito(Grafo G);

int DfsCheck(Vertice V, u32 color);


/* Ordenes.c */

void Ordenar(Grafo G,int (*compar)(const void *, const void*));

char OrdenNatural(Grafo G);

int ComparadorNatural(const void * a, const void * b);

char OrdenWelshPowell(Grafo G);

int ComparadorWelshPowell(const void * a, const void * b);

char OrdenRMBCnormal(Grafo G);

int ComparadorRMBCnormal(const void * a, const void * b);

char OrdenRMBCrevierte(Grafo G);

int ComparadorRMBCrevierte(const void* a, const void* b);

char OrdenRMBCchicogrande(Grafo G);

int ComparadorRMBCchicogrande(const void* a, const void* b);

#endif
