# Sistema de Despacho de Logística Urbana

 Seminário de Estruturas Avançadas** (Proposta de Projeto 5).

## Integrantes do grupo

- Fabricyo Silva
- Pedro Afonso Cavalcante
- Mateus Cavalcante
- Juliana Miranda
- Luendell dos Reis
- Álife Roberto Soares

## Problema

Uma startup de entregas opera numa região metropolitana modelada como um
**grafo direcionado e ponderado**:

- **Vértices** = pontos de coleta/entrega
- **Arestas** = ruas/conexões
- **Peso da aresta** = tempo de deslocamento em minutos (varia com o trânsito)

O centro de controle precisa de uma **matriz de caminhos mínimos entre TODOS
os pares de pontos** (All-Pairs Shortest Path — APSP), e precisa atualizá-la de
forma eficiente quando o trânsito altera o peso de uma rua.

## Solução adotada

| Necessidade | Técnica |
|---|---|
| Distância de todos para todos | **Algoritmo de Floyd-Warshall** — O(V³) tempo, O(V²) espaço |
| Reconstrução das rotas (não só o tempo) | Matriz de predecessores `prox[i][j]` |
| Anomalia de trânsito (1 aresta muda) | **Atualização incremental** em O(V²) (sem rodar tudo de novo) |

A estrutura (matriz de adjacência / distâncias) é construída do zero com
alocação dinâmica (`malloc`/`free`), conforme exige o enunciado — sem
bibliotecas de terceiros para a estrutura de dados.

## Estrutura do repositório

```
despacho-logistica/
├── include/          # Cabeçalhos (.h) — structs e protótipos
│   ├── grafo.h
│   ├── floyd_warshall.h
│   └── io.h
├── src/              # Implementações (.c)
│   ├── main.c
│   ├── grafo.c
│   ├── floyd_warshall.c
│   └── io.c
├── data/             # Massas de teste (mapas de exemplo)
│   └── mapa_exemplo.txt
├── Makefile
└── README.md
```

> A fundamentação teórica (relatório escrito) é entregue à parte — este
> repositório contém **apenas a implementação do código**.

## Como compilar e executar

```bash
make                              # compila e gera o executavel ./despacho
./despacho data/mapa_exemplo.txt  # roda passando o mapa como argumento
```

Ou, em um passo só, usando o atalho do Makefile:

```bash
make run     # compila e ja roda com data/mapa_exemplo.txt
make clean   # remove os objetos (build/) e o executavel
```

## Usando o sistema (menu interativo)

Ao iniciar, o programa carrega o mapa do arquivo informado, executa o
Floyd-Warshall **uma vez** e abre um menu no console. Digite o número da
opção e pressione Enter:

```
=== Despacho de Logistica Urbana ===
1. Mostrar matriz de adjacencia (tempos diretos)
2. Mostrar matriz de custos minimos (APSP)
3. Consultar rota (origem -> destino)
4. Simular anomalia de transito (mudar peso de uma rua)
0. Sair
```

- **1** — matriz de adjacência: os tempos diretos de cada rua (`INF` = sem ligação).
- **2** — matriz de custos mínimos: o menor tempo entre todos os pares de pontos.
- **3** — consulta uma rota: pede a origem e o destino e imprime o caminho
  reconstruído com o custo total (ex.: `0 -> 2 -> 1 -> 3 -> 4`).
- **4** — anomalia de trânsito: pede a aresta (`u`, `v`) e o novo peso, aplica a
  atualização incremental em O(V²) e reimprime a matriz de custos mínimos.
  > A atualização incremental só reotimiza quando o peso **diminui**; ao informar
  > um peso maior, o programa avisa que nada muda (aumento de peso é o caso
  > difícil, discutido no relatório).
- **0** — encerra o programa.

## Formato do arquivo de mapa

Um arquivo texto (ver `data/mapa_exemplo.txt`):

```
<num_vertices> <num_arestas>
<origem> <destino> <peso_em_minutos>
...
```

- Os vértices são numerados de `0` a `num_vertices - 1`.
- Cada aresta é direcionada (`origem -> destino`).
- Linhas em branco e linhas que começam com `#` (comentários) são ignoradas.

Exemplo (5 pontos, 8 ruas):

```
5 8
0 1 4
0 2 1
2 1 1
1 3 2
3 2 5
2 3 8
3 4 3
4 0 7
```
