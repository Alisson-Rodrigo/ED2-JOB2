#include <stdio.h>
#include <stdlib.h>
#include "entrevistas.h"

int main() {
    Arvore_entrevistas *raiz = NULL; // Inicializa a raiz como NULL

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Inserir nova entrevista\n");
        printf("2. Buscar entrevista por t�tulo\n");
        printf("3. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nInserir nova entrevista:\n");
                Arvore_entrevistas *novaEntrevista = criar_arvore_entrevistas();
                Ler_dados_de_insercao_entrevistas(novaEntrevista);
                raiz = inserir_entrevistas(raiz, novaEntrevista);
                printf("Entrevista inserida com sucesso!\n");
                break;
            case 2:
                printf("\nBuscar entrevista por t�tulo:\n");
                char titulo[50];
                printf("Digite o t�tulo da entrevista a ser buscada: ");
                scanf("%s", titulo);
                Arvore_entrevistas *entrevistaEncontrada = buscar_entrevistas(raiz, titulo);
                if (entrevistaEncontrada != NULL) {
                    printf("Entrevista encontrada:\n");
                    printf("T�tulo: %s\n", entrevistaEncontrada->titulos);
                    printf("Data: %s\n", entrevistaEncontrada->data);
                    printf("Dura��o: %d\n", entrevistaEncontrada->duracao);
                    printf("Nome do convidado: %s\n", entrevistaEncontrada->nome_convidado);
                    printf("Especialidade do convidado: %s\n", entrevistaEncontrada->especialidade_convidado);
                } else {
                    printf("Entrevista n�o encontrada.\n");
                }
                break;
            case 3:
                printf("\nEncerrando o programa.\n");
                break;
            default:
                printf("\nOp��o inv�lida. Por favor, escolha uma op��o v�lida.\n");
        }
    } while (opcao != 3);

    // Libere a mem�ria alocada para a �rvore antes de encerrar o programa
    // Coloque aqui a l�gica para liberar a mem�ria

    return 0;
}

