#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "floyd_warshall.h"
#include "io.h"

/*
 * main.c
 * ------
 * Demonstracao INTERATIVA do sistema de despacho (menu no console).
 *
 * O mapa e carregado de um arquivo (data/mapa_exemplo.txt) e o Floyd-Warshall
 * e executado UMA vez no inicio. Depois o usuario escolhe, em tempo real, o que
 * quer ver/fazer:
 *
 *   1. Mostrar a matriz de adjacencia (tempos diretos).
 *   2. Mostrar a matriz de custos minimos (todos -> todos).
 *   3. Consultar uma rota especifica (origem -> destino).
 *   4. Simular uma ANOMALIA DE TRANSITO (mudar o peso de uma rua) e atualizar
 *      a matriz de forma incremental, mostrando o resultado.
 *   0. Sair.
 *
 * Uso: ./despacho data/mapa_exemplo.txt
 */

/* Le um inteiro do teclado de forma robusta. Grava o numero lido em *valor e
 * retorna 1 em caso de sucesso. Se a entrada nao for um numero, limpa o buffer
 * e pede de novo. Se a entrada TERMINAR (EOF: Ctrl+Z/Ctrl+D, pipe ou arquivo
 * que acaba), retorna 0 — assim o programa encerra em vez de entrar num laco
 * infinito imprimindo "Entrada invalida". */
static int ler_inteiro(const char *prompt, int *valor)
{
    int c;

    for (;;) {
        printf("%s", prompt);
        if (scanf("%d", valor) == 1) {
            /* descarta o resto da linha (incluindo o '\n') */
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            return 1;
        }

        /* Fim da entrada: nao ha mais nada para ler, sai para nao travar. */
        if (feof(stdin))
            return 0;

        /* entrada invalida (nao e numero): limpa o buffer e pede de novo */
        printf("Entrada invalida, tente novamente.\n");
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
}

/* Imprime o menu de opcoes. */
static void mostrar_menu(void)
{
    printf("\n=== Despacho de Logistica Urbana ===\n");
    printf("1. Mostrar matriz de adjacencia (tempos diretos)\n");
    printf("2. Mostrar matriz de custos minimos (APSP)\n");
    printf("3. Consultar rota (origem -> destino)\n");
    printf("4. Simular anomalia de transito (mudar peso de uma rua)\n");
    printf("0. Sair\n");
}

/* Opcao 3: pede origem/destino e imprime a rota reconstruida. */
static void opcao_consultar_rota(const ResultadoAPSP *r)
{
    int origem, destino;

    /* Se a entrada terminar (EOF) no meio, aborta a operacao. */
    if (!ler_inteiro("Origem: ", &origem) ||
        !ler_inteiro("Destino: ", &destino))
        return;

    apsp_imprimir_rota(r, origem, destino);
}

/* Opcao 4: pede a aresta e o novo peso, aplica a atualizacao incremental e
 * reimprime a matriz de custos minimos (antes/depois ao vivo). */
static void opcao_simular_anomalia(ResultadoAPSP *r, Grafo *g)
{
    int u, v, novo_peso;

    /* Se a entrada terminar (EOF) no meio, aborta a operacao. */
    if (!ler_inteiro("Aresta - origem (u): ", &u) ||
        !ler_inteiro("Aresta - destino (v): ", &v) ||
        !ler_inteiro("Novo peso (minutos): ", &novo_peso))
        return;

    /* Tempo de deslocamento nao pode ser negativo. Um peso negativo criaria um
     * ciclo de custo negativo, e a reconstrucao da rota entraria em laco
     * infinito (o caminho minimo deixaria de ser bem definido). */
    if (novo_peso < 0) {
        printf("Peso invalido: o tempo em minutos deve ser >= 0.\n");
        return;
    }

    /* Aplica a mudanca e escolhe a estrategia conforme o impacto:
     *   - reducao que melhora rotas  -> atualizacao incremental O(V^2);
     *   - aumento de peso            -> Floyd-Warshall completo O(V^3);
     *   - mudanca sem efeito         -> nada a recalcular. */
    int resultado = apsp_atualizar_aresta(r, g, u, v, novo_peso);

    if (resultado == 1) {
        printf("\nRua %d->%d atualizada para %d min (peso REDUZIU).\n", u, v, novo_peso);
        printf("Estrategia: atualizacao incremental O(V^2).\n");
    } else if (resultado == 0) {
        printf("\nRua %d->%d atualizada para %d min (peso AUMENTOU).\n", u, v, novo_peso);
        printf("Estrategia: Floyd-Warshall completo O(V^3) re-executado.\n");
    } else if (resultado == 2) {
        printf("\nRua %d->%d atualizada para %d min, mas nenhum caminho minimo mudou.\n",
               u, v, novo_peso);
        return;
    } else {
        printf("Erro ao atualizar a aresta.\n");
        return;
    }

    printf("\nNova matriz de custos minimos:\n");
    apsp_imprimir_matriz(r);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_do_mapa>\n", argv[0]);
        return 1;
    }

    /* 1. Carrega o mapa do arquivo. */
    Grafo *g = io_carregar_mapa(argv[1]);
    if (g == NULL) {
        fprintf(stderr, "Erro ao carregar o mapa.\n");
        return 1;
    }

    /* 2. Roda o Floyd-Warshall uma vez (APSP + matriz de reconstrucao). */
    ResultadoAPSP *r = floyd_warshall_executar(g);
    if (r == NULL) {
        fprintf(stderr, "Erro ao executar o Floyd-Warshall.\n");
        grafo_destruir(g);
        return 1;
    }

    printf("Mapa carregado: %d pontos.\n", g->num_vertices);

    /* 3. Laco do menu interativo. */
    int opcao = -1;
    while (opcao != 0) {
        mostrar_menu();

        /* EOF na entrada: encerra de forma limpa, como se fosse a opcao 0. */
        if (!ler_inteiro("Escolha: ", &opcao))
            break;

        switch (opcao) {
        case 0:
            break;  /* sai do laco (condicao do while) */
        case 1:
            printf("\n== Matriz de adjacencia (tempos diretos) ==\n");
            grafo_imprimir(g);
            break;
        case 2:
            printf("\n== Matriz de custos minimos (todos -> todos) ==\n");
            apsp_imprimir_matriz(r);
            break;
        case 3:
            opcao_consultar_rota(r);
            break;
        case 4:
            opcao_simular_anomalia(r, g);
            break;
        default:
            printf("Opcao invalida. Escolha um numero do menu.\n");
            break;
        }
    }

    /* 4. Libera tudo. */
    apsp_destruir(r);
    grafo_destruir(g);
    printf("Encerrado.\n");
    return 0;
}
