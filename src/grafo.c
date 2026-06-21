#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/*
 * grafo.c
 * --------
 * Implementacao da matriz de adjacencia dinamica.
 */

Grafo *grafo_criar(int num_vertices)
{
    int i, j;

    /* Numero de vertices invalido. */
    if (num_vertices <= 0)
        return NULL;

    /* 1. Aloca a struct Grafo. */
    Grafo *g = malloc(sizeof(Grafo));
    if (g == NULL)
        return NULL;

    g->num_vertices = num_vertices;

    /* 2. Aloca o vetor de ponteiros (uma posicao por linha da matriz). */
    g->adj = malloc(num_vertices * sizeof(int *));
    if (g->adj == NULL) {
        free(g);
        return NULL;
    }

    /* 3. Aloca cada linha (num_vertices colunas de int). */
    for (i = 0; i < num_vertices; i++) {
        g->adj[i] = malloc(num_vertices * sizeof(int));
        if (g->adj[i] == NULL) {
            /* Falhou no meio: libera as linhas ja alocadas para nao vazar. */
            for (j = 0; j < i; j++)
                free(g->adj[j]);
            free(g->adj);
            free(g);
            return NULL;
        }
    }

    /* 4. Inicializa: sem aresta = INFINITO; diagonal (i->i) = 0. */
    for (i = 0; i < num_vertices; i++) {
        for (j = 0; j < num_vertices; j++) {
            if (i == j)
                g->adj[i][j] = 0;
            else
                g->adj[i][j] = INFINITO;
        }
    }

    return g;
}

void grafo_destruir(Grafo *g)
{
    int i;

    if (g == NULL)
        return;

    /* Libera na ordem INVERSA da alocacao em grafo_criar: */
    if (g->adj != NULL) {
        /* 1. cada linha da matriz */
        for (i = 0; i < g->num_vertices; i++)
            free(g->adj[i]);
        /* 2. o vetor de ponteiros */
        free(g->adj);
    }

    /* 3. a struct */
    free(g);
}

void grafo_adicionar_aresta(Grafo *g, int origem, int destino, int peso)
{
    if (g == NULL)
        return;

    /* Valida os indices: precisam estar dentro de [0, num_vertices). */
    if (origem < 0 || origem >= g->num_vertices ||
        destino < 0 || destino >= g->num_vertices) {
        fprintf(stderr,
                "Aviso: aresta (%d -> %d) ignorada (vertice fora do intervalo).\n",
                origem, destino);
        return;
    }

    /* Grafo direcionado: define apenas o sentido origem -> destino. */
    g->adj[origem][destino] = peso;
}

void grafo_imprimir(const Grafo *g)
{
    int i, j;

    if (g == NULL)
        return;

    /* Cabecalho com os indices das colunas. */
    printf("      ");
    for (j = 0; j < g->num_vertices; j++)
        printf("%6d", j);
    printf("\n");

    /* Uma linha por vertice de origem. */
    for (i = 0; i < g->num_vertices; i++) {
        printf("%4d |", i);
        for (j = 0; j < g->num_vertices; j++) {
            if (g->adj[i][j] == INFINITO)
                printf("%6s", "INF");
            else
                printf("%6d", g->adj[i][j]);
        }
        printf("\n");
    }
}
