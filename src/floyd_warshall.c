#include <stdio.h>
#include <stdlib.h>
#include "floyd_warshall.h"

/*
 * floyd_warshall.c
 * ----------------
 * Implementacao do APSP (Floyd-Warshall) + reconstrucao de rota + update.
 *
 * >>> ESQUELETO: as funcoes abaixo estao com TODO. Preencha a logica. <<<
 */

ResultadoAPSP *floyd_warshall_executar(const Grafo *g)
{
    /* TODO:
     * 1. alocar ResultadoAPSP, dist[V][V] e prox[V][V].
     * 2. inicializar dist[i][j] = g->adj[i][j].
     *    inicializar prox[i][j] = j quando existe aresta, senao -1.
     * 3. nucleo do algoritmo (cuidado com overflow ao somar INFINITO):
     *
     *    for (k = 0; k < V; k++)
     *      for (i = 0; i < V; i++)
     *        for (j = 0; j < V; j++)
     *          if (dist[i][k] + dist[k][j] < dist[i][j]) {
     *              dist[i][j] = dist[i][k] + dist[k][j];
     *              prox[i][j] = prox[i][k];
     *          }
     */
    (void) g;
    return NULL;
}

void apsp_destruir(ResultadoAPSP *r)
{
    /* TODO: liberar dist, prox e a struct. */
    (void) r;
}

void apsp_imprimir_matriz(const ResultadoAPSP *r)
{
    /* TODO: imprimir dist[i][j] (INFINITO -> "INF"). */
    (void) r;
}

void apsp_imprimir_rota(const ResultadoAPSP *r, int origem, int destino)
{
    /* TODO:
     * se prox[origem][destino] == -1 -> "sem rota".
     * senao seguir: u = origem; imprime u; enquanto u != destino:
     *   u = prox[u][destino]; imprime u;
     */
    (void) r; (void) origem; (void) destino;
}

void apsp_atualizar_aresta(ResultadoAPSP *r, int u, int v, int novo_peso)
{
    /* TODO (diferencial do trabalho):
     * Reduzir o peso da aresta u->v e reajustar a matriz inteira em O(V^2):
     *
     *   if (novo_peso < dist[u][v]) {
     *       dist[u][v] = novo_peso; prox[u][v] = v;
     *       for (i = 0; i < V; i++)
     *         for (j = 0; j < V; j++)
     *           if (dist[i][u] + novo_peso + dist[v][j] < dist[i][j]) {
     *               dist[i][j] = dist[i][u] + novo_peso + dist[v][j];
     *               prox[i][j] = prox[i][u];
     *           }
     *   }
     *
     * Observacao para o relatorio: AUMENTAR um peso e o caso dificil e
     * normalmente exige recomputo (discutir essa limitacao).
     */
    (void) r; (void) u; (void) v; (void) novo_peso;
}
