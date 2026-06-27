#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include "grafo.h"

/*
 * floyd_warshall.h
 * ----------------
 * Algoritmo de caminhos minimos entre TODOS os pares de vertices (APSP).
 *
 * Complexidade (pior caso):
 *   - Tempo:  O(V^3)
 *   - Espaco: O(V^2)
 *
 * Guardamos duas matrizes:
 *   - dist[i][j] = menor tempo conhecido de i ate j
 *   - prox[i][j] = proximo vertice no caminho de i ate j (reconstroi a rota)
 */

typedef struct {
    int   num_vertices;
    int **dist;   /* matriz de distancias minimas V x V */
    int **prox;   /* matriz "next" para reconstruir caminhos V x V */
} ResultadoAPSP;

/* Executa Floyd-Warshall sobre o grafo e devolve as matrizes dist/prox.
 * TODO: inicializar dist a partir de g->adj e prox; rodar os 3 lacos (k,i,j). */
ResultadoAPSP *floyd_warshall_executar(const Grafo *g);

/* Libera a memoria do resultado. */
void apsp_destruir(ResultadoAPSP *r);

/* Imprime a matriz de distancias minimas (INFINITO -> "INF"). */
void apsp_imprimir_matriz(const ResultadoAPSP *r);

/* Reconstroi e imprime a rota de 'origem' ate 'destino' usando prox[][].
 * TODO: seguir prox[origem][destino] ate chegar no destino. */
void apsp_imprimir_rota(const ResultadoAPSP *r, int origem, int destino);

/*
 * ATUALIZACAO DE ARESTA (anomalia de transito)
 * --------------------------------------------
 * Atualiza o peso da aresta u->v no grafo g e recalcula a matriz APSP em r.
 *
 * - Reducao de peso: atualizacao incremental em O(V^2) — rapido.
 * - Aumento de peso: re-executa Floyd-Warshall completo em O(V^3), pois
 *   caminhos que passavam pela aresta agora podem ser invalidos e nao ha
 *   como corrigir isso de forma incremental sem uma re-exploracao global.
 *
 * Retorna 1 se o peso foi reduzido (incremental), 0 se foi aumentado (FW
 * completo). Retorna -1 em caso de erro.
 */
int apsp_atualizar_aresta(ResultadoAPSP *r, Grafo *g, int u, int v, int novo_peso);

#endif /* FLOYD_WARSHALL_H */
