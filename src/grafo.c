#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/*
 * grafo.c
 * --------
 * Implementacao da matriz de adjacencia dinamica.
 *
 * >>> ESQUELETO: as funcoes abaixo estao com TODO. Preencha a logica. <<<
 */

Grafo *grafo_criar(int num_vertices)
{
    /* TODO:
     * 1. malloc da struct Grafo
     * 2. malloc do vetor de ponteiros (num_vertices linhas)
     * 3. malloc de cada linha (num_vertices colunas)
     * 4. inicializar: adj[i][j] = INFINITO, e adj[i][i] = 0
     * 5. tratar falhas de alocacao (retornar NULL)
     */
    (void) num_vertices;
    return NULL;
}

void grafo_destruir(Grafo *g)
{
    /* TODO: liberar cada linha, depois o vetor de ponteiros, depois a struct. */
    (void) g;
}

void grafo_add_aresta(Grafo *g, int origem, int destino, int peso)
{
    /* TODO: validar indices (0 <= idx < num_vertices) e fazer
     *       g->adj[origem][destino] = peso; */
    (void) g; (void) origem; (void) destino; (void) peso;
}

void grafo_imprimir(const Grafo *g)
{
    /* TODO: percorrer a matriz e imprimir (INFINITO -> "INF"). */
    (void) g;
}
