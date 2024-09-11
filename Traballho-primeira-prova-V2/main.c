#include <stdio.h>
#include <stdlib.h>
#include "curso.c"

int main()
{
    Arvore_curso *raiz_cursos = NULL;
    int opcao, codigo;
    Arvore_curso *curso;

    do
    {
        printf("Menu:\n");
        printf("1. Cadastrar curso\n");
        printf("2. Imprimir cursos\n");
        printf("3. Buscar curso\n");
        printf("4. Remover curso\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
                curso = criar_curso();
                ler_dados_curso(curso);
                raiz_cursos = inserir_curso(raiz_cursos, curso);
                break;

            case 2:
                imprimir_cursos(raiz_cursos);
                break;

            case 3:
                printf("Digite o código do curso a ser buscado: ");
                scanf("%d", &codigo);
                curso = buscar_curso(raiz_cursos, codigo);
                if (curso)
                {
                    printf("Curso encontrado:\n");
                    printf("Codigo: %d\n", curso->codigo);
                    printf("Nome: %s\n", curso->nome);
                    printf("Periodo: %d\n", curso->periodo);
                }
                else
                {
                    printf("Curso não encontrado.\n");
                }
                break;

            case 4:
                printf("Digite o código do curso a ser removido: ");
                scanf("%d", &codigo);
                raiz_cursos = remover_curso(raiz_cursos, codigo);
                break;

            case 5:
                // Liberar memória e sair
                // Função para liberar cursos deve ser implementada
                break;

            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}
