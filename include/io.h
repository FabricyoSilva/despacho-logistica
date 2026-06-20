#ifndef IO_H
#define IO_H

#include "grafo.h"

/*
 * io.h
 * ----
 * Leitura do mapa urbano a partir de um arquivo texto.
 *
 * Formato sugerido do arquivo (ver data/mapa_exemplo.txt):
 *
 *   <num_vertices> <num_arestas>
 *   <origem> <destino> <peso>
 *   <origem> <destino> <peso>
 *   ...
 *
 * Os vertices sao numerados de 0 a num_vertices-1.
 */

/* Le o arquivo e devolve um Grafo pronto (ja com as arestas adicionadas).
 * Retorna NULL se o arquivo nao abrir ou estiver mal formatado.
 * TODO: abrir arquivo, ler cabecalho, criar grafo, ler cada aresta. */
Grafo *io_carregar_mapa(const char *caminho_arquivo);

#endif /* IO_H */
