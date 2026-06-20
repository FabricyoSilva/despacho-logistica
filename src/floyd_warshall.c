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
    int u;

    if (r == NULL)
        return;

    /* Indices fora do intervalo. */
    if (origem < 0 || origem >= r->num_vertices ||
        destino < 0 || destino >= r->num_vertices) {
        printf("Rota %d -> %d: indices invalidos.\n", origem, destino);
        return;
    }

    /* Sem caminho possivel entre os dois pontos. */
    if (r->prox[origem][destino] == -1) {
        printf("Rota %d -> %d: nao existe caminho.\n", origem, destino);
        return;
    }

    /* Reconstroi seguindo a matriz prox: a cada passo, vai para o proximo
     * vertice no caminho ate chegar no destino. */
    printf("Rota %d -> %d (custo %d): %d", origem, destino,
           r->dist[origem][destino], origem);
    u = origem;
    while (u != destino) {
        u = r->prox[u][destino];
        printf(" -> %d", u);
    }
    printf("\n");
}

void apsp_atualizar_aresta(ResultadoAPSP *r, int u, int v, int novo_peso)
{
    int i, j, V;

    if (r == NULL)
        return;

    V = r->num_vertices;

    if (u < 0 || u >= V || v < 0 || v >= V) {
        fprintf(stderr, "Aviso: atualizacao (%d -> %d) ignorada (indice invalido).\n",
                u, v);
        return;
    }

    /* Atualizacao incremental em O(V^2), valida quando o peso DIMINUI.
     * Se a nova aresta u->v nao melhora o que ja temos, nada muda. */
    if (novo_peso >= r->dist[u][v])
        return;

    /* A aresta direta u->v ficou mais rapida: registra. */
    r->dist[u][v] = novo_peso;
    r->prox[u][v] = v;

    /* Propaga: para todo par (i, j), verifica se o caminho que usa a aresta
     * melhorada (i ... u -> v ... j) ficou mais curto que o atual. */
    for (i = 0; i < V; i++) {
        if (r->dist[i][u] == INFINITO)   /* i nem chega em u: nada a fazer */
            continue;
        for (j = 0; j < V; j++) {
            if (r->dist[v][j] == INFINITO) /* de v nao se chega em j */
                continue;
            if (r->dist[i][u] + novo_peso + r->dist[v][j] < r->dist[i][j]) {
                r->dist[i][j] = r->dist[i][u] + novo_peso + r->dist[v][j];
                r->prox[i][j] = r->prox[i][u];
            }
        }
    }
}
