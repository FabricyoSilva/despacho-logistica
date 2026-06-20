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
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_do_mapa>\n", argv[0]);
        return 1;
    }

    /* TODO: descomentar conforme as funcoes forem implementadas.

    Grafo *g = io_carregar_mapa(argv[1]);
    if (g == NULL) {
        fprintf(stderr, "Erro ao carregar o mapa.\n");
        return 1;
    }

    printf("== Matriz de adjacencia (tempos diretos) ==\n");
    grafo_imprimir(g);

    ResultadoAPSP *r = floyd_warshall_executar(g);

    printf("\n== Matriz de custos minimos (todos -> todos) ==\n");
    apsp_imprimir_matriz(r);

    printf("\n== Rota de 0 ate %d ==\n", g->num_vertices - 1);
    apsp_imprimir_rota(r, 0, g->num_vertices - 1);

    printf("\n== Anomalia de transito: rua 0->1 ficou mais rapida (peso 1) ==\n");
    apsp_atualizar_aresta(r, 0, 1, 1);
    apsp_imprimir_matriz(r);

    apsp_destruir(r);
    grafo_destruir(g);
    */

    printf("Esqueleto do projeto. Implemente os modulos em src/.\n");
    return 0;
}
