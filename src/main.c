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

    grafo_destruir(g);
    return 0;
}
