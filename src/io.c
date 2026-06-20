#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "io.h"

/*
 * io.c
 * ----
 * Leitura do mapa a partir de arquivo texto.
 *
 * Formato (ver data/mapa_exemplo.txt):
 *   <num_vertices> <num_arestas>
 *   <origem> <destino> <peso>
 *   ...
 * Linhas que comecam com '#' (comentarios) e linhas em branco sao ignoradas.
 */

#define TAM_LINHA 256

/* Le do arquivo a proxima linha "util": ignora linhas em branco e comentarios
 * (que comecam com '#', podendo ter espacos antes). Copia a linha em 'destino'.
 * Retorna 1 se conseguiu ler uma linha util, ou 0 ao chegar no fim do arquivo. */
static int ler_proxima_linha_util(FILE *arq, char *destino, int tamanho)
{
    while (fgets(destino, tamanho, arq) != NULL) {
        /* Pula os espacos iniciais para olhar o primeiro caractere real. */
        char *p = destino;
        while (*p == ' ' || *p == '\t')
            p++;

        /* Linha em branco ou comentario -> continua para a proxima. */
        if (*p == '\0' || *p == '\n' || *p == '\r' || *p == '#')
            continue;

        return 1;  /* achou uma linha com conteudo */
    }
    return 0;  /* fim do arquivo */
}

Grafo *io_carregar_mapa(const char *caminho_arquivo)
{
    char linha[TAM_LINHA];
    int num_vertices, num_arestas;
    int i;

    /* 1. Abre o arquivo em modo leitura. */
    FILE *arq = fopen(caminho_arquivo, "r");
    if (arq == NULL) {
        fprintf(stderr, "Erro: nao foi possivel abrir o arquivo '%s'.\n",
                caminho_arquivo);
        return NULL;
    }

    /* 2. Le o cabecalho: numero de vertices e de arestas. */
    if (!ler_proxima_linha_util(arq, linha, TAM_LINHA) ||
        sscanf(linha, "%d %d", &num_vertices, &num_arestas) != 2) {
        fprintf(stderr, "Erro: cabecalho invalido (esperado: num_vertices num_arestas).\n");
        fclose(arq);
        return NULL;
    }

    /* 3. Cria o grafo. */
    Grafo *g = grafo_criar(num_vertices);
    if (g == NULL) {
        fprintf(stderr, "Erro: falha ao criar o grafo.\n");
        fclose(arq);
        return NULL;
    }

    /* 4. Le cada aresta: origem, destino e peso. */
    for (i = 0; i < num_arestas; i++) {
        int origem, destino, peso;

        if (!ler_proxima_linha_util(arq, linha, TAM_LINHA) ||
            sscanf(linha, "%d %d %d", &origem, &destino, &peso) != 3) {
            fprintf(stderr, "Erro: aresta %d invalida ou faltando no arquivo.\n", i + 1);
            grafo_destruir(g);
            fclose(arq);
            return NULL;
        }

        grafo_adicionar_aresta(g, origem, destino, peso);
    }

    /* 5. Fecha o arquivo e devolve o grafo pronto. */
    fclose(arq);
    return g;
}
