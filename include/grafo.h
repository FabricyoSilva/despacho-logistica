#ifndef GRAFO_H
#define GRAFO_H

/*
 * grafo.h
 * --------
 * Representacao do mapa urbano como um grafo direcionado e ponderado.
 *
 * Usamos MATRIZ DE ADJACENCIA alocada dinamicamente:
 *   - adj[i][j] = tempo (peso) da aresta i -> j
 *   - quando nao existe aresta i -> j, guardamos INFINITO
 *
 * Toda a memoria e gerenciada na mao (malloc/free), conforme exige o enunciado.
 */

/* Valor que representa "sem conexao direta" / distancia infinita.
 * Use um numero grande, mas que NAO cause overflow ao somar dois deles
 * (dist[i][k] + dist[k][j]) no Floyd-Warshall. */
#define INFINITO 1000000000

typedef struct {
    int   num_vertices;   /* quantidade de pontos (V) */
    int **adj;            /* matriz V x V com os pesos das arestas */
} Grafo;

/* Cria um grafo com 'num_vertices' vertices e nenhuma aresta (tudo INFINITO,
 * exceto a diagonal que vale 0). Retorna NULL em caso de falha de alocacao.
 * TODO: alocar a matriz adj dinamicamente (vetor de ponteiros + linhas). */
Grafo *grafo_criar(int num_vertices);

/* Libera toda a memoria do grafo (linhas, vetor de ponteiros e struct).
 * TODO: liberar na ordem correta para nao vazar memoria. */
void grafo_destruir(Grafo *g);

/* Adiciona/atualiza a aresta direcionada origem -> destino com o peso dado.
 * TODO: validar indices e atribuir g->adj[origem][destino] = peso. */
void grafo_add_aresta(Grafo *g, int origem, int destino, int peso);

/* Imprime a matriz de adjacencia no console (para conferencia/debug). */
void grafo_imprimir(const Grafo *g);

#endif /* GRAFO_H */
