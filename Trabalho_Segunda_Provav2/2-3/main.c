#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inclua os cabeçalhos das suas árvores 2-3 e binária
#include "arv_portugues-23.c"
#include "arv_ingles-binaria.c"

// Funções auxiliares e de impressão (implemente conforme necessário)

// Função para exibir o menu de opções
void exibirMenu() {
    printf("\nEscolha uma opção:\n");
    printf("1 - Imprimir traduções por unidade\n");
    printf("2 - Imprimir uma unidade específica e suas traduções\n");
    printf("3 - Imprimir traduções em inglês de uma palavra em português\n");
    printf("4 - Remover uma palavra em inglês de uma unidade\n");
    printf("5 - Remover uma palavra em português de uma unidade\n");
    printf("6 - Sair\n");
    printf("Digite sua opção: ");
}

int main() {
    Tree23Node *arvore = NULL;
    TreeNode *arvoreIngles = NULL;

    int opcao = -1;
    int unidade;
    char palavraPortugues[50];
    char palavraIngles[50];

    // Criação de exemplos para unidade 1
    Info busInfo = criarInfo("onibus", 1);
    adicionarTraducao(&busInfo, "Bus", 1);
    adicionarTraducao(&busInfo, "Coach", 1); // Outra tradução
    inserirValorArvore(&arvore, busInfo);

    Info bugInfo = criarInfo("inseto", 1);
    adicionarTraducao(&bugInfo, "Bug", 1);
    inserirValorArvore(&arvore, bugInfo);

    Info systemInfo = criarInfo("sistema", 1);
    adicionarTraducao(&systemInfo, "System", 1);
    inserirValorArvore(&arvore, systemInfo);

    // Criação de exemplos para unidade 2
    Info bikeInfo = criarInfo("bicicleta", 2);
    adicionarTraducao(&bikeInfo, "Bicycle", 2);
    inserirValorArvore(&arvore, bikeInfo);

    // Loop principal do menu
    while (opcao != 6) {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // (i) Imprimir todas as palavras em português e traduções por unidade
                imprimirArvorePorUnidade(arvore);
                break;
            case 2:
                // (ii) Informar uma unidade específica e imprimir palavras e traduções
                printf("Digite a unidade: ");
                scanf("%d", &unidade);
                imprimirPorDadaUnidadeTraducoes(arvore, unidade);
                break;
            case 3:
                // (iii) Imprimir traduções em inglês de uma palavra em português
                printf("Digite a palavra em português: ");
                scanf("%s", palavraPortugues);
                imprimirTraducoesEmIngles(arvore, palavraPortugues);
                break;
            case 4:
                // (iv) Remover uma palavra em inglês de uma unidade específica
                printf("Digite a palavra em inglês: ");
                scanf("%s", palavraIngles);
                printf("Digite a unidade: ");
                scanf("%d", &unidade);
                break;
            case 5:
                // (v) Remover uma palavra em português de uma unidade específica
                printf("Digite a palavra em português: ");
                scanf("%s", palavraPortugues);
                printf("Digite a unidade: ");
                scanf("%d", &unidade);
                break;
            case 6:
                // Finalizar o programa
                limparArvore(&arvore);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}
