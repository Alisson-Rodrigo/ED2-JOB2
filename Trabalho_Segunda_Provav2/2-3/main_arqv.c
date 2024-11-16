#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv_portugues-23.c"
#include "arv_ingles-binaria.c"

void carregarArquivo(const char *nomeArquivo, Tree23Node **arvore) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];
    int unidadeAtual = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        // Remove a quebra de linha ao final
        linha[strcspn(linha, "\n")] = 0;
        // Verifica se é uma linha de unidade
        if (linha[0] == '%') {
            sscanf(linha, "%% Unidade %d", &unidadeAtual);
        } else {
            // Processar linha com palavra em português e traduções
            char palavraPortugues[50];
            char traducoes[200];

            if (sscanf(linha, "%[^:]: %[^\n]", traducoes, palavraPortugues) == 2) {
                // Cria um novo Info para a palavra em português
                Info novoInfo = criarInfo(palavraPortugues, unidadeAtual);

                // Processar traduções separadas por vírgula ou ponto e vírgula
                char *traducao = strtok(traducoes, ",;");
                while (traducao != NULL) {
                    // Remove espaços em branco no início
                    while (*traducao == ' ') traducao++;

                    // Adiciona tradução à árvore binária no Info
                    adicionarTraducao(&novoInfo, traducao, unidadeAtual);

                    traducao = strtok(NULL, ",;");
                }

                // Insere o Info (com a árvore binária preenchida) na árvore 2-3
                inserirValorArvore(arvore, novoInfo);
            }
        }
    }

    fclose(arquivo);
}



// Função para exibir os valores do arquivo
void exibirArvore23(Tree23Node *arvore) {
    if (arvore) {
        // Exibe subárvore à esquerda
        exibirArvore23(arvore->left);

        // Exibe o primeiro Info
        printf("Palavra em Português: %s (Unidade: %d)\n", arvore->info1.portugueseWord, arvore->info1.unit);
        printf("Traduções em Inglês:\n");
        printBinaryTree(arvore->info1.englishTreeRoot); // Imprime a árvore binária associada

        // Exibe o segundo Info, se existir
        if (arvore->nInfos == 2) {
            printf("Palavra em Português: %s (Unidade: %d)\n", arvore->info2.portugueseWord, arvore->info2.unit);
            printf("Traduções em Inglês:\n");
            printBinaryTree(arvore->info2.englishTreeRoot); // Imprime a árvore binária associada
        }

        // Exibe subárvores do meio e à direita
        exibirArvore23(arvore->middle);
        if (arvore->nInfos == 2) {
            exibirArvore23(arvore->right);
        }
    }
}


int main() {
    Tree23Node *arvore23 = NULL;

    // Carregar o arquivo de palavras
    carregarArquivo("C:/Users/PurooLight/Documents/GitHub/ED2-JOB2/Trabalho_Segunda_Provav2/2-3/arqv.txt", &arvore23);

    // Exibir os valores da árvore 2-3
    exibirArvore23(arvore23);

    return 0;
}





