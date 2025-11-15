# 🔫 Mini Game Free Fire — Inventário, Listas e Algoritmos em C

Este projeto foi desenvolvido como parte da disciplina de **Análise e Desenvolvimento de Sistemas**, aplicando conceitos de **Estruturas de Dados** através de um mini game inspirado no modo de sobrevivência de **Free Fire**.

O foco do trabalho é implementar a lógica da mochila (inventário) do jogador, utilizando **vetores**, **listas encadeadas**, **buscas** e **algoritmos de ordenação**, comparando eficiência entre as abordagens.

---

## 🎯 Objetivos

- Compreender a implementação de:
  - Listas lineares estáticas (vetores)
  - Listas dinâmicas (listas encadeadas)
  - Inserção, remoção, percorrimento e busca sequencial
- Comparar vetores e listas encadeadas nas operações de inserção, remoção e busca
- Implementar **busca binária** (iterativa e recursiva) no vetor ordenado
- Analisar o uso de **métodos de ordenação** (Bubble Sort) medindo o número de comparações

---

## 🧱 Estruturas Utilizadas

### Struct `Item`

```c
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;
