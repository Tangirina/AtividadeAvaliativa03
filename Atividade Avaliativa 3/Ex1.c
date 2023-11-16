#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int codigo;
    char descricao[50];
    int quantidade;
    float valor;
} Produto;

typedef struct {
    Produto *produtos;
    int tamanho;
} Estoque;

Estoque inicializarEstoque() {
    Estoque estoque;
    estoque.produtos = NULL;
    estoque.tamanho = 0;
    return estoque;
}

void adicionarProduto(Estoque *estoque) {
    estoque->tamanho++;
    estoque->produtos = realloc(estoque->produtos, estoque->tamanho * sizeof(Produto));

    printf("Informe o codigo do produto: ");
    scanf("%d", &estoque->produtos[estoque->tamanho - 1].codigo);

    printf("Informe a descricao do produto: ");
    scanf("%s", estoque->produtos[estoque->tamanho - 1].descricao);

    printf("Informe a quantidade do produto: ");
    scanf("%d", &estoque->produtos[estoque->tamanho - 1].quantidade);

    printf("Informe o valor do produto: ");
    scanf("%f", &estoque->produtos[estoque->tamanho - 1].valor);
}

void imprimirRelatorio(Estoque estoque) {
    printf("\nRelatorio de Produtos:\n");
    printf("| %-10s | %-20s | %-10s | %-10s |\n", "Codigo", "Descricao", "Quantidade", "Valor");
    printf("|------------|----------------------|------------|------------|\n");

    for (int i = 0; i < estoque.tamanho; i++) {
        printf("| %-10d | %-20s | %-10d | %-10.2f |\n", 
               estoque.produtos[i].codigo, 
               estoque.produtos[i].descricao, 
               estoque.produtos[i].quantidade, 
               estoque.produtos[i].valor);
    }

    printf("\n");
}

void pesquisarProduto(Estoque estoque) {
    int codigo;
    printf("Informe o codigo do produto a ser pesquisado: ");
    scanf("%d", &codigo);

    for (int i = 0; i < estoque.tamanho; i++) {
        if (estoque.produtos[i].codigo == codigo) {
            printf("\nProduto encontrado:\n");
            printf("Codigo: %d\n", estoque.produtos[i].codigo);
            printf("Descricao: %s\n", estoque.produtos[i].descricao);
            printf("Quantidade: %d\n", estoque.produtos[i].quantidade);
            printf("Valor: %.2f\n\n", estoque.produtos[i].valor);
            return;
        }
    }

    printf("\nProduto nao encontrado.\n\n");
}

void removerProduto(Estoque *estoque) {
    int codigo;
    printf("Informe o codigo do produto a ser removido: ");
    scanf("%d", &codigo);

    for (int i = 0; i < estoque->tamanho; i++) {
        if (estoque->produtos[i].codigo == codigo) {
            for (int j = i; j < estoque->tamanho - 1; j++) {
                estoque->produtos[j] = estoque->produtos[j + 1];
            }

            estoque->tamanho--;
            estoque->produtos = realloc(estoque->produtos, estoque->tamanho * sizeof(Produto));

            printf("\nProduto removido com sucesso.\n\n");
            return;
        }
    }

    printf("\nProduto nao encontrado.\n\n");
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
                printf("Programa Encerrado.\n");
                break;
            default:
                printf("Opçao inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    free(estoque.produtos);

    return 0;
}