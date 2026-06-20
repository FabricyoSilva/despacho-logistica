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
 * ATUALIZACAO INCREMENTAL (o diferencial do trabalho)
 * ---------------------------------------------------
 * Quando o peso de UMA aresta (u -> v) muda por causa do transito, NAO e
 * preciso rodar Floyd-Warshall inteiro (O(V^3)) de novo. Da para reajustar
 * toda a matriz dist em O(V^2).
 *
 * TODO: implementar a atualizacao em O(V^2) ao reduzir o peso de uma aresta.
 *       (aumentar o peso e o caso dificil — discutir no relatorio).
 */
void apsp_atualizar_aresta(ResultadoAPSP *r, int u, int v, int novo_peso);

#endif /* FLOYD_WARSHALL_H */
