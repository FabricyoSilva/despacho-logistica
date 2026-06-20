# Sistema de Despacho de Logística Urbana

Projeto da **Atividade 3 — Seminário de Estruturas Avançadas** (Proposta de Projeto 5).

## Integrantes do grupo

- Fabricyo Silva
- Pedro Afonso
- Mateus Cavalcante
- Juliana Miranda
- Luendell dos Reis
- Álife Roberto

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
make
./despacho data/mapa_exemplo.txt
```

## Divisão de tarefas sugerida (para o grupo)

- [ ] **Entrada/saída** (`io.c`): ler o mapa de um arquivo e imprimir a matriz.
- [ ] **Grafo** (`grafo.c`): alocar/liberar a matriz de adjacência dinamicamente.
- [ ] **Algoritmo** (`floyd_warshall.c`): APSP + reconstrução de rota + update incremental.
- [ ] **Demonstração**: roteiro da apresentação com feedback visual no console.
