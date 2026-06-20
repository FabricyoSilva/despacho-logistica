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

int main(int argc, char *argv[])
{
    /* -----------------------------------------------------------------
     * TESTE do modulo io: carrega o mapa de um arquivo e imprime a matriz.
     * Uso: ./despacho data/mapa_exemplo.txt
     * Os modulos floyd_warshall (APSP, rota e update) serao ligados depois.
     * ----------------------------------------------------------------- */

    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_do_mapa>\n", argv[0]);
        return 1;
    }

    Grafo *g = io_carregar_mapa(argv[1]);
    if (g == NULL) {
        fprintf(stderr, "Erro ao carregar o mapa.\n");
        return 1;
    }

    printf("== Matriz de adjacencia (tempos diretos) ==\n");
    grafo_imprimir(g);

    ResultadoAPSP *r = floyd_warshall_executar(g);
    if (r == NULL) {
        fprintf(stderr, "Erro ao executar o Floyd-Warshall.\n");
        grafo_destruir(g);
        return 1;
    }

    printf("\n== Matriz de custos minimos (todos -> todos) ==\n");
    apsp_imprimir_matriz(r);

    /* Reconstrucao de rota: mostra o caminho real, nao so o tempo. */
    printf("\n== Rotas reconstruidas ==\n");
    apsp_imprimir_rota(r, 0, 1);
    apsp_imprimir_rota(r, 1, 0);
    apsp_imprimir_rota(r, 0, 4);

    /* Anomalia de transito: a aresta 0->1 fica mais rapida (de 4 para 1 min).
     * Atualizacao incremental em O(V^2), sem recomputar tudo (O(V^3)). */
    printf("\n== Anomalia de transito: rua 0->1 caiu de 4 para 1 minuto ==\n");
    apsp_atualizar_aresta(r, 0, 1, 1);
    apsp_imprimir_matriz(r);

    printf("\n== Mesma rota apos a atualizacao ==\n");
    apsp_imprimir_rota(r, 0, 1);

    apsp_destruir(r);
    grafo_destruir(g);
    return 0;
}
