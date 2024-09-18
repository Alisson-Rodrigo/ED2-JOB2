#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curso.c"       
#include "alunos.c"      
#include "disciplinas.c"
#include "matricula.c"

void exibir_menu()
{
    printf("Menu:\n");
    printf("1. Cadastrar novo curso\n");
    printf("2. Cadastrar novo aluno\n");
    printf("3. Buscar curso por codigo\n");
    printf("4. Cadastrar nova disciplina\n");
    printf("5. Cadastrar nova matricula\n");
    printf("6. Cadastrar notas\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    Arvore_curso *raiz_cursos = NULL;
    Aluno *raiz_alunos = NULL;
    int opcao = -1; // Inicialização correta
    int codigo, codigo_curso, matricula, carga_horaria, periodo;
    char nome[100];
    Aluno *aluno;
    Arvore_curso *curso;
    arvore_disciplinas *disciplina;
    

    while (opcao != 0)
    {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            // Cadastro de curso
            printf("Digite o codigo do curso: ");
            scanf("%d", &codigo);
            printf("Digite o nome do curso: ");
            scanf(" %[^\n]", nome);
            printf("Digite o periodo do curso: ");
            scanf("%d", &periodo);
            curso = criar_curso();
            curso->codigo = codigo;
            curso->periodo = periodo;
            strcpy(curso->nome, nome);

            raiz_cursos = inserir_curso(raiz_cursos, curso);
            printf("Curso cadastrado com sucesso!\n");
            break;

        case 2:
            // Cadastro de aluno
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula);
            printf("Digite o nome do aluno: ");
            scanf(" %[^\n]", nome);
            printf("Digite o codigo do curso do aluno: ");
            scanf("%d", &codigo_curso);

            // Verificar se o codigo do curso existe
            curso = buscar_curso(raiz_cursos, codigo_curso);
            if (curso == NULL)
            {
                printf("Codigo de curso nao encontrado. Cadastro do aluno nao realizado.\n");
                break;
            }

            aluno = criar_aluno();
            aluno->matricula = matricula;
            strcpy(aluno->nome, nome);
            aluno->codigo_curso = codigo_curso;

            raiz_alunos = inserir_aluno(raiz_alunos, aluno);
            printf("Aluno cadastrado com sucesso!\n");
            break;

        case 3:
            // Buscar curso
            printf("Digite o codigo do curso a buscar: ");
            scanf("%d", &codigo);
            curso = buscar_curso(raiz_cursos, codigo);
            if (curso != NULL)
            {
                printf("Curso encontrado:\n");
                printf("Codigo: %d\n", curso->codigo);
                printf("Nome: %s\n", curso->nome);
                printf("Periodo: %d\n", curso->periodo);
            }
            else
            {
                printf("Curso nao encontrado.\n");
            }
            break;

        case 4:
            // Cadastro de disciplina
            printf("Digite o codigo do curso da disciplina: ");
            scanf("%d", &codigo_curso);
            curso = buscar_curso(raiz_cursos, codigo_curso);
            if (curso == NULL)
            {
                printf("Codigo de curso nao encontrado. Cadastro da disciplina nao realizado.\n");
                break;
            }

            printf("Digite o codigo da disciplina: ");
            scanf("%d", &codigo);
            printf("Digite o nome da disciplina: ");
            scanf(" %[^\n]", nome);
            printf("Digite a carga horaria da disciplina: ");
            scanf("%d", &carga_horaria);

            // Validação da carga horária
            if (carga_horaria < 30 || carga_horaria > 90 || carga_horaria % 15 != 0)
            {
                printf("Carga horaria invalida. Cadastro da disciplina nao realizado.\n");
                break;
            }

            printf("Digite o periodo da disciplina: ");
            scanf("%d", &periodo);

            // Validação do período
            if (periodo < 1 || periodo > curso->periodo)
            {
                printf("Periodo invalido. Cadastro da disciplina nao realizado.\n");
                break;
            }

            // Criar e preencher a disciplina
            disciplina = criar_disciplina();
            disciplina->codigo = codigo;
            strcpy(disciplina->nome, nome);
            disciplina->carga_horaria = carga_horaria;
            disciplina->periodo = periodo;

            // Inserir a disciplina na árvore de disciplinas do curso
            curso->raiz_disciplinas = inserir_disciplina(curso->raiz_disciplinas, disciplina);
            printf("Disciplina cadastrada com sucesso.\n");
            break;
        case 5:
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula);
            aluno = buscar_aluno(raiz_alunos, matricula);
            if (aluno == NULL)
            {
                printf("Matricula nao encontrada.\n");
                break;
            }

            printf("Digite o codigo da disciplina: ");
            scanf("%d", &codigo);
            disciplina = buscar_disciplina(curso->raiz_disciplinas, codigo);
            if (disciplina == NULL)
            {
                printf("Disciplina nao encontrada.\n");
                break;
            }

            arvore_matricula *matricula = criar_matricula();
            matricula->codigo_disciplina = codigo;
            inserir_matriculas(aluno->raiz_matriculas, matricula);
            printf("Matricula cadastrada com sucesso.\n");
            break;
        case 6:
            /*
            Cadastrar Notas, permitir o cadastro de notas somente de disciplinas que estejam na árvore de
            matricula, e quando a nota for cadastrada a disciplina deve ser removida da árvore de matricula para
            árvore de notas. 
            */
            printf("Digite a matricula do aluno: ");
            scanf("%d", &raiz_alunos->matricula);
            aluno = buscar_aluno(raiz_alunos, raiz_alunos->matricula);
            if (aluno == NULL)
                {
                    printf("Matricula nao encontrada.\n");
                    break;
                }
            printf("Digite o codigo da disciplina: ");
            scanf("%d", &codigo);
            //Verificar arvore de matricula do aluno
            matricula = aluno->raiz_matriculas;
            disciplina = buscar_matricula(matricula, codigo);
            if (disciplina == NULL)
                {
                    printf("Disciplina nao encontrada.\n");
                    break;
                }
            //Cadastrar notas
            printf("Digite a nota final do aluno: ");
            scanf("%f", &aluno->raiz_notas->nota_final);
            printf("Digite o semestre cursado (ex: 2023.1): ");
            scanf("%s", aluno->raiz_notas->semestre_cursado);
            aluno->raiz_notas->codigo_disciplina = codigo;
            //Inserir notas na arvore de notas
            aluno->raiz_notas = inserir_nota(aluno->raiz_notas);
            printf("Nota cadastrada com sucesso.\n");
            //Remover disciplina da arvore de matricula
            aluno->raiz_matriculas = remover_matricula(aluno->raiz_matriculas, codigo);
            
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    // Liberação de memória (opcional, mas recomendado)
 
    // Assumindo que você tenha uma função para liberar disciplinas em cada curso

    return 0;
}
