#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// --- Contadores Globais para Comparacao ---
int comparacoes_sequencial = 0;
int comparacoes_binaria = 0;

// --- Estruturas de Dados ---

// Estrutura para representar um Item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Estrutura para o No da Lista Encadeada
struct No {
    struct Item dados;
    struct No* proximo;
};

// --- Funcoes para a Mochila com Vetor ---

void inserirVetor(struct Item mochila[], int* num_itens) {
    if (*num_itens >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }
    printf("\nNome do item: ");
    while (getchar() != '\n');
    fgets(mochila[*num_itens].nome, 30, stdin);
    mochila[*num_itens].nome[strcspn(mochila[*num_itens].nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(mochila[*num_itens].tipo, 20, stdin);
    mochila[*num_itens].tipo[strcspn(mochila[*num_itens].tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &mochila[*num_itens].quantidade);
    (*num_itens)++;
    printf("Item adicionado com sucesso!\n");
}

void removerVetor(struct Item mochila[], int* num_itens, char* nome) {
    int i, j;
    for (i = 0; i < *num_itens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (j = i; j < (*num_itens) - 1; j++) {
                mochila[j] = mochila[j+1];
            }
            (*num_itens)--;
            printf("Item '%s' removido.\n", nome);
            return;
        }
    }
    printf("Item '%s' nao encontrado.\n", nome);
}

void listarVetor(struct Item mochila[], int num_itens) {
    if (num_itens == 0) {
        printf("\nMochila vazia.\n");
        return;
    }
    printf("\n=== ITENS NA MOCHILA (Vetor) ===\n");
    for (int i = 0; i < num_itens; i++) {
        printf("Nome: %s, Tipo: %s, Qtd: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void ordenarVetor(struct Item mochila[], int num_itens) {
    int i, j;
    struct Item temp;
    for (i = 0; i < num_itens - 1; i++) {
        for (j = 0; j < num_itens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j+1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = temp;
            }
        }
    }
    printf("\nItens ordenados com sucesso!\n");
}

void buscarSequencialVetor(struct Item mochila[], int num_itens, char* nome) {
    comparacoes_sequencial = 0;
    for (int i = 0; i < num_itens; i++) {
        comparacoes_sequencial++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem '%s' encontrado! Tipo: %s, Qtd: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            printf("Busca Sequencial: %d comparacoes.\n", comparacoes_sequencial);
            return;
        }
    }
    printf("\nItem '%s' nao encontrado.\n", nome);
    printf("Busca Sequencial: %d comparacoes.\n", comparacoes_sequencial);
}

void buscarBinariaVetor(struct Item mochila[], int num_itens, char* nome) {
    comparacoes_binaria = 0;
    int inicio = 0, fim = num_itens - 1, meio;
    while (inicio <= fim) {
        comparacoes_binaria++;
        meio = inicio + (fim - inicio) / 2;
        if (strcmp(mochila[meio].nome, nome) == 0) {
            printf("\nItem '%s' encontrado! Tipo: %s, Qtd: %d\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade);
            printf("Busca Binaria: %d comparacoes.\n", comparacoes_binaria);
            return;
        }
        if (strcmp(mochila[meio].nome, nome) < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("\nItem '%s' nao encontrado.\n", nome);
    printf("Busca Binaria: %d comparacoes.\n", comparacoes_binaria);
}

// --- Funcoes para a Mochila com Lista Encadeada ---

struct No* inserirLista(struct No* head) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    if (novoNo == NULL) {
        printf("\nErro de alocacao de memoria.\n");
        return head;
    }
    printf("\nNome do item: ");
    while (getchar() != '\n');
    fgets(novoNo->dados.nome, 30, stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novoNo->dados.tipo, 20, stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    
    novoNo->proximo = head;
    printf("Item adicionado com sucesso!\n");
    return novoNo;
}

struct No* removerLista(struct No* head, char* nome) {
    struct No* temp = head, *anterior = NULL;
    while (temp != NULL && strcmp(temp->dados.nome, nome) != 0) {
        anterior = temp;
        temp = temp->proximo;
    }
    if (temp == NULL) {
        printf("Item '%s' nao encontrado.\n", nome);
        return head;
    }
    if (anterior == NULL) {
        head = temp->proximo;
    } else {
        anterior->proximo = temp->proximo;
    }
    free(temp);
    printf("Item '%s' removido.\n", nome);
    return head;
}

void listarLista(struct No* head) {
    if (head == NULL) {
        printf("\nMochila vazia.\n");
        return;
    }
    printf("\n=== ITENS NA MOCHILA (Lista Encadeada) ===\n");
    struct No* temp = head;
    while (temp != NULL) {
        printf("Nome: %s, Tipo: %s, Qtd: %d\n", temp->dados.nome, temp->dados.tipo, temp->dados.quantidade);
        temp = temp->proximo;
    }
}

void buscarLista(struct No* head, char* nome) {
    comparacoes_sequencial = 0;
    struct No* temp = head;
    while (temp != NULL) {
        comparacoes_sequencial++;
        if (strcmp(temp->dados.nome, nome) == 0) {
            printf("\nItem '%s' encontrado! Tipo: %s, Qtd: %d\n", temp->dados.nome, temp->dados.tipo, temp->dados.quantidade);
            printf("Busca Sequencial: %d comparacoes.\n", comparacoes_sequencial);
            return;
        }
        temp = temp->proximo;
    }
    printf("\nItem '%s' nao encontrado.\n", nome);
    printf("Busca Sequencial: %d comparacoes.\n", comparacoes_sequencial);
}

// --- Funcao Principal e Menus ---

void menuVetor() {
    struct Item mochila_vetor[MAX_ITENS];
    int num_itens_vetor = 0;
    int opcao_vetor;
    char nome[30];

    do {
        printf("\n--- MENU VETOR ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar item (Sequencial)\n");
        printf("5. Ordenar itens\n");
        printf("6. Buscar item (Binaria)\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao_vetor);

        switch (opcao_vetor) {
            case 1: inserirVetor(mochila_vetor, &num_itens_vetor); break;
            case 2:
                printf("Nome do item a remover: ");
                while (getchar() != '\n');
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removerVetor(mochila_vetor, &num_itens_vetor, nome);
                break;
            case 3: listarVetor(mochila_vetor, num_itens_vetor); break;
            case 4:
                printf("Nome do item a buscar: ");
                while (getchar() != '\n');
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                buscarSequencialVetor(mochila_vetor, num_itens_vetor, nome);
                break;
            case 5: ordenarVetor(mochila_vetor, num_itens_vetor); break;
            case 6:
                printf("Nome do item a buscar (Lembre-se: os itens devem estar ordenados): ");
                while (getchar() != '\n');
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                buscarBinariaVetor(mochila_vetor, num_itens_vetor, nome);
                break;
        }
    } while (opcao_vetor != 0);
}

void menuLista() {
    struct No* mochila_lista = NULL;
    int opcao_lista;
    char nome[30];

    do {
        printf("\n--- MENU LISTA ENCADEDADA ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar item\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao_lista);

        switch (opcao_lista) {
            case 1: mochila_lista = inserirLista(mochila_lista); break;
            case 2:
                printf("Nome do item a remover: ");
                while (getchar() != '\n');
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                mochila_lista = removerLista(mochila_lista, nome);
                break;
            case 3: listarLista(mochila_lista); break;
            case 4:
                printf("Nome do item a buscar: ");
                while (getchar() != '\n');
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                buscarLista(mochila_lista, nome);
                break;
        }
    } while (opcao_lista != 0);

    // Liberar memoria da lista ao sair
    struct No* temp;
    while(mochila_lista != NULL) {
        temp = mochila_lista;
        mochila_lista = mochila_lista->proximo;
        free(temp);
    }
}

int main() {
    int opcao_principal;

    do {
        printf("\n=== ESCOLHA A ESTRUTURA DE DADOS ===\n");
        printf("1. Mochila com Vetor\n");
        printf("2. Mochila com Lista Encadeada\n");
        printf("0. Sair do programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao_principal);

        switch (opcao_principal) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("\nSaindo. Ate logo!\n"); break;
            default: printf("Opcao invalida. Tente novamente.\n"); break;
        }
    } while (opcao_principal != 0);

    return 0;
}