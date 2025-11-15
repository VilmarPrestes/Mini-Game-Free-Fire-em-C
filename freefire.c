#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// ---------------------------
// Structs principais
// ---------------------------

// Representa um item da mochila
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ---------------------------
// Globais para o vetor
// ---------------------------
Item mochilaVetor[MAX_ITENS];
int qtdItensVetor = 0; // quantidade atual de itens no vetor

// Cabeça da lista encadeada
No* mochilaLista = NULL;

// ---------------------------
// Funções utilitárias
// ---------------------------

// Lê string com segurança, removendo o '\n'
void lerString(char* destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

// Exibe um item formatado
void exibirItem(Item* item) {
    printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
           item->nome, item->tipo, item->quantidade);
}

// ---------------------------
// Funções para VETOR
// ---------------------------

// Inserir item no vetor
void inserirItemVetor() {
    if (qtdItensVetor >= MAX_ITENS) {
        printf("\n[ERRO] Mochila (vetor) cheia. Capacidade maxima = %d.\n", MAX_ITENS);
        return;
    }

    Item novo;
    printf("\n=== Inserir Item na Mochila (Vetor) ===\n");
    printf("Nome do item: ");
    lerString(novo.nome, TAM_NOME);

    printf("Tipo do item (ex: arma, municao, cura): ");
    lerString(novo.tipo, TAM_TIPO);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // consome '\n'

    mochilaVetor[qtdItensVetor] = novo;
    qtdItensVetor++;

    printf("\nItem inserido com sucesso na mochila (vetor)!\n");
}

// Remover item do vetor pelo nome
void removerItemVetor() {
    if (qtdItensVetor == 0) {
        printf("\n[ERRO] Mochila (vetor) vazia. Nao ha o que remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== Remover Item da Mochila (Vetor) ===\n");
    printf("Informe o nome do item a ser removido: ");
    lerString(nomeBusca, TAM_NOME);

    int i, pos = -1;
    for (i = 0; i < qtdItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("\n[INFO] Item '%s' nao encontrado na mochila (vetor).\n", nomeBusca);
        return;
    }

    // Desloca os itens para "tampar o buraco"
    for (i = pos; i < qtdItensVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }

    qtdItensVetor--;
    printf("\nItem removido com sucesso da mochila (vetor).\n");
}

// Listar itens do vetor
void listarItensVetor() {
    printf("\n=== Itens na Mochila (Vetor) ===\n");
    if (qtdItensVetor == 0) {
        printf("[INFO] Mochila vazia.\n");
    } else {
        for (int i = 0; i < qtdItensVetor; i++) {
            printf("Pos %d -> ", i);
            exibirItem(&mochilaVetor[i]);
        }
    }
    printf("================================\n");
}

// Busca sequencial no vetor, retorna índice ou -1
// e conta comparacoes em *comparacoes
int buscarSequencialVetor(char* nomeBusca, int* comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < qtdItensVetor; i++) {
        (*comparacoes)++;
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            return i;
        }
    }
    return -1;
}

// Bubble Sort por nome no vetor, contando comparacoes
void ordenarVetorPorNome(int* comparacoes) {
    *comparacoes = 0;
    if (qtdItensVetor <= 1) {
        printf("\n[INFO] Poucos itens para ordenar na mochila (vetor).\n");
        return;
    }

    for (int i = 0; i < qtdItensVetor - 1; i++) {
        for (int j = 0; j < qtdItensVetor - 1 - i; j++) {
            (*comparacoes)++;
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }

    printf("\n[OK] Mochila (vetor) ordenada por nome (Bubble Sort).\n");
}

// Busca binária iterativa no vetor ordenado, retorna índice ou -1
int buscarBinariaIterativa(char* nomeBusca, int* comparacoes) {
    *comparacoes = 0;
    int ini = 0;
    int fim = qtdItensVetor - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(nomeBusca, mochilaVetor[meio].nome);
        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            ini = meio + 1;
        }
    }

    return -1;
}

// Busca binária recursiva
int buscarBinariaRecursivaAux(char* nomeBusca, int ini, int fim, int* comparacoes) {
    if (ini > fim) {
        return -1;
    }

    int meio = (ini + fim) / 2;
    (*comparacoes)++;
    int cmp = strcmp(nomeBusca, mochilaVetor[meio].nome);
    if (cmp == 0) {
        return meio;
    } else if (cmp < 0) {
        return buscarBinariaRecursivaAux(nomeBusca, ini, meio - 1, comparacoes);
    } else {
        return buscarBinariaRecursivaAux(nomeBusca, meio + 1, fim, comparacoes);
    }
}

int buscarBinariaRecursiva(char* nomeBusca, int* comparacoes) {
    *comparacoes = 0;
    return buscarBinariaRecursivaAux(nomeBusca, 0, qtdItensVetor - 1, comparacoes);
}

// ---------------------------
// Funções para LISTA ENCADEADA
// ---------------------------

// Inserir item na lista encadeada (no início)
void inserirItemLista() {
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("[ERRO] Falha ao alocar memoria para novo no.\n");
        return;
    }

    printf("\n=== Inserir Item na Mochila (Lista Encadeada) ===\n");
    printf("Nome do item: ");
    lerString(novoNo->dados.nome, TAM_NOME);

    printf("Tipo do item (ex: arma, municao, cura): ");
    lerString(novoNo->dados.tipo, TAM_TIPO);

    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    getchar(); // consome '\n'

    novoNo->proximo = mochilaLista;
    mochilaLista = novoNo;

    printf("\nItem inserido com sucesso na mochila (lista encadeada)!\n");
}

// Remover item da lista encadeada pelo nome
void removerItemLista() {
    if (mochilaLista == NULL) {
        printf("\n[ERRO] Mochila (lista) vazia. Nao ha o que remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== Remover Item da Mochila (Lista Encadeada) ===\n");
    printf("Informe o nome do item a ser removido: ");
    lerString(nomeBusca, TAM_NOME);

    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nomeBusca) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\n[INFO] Item '%s' nao encontrado na mochila (lista).\n", nomeBusca);
        return;
    }

    if (anterior == NULL) {
        // Removendo o primeiro nó
        mochilaLista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("\nItem removido com sucesso da mochila (lista encadeada).\n");
}

// Listar itens da lista encadeada
void listarItensLista() {
    printf("\n=== Itens na Mochila (Lista Encadeada) ===\n");

    if (mochilaLista == NULL) {
        printf("[INFO] Mochila (lista) vazia.\n");
    } else {
        No* aux = mochilaLista;
        int pos = 0;
        while (aux != NULL) {
            printf("No %d -> ", pos);
            exibirItem(&aux->dados);
            aux = aux->proximo;
            pos++;
        }
    }

    printf("==========================================\n");
}

// Busca sequencial na lista, retorna ponteiro para No ou NULL
// e conta comparacoes em *comparacoes
No* buscarSequencialLista(char* nomeBusca, int* comparacoes) {
    *comparacoes = 0;
    No* aux = mochilaLista;

    while (aux != NULL) {
        (*comparacoes)++;
        if (strcmp(aux->dados.nome, nomeBusca) == 0) {
            return aux;
        }
        aux = aux->proximo;
    }

    return NULL;
}

// Liberar toda a lista encadeada
void liberarLista() {
    No* aux = mochilaLista;
    while (aux != NULL) {
        No* temp = aux;
        aux = aux->proximo;
        free(temp);
    }
    mochilaLista = NULL;
}

// ---------------------------
// Menu principal
// ---------------------------
void exibirMenu() {
    printf("\n=========================================\n");
    printf("       MINI GAME FREE FIRE - MOCHILA     \n");
    printf("=========================================\n");
    printf("1  - Inserir item na mochila (vetor)\n");
    printf("2  - Remover item da mochila (vetor)\n");
    printf("3  - Listar itens da mochila (vetor)\n");
    printf("4  - Buscar item (sequencial) no vetor\n");
    printf("5  - Ordenar vetor por nome (Bubble Sort)\n");
    printf("6  - Buscar item (binaria iterativa) no vetor\n");
    printf("7  - Buscar item (binaria recursiva) no vetor\n");
    printf("8  - Inserir item na mochila (lista encadeada)\n");
    printf("9  - Remover item da mochila (lista encadeada)\n");
    printf("10 - Listar itens da mochila (lista encadeada)\n");
    printf("11 - Buscar item (sequencial) na lista encadeada\n");
    printf("0  - Sair\n");
    printf("=========================================\n");
    printf("Escolha uma opcao: ");
}

// ---------------------------
// Função principal
// ---------------------------
int main() {
    int opcao;
    int comparacoes;
    char nomeBusca[TAM_NOME];

    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // consome '\n'

        switch (opcao) {
            case 1:
                inserirItemVetor();
                listarItensVetor();
                break;
            case 2:
                removerItemVetor();
                listarItensVetor();
                break;
            case 3:
                listarItensVetor();
                break;
            case 4:
                printf("\n=== Busca Sequencial no Vetor ===\n");
                printf("Informe o nome do item: ");
                lerString(nomeBusca, TAM_NOME);
                {
                    int pos = buscarSequencialVetor(nomeBusca, &comparacoes);
                    if (pos == -1) {
                        printf("Item nao encontrado no vetor.\n");
                    } else {
                        printf("Item encontrado na posicao %d do vetor.\n", pos);
                        exibirItem(&mochilaVetor[pos]);
                    }
                    printf("Comparacoes realizadas (sequencial vetor): %d\n",
                           comparacoes);
                }
                break;
            case 5:
                ordenarVetorPorNome(&comparacoes);
                printf("Comparacoes realizadas na ordenacao (Bubble Sort): %d\n",
                       comparacoes);
                listarItensVetor();
                break;
            case 6:
                printf("\n=== Busca Binaria Iterativa no Vetor ===\n");
                printf("ATENCAO: o vetor deve estar ORDENADO por nome.\n");
                printf("Informe o nome do item: ");
                lerString(nomeBusca, TAM_NOME);
                {
                    int pos = buscarBinariaIterativa(nomeBusca, &comparacoes);
                    if (pos == -1) {
                        printf("Item nao encontrado no vetor.\n");
                    } else {
                        printf("Item encontrado na posicao %d do vetor.\n", pos);
                        exibirItem(&mochilaVetor[pos]);
                    }
                    printf("Comparacoes realizadas (binaria iterativa): %d\n",
                           comparacoes);
                }
                break;
            case 7:
                printf("\n=== Busca Binaria Recursiva no Vetor ===\n");
                printf("ATENCAO: o vetor deve estar ORDENADO por nome.\n");
                printf("Informe o nome do item: ");
                lerString(nomeBusca, TAM_NOME);
                {
                    int pos = buscarBinariaRecursiva(nomeBusca, &comparacoes);
                    if (pos == -1) {
                        printf("Item nao encontrado no vetor.\n");
                    } else {
                        printf("Item encontrado na posicao %d do vetor.\n", pos);
                        exibirItem(&mochilaVetor[pos]);
                    }
                    printf("Comparacoes realizadas (binaria recursiva): %d\n",
                           comparacoes);
                }
                break;
            case 8:
                inserirItemLista();
                listarItensLista();
                break;
            case 9:
                removerItemLista();
                listarItensLista();
                break;
            case 10:
                listarItensLista();
                break;
            case 11:
                printf("\n=== Busca Sequencial na Lista Encadeada ===\n");
                printf("Informe o nome do item: ");
                lerString(nomeBusca, TAM_NOME);
                {
                    No* resultado = buscarSequencialLista(nomeBusca, &comparacoes);
                    if (resultado == NULL) {
                        printf("Item nao encontrado na lista encadeada.\n");
                    } else {
                        printf("Item encontrado na lista encadeada:\n");
                        exibirItem(&resultado->dados);
                    }
                    printf("Comparacoes realizadas (sequencial lista): %d\n",
                           comparacoes);
                }
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    // Libera memoria da lista antes de sair
    liberarLista();

    printf("\nMemoria liberada. Fim do jogo.\n");
    return 0;
}
