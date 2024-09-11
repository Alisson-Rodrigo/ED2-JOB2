#include "curso.h"
#include <stdlib.h>
#include <stdio.h>


Arvore_curso *criar_curso()
{
    Arvore_curso *curso = (Arvore_curso *)malloc(sizeof(Arvore_curso));
    if (curso == NULL)
    {
        printf("Erro ao alocar memória para o curso\n");
        exit(1);
    }
    curso->raiz_disciplinas = NULL;
    curso->esq = NULL;
    curso->dir = NULL;
    return curso;
}

Arvore_curso *inserir_curso(Arvore_curso *curso, Arvore_curso *no)
{
    if (curso == NULL)
    {
        curso = no;
    }
    else
    {
        if (no->codigo < curso->codigo)
        {
            curso->esq = inserir_curso(curso->esq, no);
        }
        else
        {
            curso->dir = inserir_curso(curso->dir, no);
        }
    }
    return curso;
}

void imprimir_cursos(Arvore_curso *curso)
{
    if (curso != NULL)
    {
        imprimir_cursos(curso->esq);
        printf("Codigo: %d\n", curso->codigo);
        printf("Nome: %s\n", curso->nome);
        printf("Periodo: %d\n", curso->periodo);
        printf("\n");
        imprimir_cursos(curso->dir);
    }
}