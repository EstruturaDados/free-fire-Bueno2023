#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// --- Definição da Struct ---
// Estrutura 'Item' para representar os objetos na mochila.
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// --- Funções do Sistema ---

// Funcao para inserir um novo item na mochila
void inserirItem(struct Item mochila[], int* num_itens) {
    if (*num_itens >= MAX_ITENS) {
        printf("\nMOCHILA CHEIA! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n--- CADASTRAR NOVO ITEM ---\n");
    printf("Nome do item: ");
    while (getchar() != '\n'); // Limpa o buffer de entrada
    fgets(mochila[*num_itens].nome, 30, stdin);
    mochila[*num_itens].nome[strcspn(mochila[*num_itens].nome, "\n")] = '\0';

    printf("Tipo (ex: arma, municao, cura): ");
    fgets(mochila[*num_itens].tipo, 20, stdin);
    mochila[*num_itens].tipo[strcspn(mochila[*num_itens].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &mochila[*num_itens].quantidade);
    
    (*num_itens)++;
    printf("Item cadastrado com sucesso!\n");
}

// Funcao para remover um item da mochila pelo nome
void removerItem(struct Item mochila[], int* num_itens) {
    char nome_busca[30];
    int i, j;
    
    if (*num_itens == 0) {
        printf("\nMOCHILA VAZIA! Nao ha itens para remover.\n");
        return;
    }
    
    printf("\n--- REMOVER ITEM ---\n");
    printf("Digite o nome do item a ser removido: ");
    while (getchar() != '\n');
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = '\0';
    
    // Busca o item no vetor
    for (i = 0; i < *num_itens; i++) {
        if (strcmp(mochila[i].nome, nome_busca) == 0) {
            // Se o item for encontrado, remove e move os demais
            for (j = i; j < (*num_itens) - 1; j++) {
                mochila[j] = mochila[j+1];
            }
            (*num_itens)--;
            printf("Item '%s' removido com sucesso!\n", nome_busca);
            return;
        }
    }
    
    printf("Item '%s' nao encontrado na mochila.\n", nome_busca);
}

// Funcao para buscar um item na mochila pelo nome
void buscarItem(struct Item mochila[], int num_itens) {
    char nome_busca[30];
    int i;
    
    if (num_itens == 0) {
        printf("\nMOCHILA VAZIA! Nao ha itens para buscar.\n");
        return;
    }
    
    printf("\n--- BUSCAR ITEM ---\n");
    printf("Digite o nome do item a ser buscado: ");
    while (getchar() != '\n');
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = '\0';
    
    // Percorre o vetor para encontrar o item
    for (i = 0; i < num_itens; i++) {
        if (strcmp(mochila[i].nome, nome_busca) == 0) {
            printf("\n--- ITEM ENCONTRADO ---\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }
    
    printf("Item '%s' nao encontrado na mochila.\n", nome_busca);
}

// Funcao para listar todos os itens na mochila
void listarItens(struct Item mochila[], int num_itens) {
    int i;
    
    printf("\n=== ITENS NA MOCHILA ===\n");
    if (num_itens == 0) {
        printf("A mochila esta vazia.\n");
    } else {
        for (i = 0; i < num_itens; i++) {
            printf("-----------------------\n");
            printf("Item %d:\n", i + 1);
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
        }
        printf("-----------------------\n");
    }
}

// --- Funcao Principal (Fluxo do Programa) ---
int main() {
    struct Item mochila[MAX_ITENS];
    int num_itens = 0;
    int opcao;

    do {
        // Menu principal para o usuario
        printf("\n--- MENU DA MOCHILA ---\n");
        printf("1. Cadastrar novo item\n");
        printf("2. Remover item\n");
        printf("3. Buscar item\n");
        printf("4. Listar todos os itens\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &num_itens);
                break;
            case 2:
                removerItem(mochila, &num_itens);
                break;
            case 3:
                buscarItem(mochila, num_itens);
                break;
            case 4:
                listarItens(mochila, num_itens);
                break;
            case 0:
                printf("\nSaindo do sistema. Ate mais!\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}