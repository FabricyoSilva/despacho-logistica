#include <stdio.h>
#include <stdlib.h>
#include "io.h"

/*
 * io.c
 * ----
 * Leitura do mapa a partir de arquivo texto.
 *
 * >>> ESQUELETO: funcao com TODO. Preencha a logica. <<<
 */

Grafo *io_carregar_mapa(const char *caminho_arquivo)
{
    /* TODO:
     * 1. abrir o arquivo (fopen) em modo leitura; tratar erro.
     * 2. ler "num_vertices num_arestas".
     * 3. criar o grafo com grafo_criar(num_vertices).
     * 4. para cada aresta: ler "origem destino peso" e
     *    chamar grafo_add_aresta(...).
     * 5. fechar o arquivo e retornar o grafo.
     */
    (void) caminho_arquivo;
    return NULL;
}
