#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Novato, Aventureiro e Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define MAX_ITENS 10

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade;
} Item;

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).
typedef enum {
    ORDENAR_POR_NOME = 1,
    ORDENAR_POR_TIPO,
    ORDENAR_POR_PRIORIDADE
} CriterioOrdenacao;

// Funções auxiliares
void limparTela() {
    for (int i = 0; i < 30; i++) printf("\n");
}

void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("📦 Mochila vazia.\n");
        return;
    }
    printf("\n======= ITENS NA MOCHILA =======\n");
    printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("---------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%-20s %-15s %-10d %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
}

void inserirItem(Item mochila[], int *total, bool *ordenadaPorNome) {
    if (*total >= MAX_ITENS) {
        printf("⚠️ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("Digite o nome do item: ");
    fgets(mochila[*total].nome, sizeof(mochila[*total].nome), stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = 0;

    printf("Digite o tipo do item: ");
    fgets(mochila[*total].tipo, sizeof(mochila[*total].tipo), stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = 0;

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    getchar();

    printf("Digite a prioridade (1-5): ");
    scanf("%d", &mochila[*total].prioridade);
    getchar();

    (*total)++;
    *ordenadaPorNome = false;
    printf("✅ Item adicionado com sucesso!\n");
}

void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("⚠️ Mochila vazia!\n");
        return;
    }

    char nome[50];
    printf("Digite o nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            encontrado = 1;
            printf("🗑️ Item removido com sucesso!\n");
            break;
        }
    }
    if (!encontrado)
        printf("❌ Item não encontrado.\n");
}

void buscarItemPorNome(Item mochila[], int total) {
    if (total == 0) {
        printf("📦 Mochila vazia.\n");
        return;
    }

    char nomeBusca[50];
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n🔍 Item encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\nPrioridade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado)
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
}

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação.
int insertionSort(Item mochila[], int total, CriterioOrdenacao criterio) {
    int comparacoes = 0;
    for (int i = 1; i < total; i++) {
        Item atual = mochila[i];
        int j = i - 1;
        while (j >= 0) {
            comparacoes++;
            bool cond = false;
            if (criterio == ORDENAR_POR_NOME)
                cond = strcmp(mochila[j].nome, atual.nome) > 0;
            else if (criterio == ORDENAR_POR_TIPO)
                cond = strcmp(mochila[j].tipo, atual.tipo) > 0;
            else if (criterio == ORDENAR_POR_PRIORIDADE)
                cond = mochila[j].prioridade < atual.prioridade;

            if (cond) {
                mochila[j + 1] = mochila[j];
                j--;
            } else break;
        }
        mochila[j + 1] = atual;
    }
    return comparacoes;
}

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
void buscaBinariaPorNome(Item mochila[], int total, bool ordenadaPorNome) {
    if (!ordenadaPorNome) {
        printf("⚠️ A lista precisa estar ordenada por nome para realizar a busca binária.\n");
        return;
    }

    char nomeBusca[50];
    printf("Digite o nome do item a buscar (binária): ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int inicio = 0, fim = total - 1, encontrado = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);

        if (cmp == 0) {
            printf("\n🎯 Item encontrado via busca binária!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\nPrioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade, mochila[meio].prioridade);
            encontrado = 1;
            break;
        } else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    if (!encontrado)
        printf("❌ Item '%s' não encontrado.\n", nomeBusca);
}

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
void menuDeOrdenacao(Item mochila[], int total, bool *ordenadaPorNome) {
    if (total == 0) {
        printf("📦 Mochila vazia. Nenhum item para ordenar.\n");
        return;
    }

    int opcao;
    printf("\n===== MENU DE ORDENACAO =====\n");
    printf("1 - Ordenar por Nome\n");
    printf("2 - Ordenar por Tipo\n");
    printf("3 - Ordenar por Prioridade\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    getchar();

    CriterioOrdenacao criterio = (CriterioOrdenacao)opcao;
    int comparacoes = insertionSort(mochila, total, criterio);

    *ordenadaPorNome = (criterio == ORDENAR_POR_NOME);

    printf("✅ Itens ordenados com sucesso! (%d comparações)\n", comparacoes);
    listarItens(mochila, total);
}

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    bool ordenadaPorNome = false;
    int opcao;

    do {
        printf("\n===== MOCHILA DO SOBREVIVENTE =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item por nome\n");
        printf("5 - Ordenar mochila\n");
        printf("6 - Busca binária por nome\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: inserirItem(mochila, &total, &ordenadaPorNome); break;
            case 2: removerItem(mochila, &total); break;
            case 3: listarItens(mochila, total); break;
            case 4: buscarItemPorNome(mochila, total); break;
            case 5: menuDeOrdenacao(mochila, total, &ordenadaPorNome); break;
            case 6: buscaBinariaPorNome(mochila, total, ordenadaPorNome); break;
            case 0: printf("👋 Saindo da ilha...\n"); break;
            default: printf("⚠️ Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
