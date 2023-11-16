#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto {
    int codigo;
    char descricao[50];
    int quantidade;
    float valor;
    struct Produto* proximo;
} Produto;

typedef struct {
    Produto* inicio;
} Estoque;

Estoque inicializarEstoque() {
    Estoque estoque;
    estoque.inicio = NULL;
    return estoque;
}

void adicionarProduto(Estoque* estoque) {
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));

    printf("Informe o codigo do produto: ");
    scanf("%d", &novoProduto->codigo);

    printf("Informe a descricao do produto: ");
    scanf("%s", novoProduto->descricao);

    printf("Informe a quantidade do produto: ");
    scanf("%d", &novoProduto->quantidade);

    printf("Informe o valor do produto: ");
    scanf("%f", &novoProduto->valor);

    novoProduto->proximo = estoque->inicio;
    estoque->inicio = novoProduto;
}

void imprimirRelatorio(Estoque estoque) {
    printf("\nRelatorio de Produtos:\n");
    printf("| %-10s | %-20s | %-10s | %-10s |\n", "Codigo", "Descricao", "Quantidade", "Valor");
    printf("|------------|----------------------|------------|------------|\n");

    Produto* atual = estoque.inicio;

    while (atual != NULL) {
        printf("| %-10d | %-20s | %-10d | %-10.2f |\n", 
               atual->codigo, 
               atual->descricao, 
               atual->quantidade, 
               atual->valor);
        atual = atual->proximo;
    }

    printf("\n");
}

void pesquisarProduto(Estoque estoque) {
    int codigo;
    printf("Informe o codigo do produto a ser pesquisado: ");
    scanf("%d", &codigo);

    Produto* atual = estoque.inicio;

    while (atual != NULL) {
        if (atual->codigo == codigo) {
            printf("\nProduto encontrado:\n");
            printf("Codigo: %d\n", atual->codigo);
            printf("Descricao: %s\n", atual->descricao);
            printf("Quantidade: %d\n", atual->quantidade);
            printf("Valor: %.2f\n\n");
            return;
        }
        atual = atual->proximo;
    }

    printf("\nProduto nao encontrado.\n\n");
}

void removerProduto(Estoque* estoque) {
    int codigo;
    printf("Informe o codigo do produto a ser removido: ");
    scanf("%d", &codigo);

    Produto* atual = estoque->inicio;
    Produto* anterior = NULL;

    while (atual != NULL) {
        if (atual->codigo == codigo) {
            if (anterior == NULL) {
                estoque->inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            free(atual);
            printf("\nProduto removido com sucesso.\n\n");
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("\nProduto nao encontrado.\n\n");
}

void liberarEstoque(Estoque* estoque) {
    Produto* atual = estoque->inicio;
    Produto* proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    estoque->inicio = NULL;
}

int main() {
    Estoque estoque = inicializarEstoque();
    int opcao;

    do {
        printf("Sistema de Controle de Estoque\n");
        printf("1. Adicionar Produto\n");
        printf("2. Imprimir Relatorio\n");
        printf("3. Pesquisar Produto\n");
        printf("4. Remover Produto\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarProduto(&estoque);
                break;
            case 2:
                imprimirRelatorio(estoque);
                break;
            case 3:
                pesquisarProduto(estoque);
                break;
            case 4:
                removerProduto(&estoque);
                break;
            case 0:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarEstoque(&estoque);

    return 0;
}