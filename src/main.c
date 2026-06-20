#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "floyd_warshall.h"
#include "io.h"

/*
 * main.c
 * ------
 * Fluxo da demonstracao (roteiro para a apresentacao):
 *
 *   1. Carregar o mapa de um arquivo (data/mapa_exemplo.txt).
 *   2. Mostrar a matriz de adjacencia (tempos diretos).
 *   3. Rodar Floyd-Warshall e mostrar a matriz de custos minimos (todos->todos).
 *   4. Reconstruir e mostrar uma rota especifica (origem -> destino).
 *   5. Simular uma ANOMALIA DE TRANSITO (mudar o peso de uma aresta) e
 *      atualizar a matriz de forma incremental, mostrando o antes/depois.
 *
 * >>> ESQUELETO: descomente e preencha conforme implementar os modulos. <<<
 */

int main(void)
{
    /* -----------------------------------------------------------------
     * TESTE TEMPORARIO do modulo grafo.
     * Enquanto o io.c (leitura de arquivo) nao esta pronto, montamos um
     * grafo na mao para conferir grafo_criar / adicionar_aresta / imprimir.
     * Depois este bloco sera substituido pelo fluxo real da demonstracao.
     * ----------------------------------------------------------------- */

    Grafo *g = grafo_criar(5);
    if (g == NULL) {
        fprintf(stderr, "Erro ao criar o grafo.\n");
        return 1;
    }

    /* Mesmas arestas do data/mapa_exemplo.txt (5 vertices, 8 arestas). */
    grafo_adicionar_aresta(g, 0, 1, 4);
    grafo_adicionar_aresta(g, 0, 2, 1);
    grafo_adicionar_aresta(g, 2, 1, 1);
    grafo_adicionar_aresta(g, 1, 3, 2);
    grafo_adicionar_aresta(g, 3, 2, 5);
    grafo_adicionar_aresta(g, 2, 3, 8);
    grafo_adicionar_aresta(g, 3, 4, 3);
    grafo_adicionar_aresta(g, 4, 0, 7);

    printf("== Matriz de adjacencia (tempos diretos) ==\n");
    grafo_imprimir(g);

    grafo_destruir(g);
    return 0;
}
