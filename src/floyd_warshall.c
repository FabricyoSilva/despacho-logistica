#include <stdio.h>
#include <stdlib.h>
#include "floyd_warshall.h"

/*
 * floyd_warshall.c
 * ----------------
 * Implementacao do APSP (Floyd-Warshall) + reconstrucao de rota + update.
 */

/* ---------- auxiliares de alocacao de matriz V x V de int ---------- */

/* Aloca uma matriz n x n de inteiros. Retorna NULL em caso de falha
 * (liberando o que ja havia sido alocado). */
static int **alocar_matriz(int n)
{
    int i, j;
    int **m = malloc(n * sizeof(int *));
    if (m == NULL)
        return NULL;

    for (i = 0; i < n; i++) {
        m[i] = malloc(n * sizeof(int));
        if (m[i] == NULL) {
            for (j = 0; j < i; j++)
                free(m[j]);
            free(m);
            return NULL;
        }
    }
    return m;
}

/* Libera uma matriz n x n alocada por alocar_matriz. */
static void liberar_matriz(int **m, int n)
{
    int i;
    if (m == NULL)
        return;
    for (i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

/* ------------------------------------------------------------------ */

ResultadoAPSP *floyd_warshall_executar(const Grafo *g)
{
    int i, j, k, V;

    if (g == NULL)
        return NULL;

    V = g->num_vertices;

    /* 1. Aloca a struct e as duas matrizes (dist e prox). */
    ResultadoAPSP *r = malloc(sizeof(ResultadoAPSP));
    if (r == NULL)
        return NULL;

    r->num_vertices = V;
    r->dist = alocar_matriz(V);
    r->prox = alocar_matriz(V);
    if (r->dist == NULL || r->prox == NULL) {
        liberar_matriz(r->dist, V);
        liberar_matriz(r->prox, V);
        free(r);
        return NULL;
    }

    /* 2. Inicializa a partir do grafo:
     *    - dist comeca igual aos tempos diretos da matriz de adjacencia;
     *    - prox[i][j] = j se existe aresta direta i->j; senao -1.
     *    (na diagonal adj[i][i] = 0 != INFINITO, entao prox[i][i] = i) */
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            r->dist[i][j] = g->adj[i][j];
            if (g->adj[i][j] != INFINITO)
                r->prox[i][j] = j;
            else
                r->prox[i][j] = -1;
        }
    }

    /* 3. Nucleo do Floyd-Warshall: para cada intermediario k, testa se passar
     *    por k encurta o caminho de i ate j. O(V^3).
     *    Guarda: so relaxa se ambos os trechos sao finitos (evita overflow e
     *    "somar com infinito"). */
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (r->dist[i][k] != INFINITO &&
                    r->dist[k][j] != INFINITO &&
                    r->dist[i][k] + r->dist[k][j] < r->dist[i][j]) {
                    r->dist[i][j] = r->dist[i][k] + r->dist[k][j];
                    /* o proximo passo de i->j passa a ser o mesmo de i->k */
                    r->prox[i][j] = r->prox[i][k];
                }
            }
        }
    }

    return r;
}

void apsp_destruir(ResultadoAPSP *r)
{
    if (r == NULL)
        return;
    liberar_matriz(r->dist, r->num_vertices);
    liberar_matriz(r->prox, r->num_vertices);
    free(r);
}

void apsp_imprimir_matriz(const ResultadoAPSP *r)
{
    int i, j;

    if (r == NULL)
        return;

    /* Cabecalho com os indices das colunas (destinos). */
    printf("      ");
    for (j = 0; j < r->num_vertices; j++)
        printf("%6d", j);
    printf("\n");

    /* Uma linha por vertice de origem. */
    for (i = 0; i < r->num_vertices; i++) {
        printf("%4d |", i);
        for (j = 0; j < r->num_vertices; j++) {
            if (r->dist[i][j] == INFINITO)
                printf("%6s", "INF");
            else
                printf("%6d", r->dist[i][j]);
        }
        printf("\n");
    }
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
