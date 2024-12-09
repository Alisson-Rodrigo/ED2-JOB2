#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portugues_arv.c"
#include "ingles_arv.c"

int inserirPalavraPortugues(Arv_pt **arvore, char *palavraPortugues, char *palavraIngles, int unidade) {
    Info promove;
    Arv_pt *pai = NULL;
    int inseriu;

    // Busca a palavra na árvore
    Arv_pt *noExistente = NULL;
    noExistente =  BuscarNoPorPalavra(arvore, palavraPortugues);

    if (noExistente != NULL) {
        AdicionarTraducaoNo(noExistente, palavraPortugues, palavraIngles, unidade);
        inseriu = 1;
    } else {
        Info novoInfo = CriarInfo(palavraPortugues, palavraIngles, unidade);
        InserirInfoArvore23(arvore, &novoInfo, &promove, &pai);
        inseriu = 0;
    }
    return inseriu;
}

void carregarArquivo(const char *nomeArquivo, Arv_pt **arvore)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];

    int unidadeAtual = 0;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        linha[strcspn(linha, "\n")] = 0;

        if (linha[0] == '%')
        {
            // Atualiza a unidade corretamente
            sscanf(linha, "%% Unidade %d", &unidadeAtual);
        }
        else
        {
            char palavraIngles[50], traducoesPortugues[200];
            sscanf(linha, "%[^:]: %[^;]", palavraIngles, traducoesPortugues);
            
            char *traducaoPortugues = strtok(traducoesPortugues, ",;");
            while(traducaoPortugues != NULL)
            {
                while (*traducaoPortugues == ' ') 
                    traducaoPortugues++;

                inserirPalavraPortugues(arvore, traducaoPortugues, palavraIngles, unidadeAtual);
                traducaoPortugues = strtok(NULL, ",;");    
            }
            
        }
    }

    fclose(arquivo);
    printf("Arquivo '%s' carregado com sucesso!\n", nomeArquivo);
}


int main()
{
    Arv_pt *arvore = NULL;
    int opcao, unidade;
    char palavraPortugues[50], palavraIngles[50];

    // Carregar o arquivo
    carregarArquivo("C:/Users/PurooLight/Documents/GitHub/ED2-JOB2/Trabalho_segunda_provaVERSAO-REFERENCIA/Tabalho2_Ed2-main/trabalhoEd2.txt", &arvore);

    while (1)
    {
        printf("\nMENU\n");
        printf("1. Exibir palavras associadas a uma unidade\n");
        printf("2. Exibir traducoes em ingles para uma palavra em portugues\n");
        printf("3. Remover palavra em ingles e atualizacoes associadas\n");
        printf("4. Remover palavra em portugues e traducoes associadas\n");
        printf("5. Sair do programa\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("Informe a unidade: ");
            while (1)
            {
                scanf("%d", &unidade);

                // Valida a unidade
                if (unidade < 1)
                {
                    printf("Unidade invalida. Tente novamente: ");
                }
                else
                {
                    break;
                }
            }
            // Imprime as palavras da unidade fornecida
            printf("Palavras da unidade %d:\n", unidade);
            imprimirPalavrasPorUnidade(arvore, unidade);
            break;

        case 2:
            printf("Informe a palavra em portugues: ");
            scanf(" %[^\n]", palavraPortugues); // Lê a palavra com espaços
            printf("Traducoes em ingles para '%s':\n", palavraPortugues);
            imprimirTraducoesIngles(arvore, palavraPortugues);
            break;

        case 3:
            printf("Informe a palavra em ingles: ");
            scanf(" %[^\n]", palavraIngles);
            printf("Informe a unidade: ");
            scanf("%d", &unidade);
            RemoverTraducoesInglesNaUnidade(&arvore, palavraIngles, unidade);
            break;
        case 4:
            printf("Informe a palavra em portugues: ");
            scanf(" %[^\n]", palavraPortugues);
            printf("Informe a unidade: ");
            scanf("%d", &unidade);
            RemoverPalavraArvore23(&arvore, palavraPortugues);
            break;
        case 5:
            printf("Saindo do programa...\n");
            exit(0);
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}