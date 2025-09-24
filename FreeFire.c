#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define CHIP_CENTRAL "Chip Central"

// --- Estruturas de Dados ---

// Estrutura para representar um componente da torre de fuga
struct Componente {
    char nome[30];
    char tipo[20];
    int prioridade;
};

// --- Funcoes de Utilitario ---

// Exibe todos os componentes em um formato claro
void mostrarComponentes(struct Componente componentes[], int num_itens) {
    if (num_itens == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }
    printf("\n=== COMPONENTES DA TORRE ===\n");
    for (int i = 0; i < num_itens; i++) {
        printf("Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
    printf("==============================\n");
}

// Funcao para trocar a posicao de dois componentes
void trocar(struct Componente* a, struct Componente* b) {
    struct Componente temp = *a;
    *a = *b;
    *b = temp;
}

// --- Algoritmos de Ordenacao ---

// Bubble Sort para ordenar por nome
void bubbleSortNome(struct Componente componentes[], int num_itens) {
    int i, j;
    long long comparacoes = 0;
    clock_t inicio, fim;
    double tempo_execucao;

    inicio = clock();
    for (i = 0; i < num_itens - 1; i++) {
        for (j = 0; j < num_itens - i - 1; j++) {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                trocar(&componentes[j], &componentes[j + 1]);
            }
        }
    }
    fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nOrdenacao por nome concluida (Bubble Sort).\n");
    printf("Comparacoes: %lld\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempo_execucao);
}

// Insertion Sort para ordenar por tipo
void insertionSortTipo(struct Componente componentes[], int num_itens) {
    int i, j;
    struct Componente chave;
    long long comparacoes = 0;
    clock_t inicio, fim;
    double tempo_execucao;

    inicio = clock();
    for (i = 1; i < num_itens; i++) {
        chave = componentes[i];
        j = i - 1;
        while (j >= 0 && strcmp(componentes[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            componentes[j + 1] = componentes[j];
            j = j - 1;
        }
        componentes[j + 1] = chave;
        if (j >= 0) {
            comparacoes++;
        }
    }
    fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nOrdenacao por tipo concluida (Insertion Sort).\n");
    printf("Comparacoes: %lld\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempo_execucao);
}

// Selection Sort para ordenar por prioridade
void selectionSortPrioridade(struct Componente componentes[], int num_itens) {
    int i, j, min_idx;
    long long comparacoes = 0;
    clock_t inicio, fim;
    double tempo_execucao;

    inicio = clock();
    for (i = 0; i < num_itens - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < num_itens; j++) {
            comparacoes++;
            if (componentes[j].prioridade < componentes[min_idx].prioridade) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            trocar(&componentes[min_idx], &componentes[i]);
        }
    }
    fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nOrdenacao por prioridade concluida (Selection Sort).\n");
    printf("Comparacoes: %lld\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempo_execucao);
}

// --- Funcao de Busca ---

// Busca Binaria por nome (requer que o vetor esteja ordenado por nome)
int buscaBinariaPorNome(struct Componente componentes[], int num_itens, char* nome_busca) {
    int inicio = 0, fim = num_itens - 1, meio, comparacoes = 0;

    printf("\nIniciando busca pelo componente '%s'...\n", nome_busca);
    while (inicio <= fim) {
        comparacoes++;
        meio = inicio + (fim - inicio) / 2;
        int cmp_resultado = strcmp(componentes[meio].nome, nome_busca);

        if (cmp_resultado == 0) {
            printf("\nComponente-chave encontrado! Prioridade: %d\n", componentes[meio].prioridade);
            printf("Busca Binaria: %d comparacoes.\n", comparacoes);
            return 1; // Encontrado
        }
        if (cmp_resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("\nComponente '%s' nao encontrado.\n", nome_busca);
    printf("Busca Binaria: %d comparacoes.\n", comparacoes);
    return 0; // Nao encontrado
}

// --- Funcao Principal e Menu Interativo ---

int main() {
    struct Componente componentes[MAX_COMPONENTES];
    int num_itens = 0;
    int opcao;

    do {
        printf("\n=== MODULO DE MONTAGEM DA TORRE ===\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Buscar componente-chave (Busca Binaria)\n");
        printf("6. Mostrar componentes\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nQuantos componentes deseja cadastrar (ate 20)? ");
                scanf("%d", &num_itens);
                while (getchar() != '\n');
                if (num_itens > MAX_COMPONENTES || num_itens <= 0) {
                    printf("Numero invalido. Tente novamente.\n");
                    num_itens = 0;
                    break;
                }
                for (int i = 0; i < num_itens; i++) {
                    printf("Componente %d:\n", i + 1);
                    printf("  Nome: ");
                    fgets(componentes[i].nome, 30, stdin);
                    componentes[i].nome[strcspn(componentes[i].nome, "\n")] = 0;
                    printf("  Tipo: ");
                    fgets(componentes[i].tipo, 20, stdin);
                    componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = 0;
                    printf("  Prioridade (1-10): ");
                    scanf("%d", &componentes[i].prioridade);
                    while (getchar() != '\n');
                }
                break;
            case 2:
                if (num_itens > 0) bubbleSortNome(componentes, num_itens);
                else printf("Cadastre componentes primeiro.\n");
                break;
            case 3:
                if (num_itens > 0) insertionSortTipo(componentes, num_itens);
                else printf("Cadastre componentes primeiro.\n");
                break;
            case 4:
                if (num_itens > 0) selectionSortPrioridade(componentes, num_itens);
                else printf("Cadastre componentes primeiro.\n");
                break;
            case 5:
                if (num_itens > 0) {
                    // Requer ordenacao por nome para funcionar
                    printf("\nPara a busca binaria, e necessario ordenar por nome primeiro.\n");
                    bubbleSortNome(componentes, num_itens);
                    buscaBinariaPorNome(componentes, num_itens, CHIP_CENTRAL);
                } else {
                    printf("Cadastre componentes primeiro.\n");
                }
                break;
            case 6:
                mostrarComponentes(componentes, num_itens);
                break;
            case 0:
                printf("\nSaindo do programa. Boa sorte na sua fuga!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}