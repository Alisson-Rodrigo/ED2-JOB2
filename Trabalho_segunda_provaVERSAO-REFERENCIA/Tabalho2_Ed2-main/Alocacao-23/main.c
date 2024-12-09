#include "arv-23.c"
#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE (1024 * 1024) // Tamanho total da memória (1MB por bloco)

void cadastrar_primeiro_no(Memory **root) {
    int start = 0, end = MEMORY_SIZE, status;
    printf("Informe o status do primeiro nó (1 para Livre, 0 para Ocupado): ");
    scanf("%d", &status);

    printf("Informe o endereço inicial do primeiro nó: %d\n", start);
    printf("Informe o endereço final do primeiro nó: %d\n", end);

    Info *info1 = CreateInfo(start, end, status);
    *root = createNode(info1, NULL, NULL);
}

void cadastrar_nos_subsequentes(Memory **root) {
    int final, status;
    while (1) {
        printf("Informe o endereço final do próximo nó (0 para terminar): ");
        scanf("%d", &final);

        if (final == 0) break;

        status = (final % 2 == 0) ? FREE : OCCUPIED; // Alternando status
        Info *info = CreateInfo(final - 1024, final, status); // Bloco de 1MB por nó
        AddInfo(root, info, NULL);
    }
}

void alocar_memoria(Memory *root) {
    int requiredSpace;
    printf("Informe a quantidade de blocos a ser alocada: ");
    scanf("%d", &requiredSpace);

    Memory *spaceNode = FindSpace(root, requiredSpace);
    if (spaceNode != NULL) {
        printf("Encontrado espaço para %d blocos.\n", requiredSpace);
        // Atualiza o status de 'livre' para 'ocupado'
        spaceNode->info1->status = OCCUPIED;
    } else {
        printf("Espaço não encontrado.\n");
    }
}

void liberar_memoria(Memory *root) {
    int requiredSpace;
    printf("Informe a quantidade de blocos a ser liberada: ");
    scanf("%d", &requiredSpace);

    Memory *releaseNode = FindSpace(root, requiredSpace);
    if (releaseNode != NULL) {
        printf("Espaço liberado de %d blocos.\n", requiredSpace);
        releaseNode->info1->status = FREE;
    } else {
        printf("Espaço não encontrado.\n");
    }
}

void exibir_estado(Memory *root) {
    printf("\nEstado atual da memória:\n");
    DisplayInfos(root);
}

int main() {
    Memory *root = NULL;
    int opcao;

    while (1) {
        // Menu interativo
        printf("\nMenu de Gerenciamento de Memória:\n");
        printf("1. Cadastrar o primeiro nó\n");
        printf("2. Cadastrar nós subsequentes\n");
        printf("3. Alocar memória\n");
        printf("4. Liberar memória\n");
        printf("5. Exibir estado da memória\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_primeiro_no(&root);
                break;
            case 2:
                cadastrar_nos_subsequentes(&root);
                break;
            case 3:
                alocar_memoria(root);
                break;
            case 4:
                liberar_memoria(root);
                break;
            case 5:
                exibir_estado(root);
                break;
            case 6:
                printf("Saindo do programa...\n");
                return 0;
            default:
                printf("Opção inválida, tente novamente.\n");
        }
    }

    return 0;
}
