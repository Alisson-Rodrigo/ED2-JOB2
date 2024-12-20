#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "notas.h"



short maior_no_nota(short a, short b)
{
    return (a > b) ? a : b;
}

short altura_do_no_nota(arvore_notas *no)
{
    if (no == NULL)
    {
        return -1;
    }
    return no->altura;
}

short fator_balanceamento_nota(arvore_notas *no)
{
    if (no == NULL)
    {
        return 0;
    }
    return altura_do_no_nota(no->esq) - altura_do_no_nota(no->dir);
}

 arvore_notas *rotar_esquerda_nota(arvore_notas *no)
{
    arvore_notas *aux, *aux1;

    aux = no->dir;
    aux1 = aux->esq;

    aux->esq = no;
    no->dir = aux1;

    no->altura = maior_no_nota(altura_do_no_nota(no->esq), altura_do_no_nota(no->dir)) + 1;
    aux->altura = maior_no_nota(altura_do_no_nota(aux->esq), altura_do_no_nota(aux->dir)) + 1;

    return aux;
}

arvore_notas *rotar_direita_nota(arvore_notas *no)
{
    arvore_notas *aux, *aux1;

    aux = no->esq;
    aux1 = aux->dir;

    aux->dir = no;
    no->esq = aux1;

    no->altura = maior_no_nota(altura_do_no_nota(no->esq), altura_do_no_nota(no->dir)) + 1;
    aux->altura = maior_no_nota(altura_do_no_nota(aux->esq), altura_do_no_nota(aux->dir)) + 1;

    return aux;
}

arvore_notas *rotar_direita_esquerda_nota(arvore_notas *no)
{
    no->dir = rotar_direita_nota(no->dir);
    return rotar_esquerda_nota(no);
}

 arvore_notas *rotar_esquerda_direita_nota(arvore_notas *no)
{
    no->esq = rotar_esquerda_nota(no->esq);
    return rotar_direita_nota(no);
}

arvore_notas *balencar_arvore_nota(arvore_notas *raiz)
{
    short fb = fator_balanceamento_nota(raiz);

    if (fb < -1 && fator_balanceamento_nota(raiz->dir) <= 0)
    {
        raiz = rotar_esquerda_nota(raiz);
    }
    else if (fb > 1 && fator_balanceamento_nota(raiz->esq) >= 0)
    {
        raiz = rotar_direita_nota(raiz);
    }
    else if (fb > 1 && fator_balanceamento_nota(raiz->esq) < 0)
    {
        raiz = rotar_esquerda_direita_nota(raiz);
    }
    else if (fb < -1 && fator_balanceamento_nota(raiz->dir) > 0)
    {
        raiz = rotar_direita_esquerda_nota(raiz);
    }
    return raiz;
}

arvore_notas *criar_nota()
{
    arvore_notas *no = (arvore_notas *)malloc(sizeof(arvore_notas));
    no->esq = NULL;
    no->dir = NULL;
    no->altura = 0;
    return no;
}



arvore_notas *inserir_nota(arvore_notas *raiz, arvore_notas *no) {
    if (raiz == NULL) {
        raiz = no;
    } else {
        if (no->codigo_disciplina < raiz->codigo_disciplina) {
            raiz->esq = inserir_nota(raiz->esq, no);
        } else {
            raiz->dir = inserir_nota(raiz->dir, no);
        }
    }
    
   
    raiz = balencar_arvore_nota(raiz);
    raiz->altura = maior_no_nota(altura_do_no_nota(raiz->esq), altura_do_no_nota(raiz->dir)) + 1;

  
    
    return raiz;
}




void imprimir_notas(arvore_notas *raiz)
{
    if (raiz != NULL)
    {
        printf("Codigo da disciplina: %d\n", raiz->codigo_disciplina);
        printf("Semestre cursado: %s\n", raiz->semestre_cursado);
        printf("Nota Final: %.2f\n", raiz->nota_final);
        imprimir_notas(raiz->esq);
        imprimir_notas(raiz->dir);
    }
}


arvore_notas *buscar_notas(arvore_notas *raiz, int codigo_disciplina)
{
    arvore_notas *aux = NULL;
    if (raiz != NULL)
    {
        {
            if (codigo_disciplina == raiz->codigo_disciplina)
            {
                aux = raiz;
            }
            else
            {
                if (codigo_disciplina < raiz->codigo_disciplina)
                {
                    aux = buscar_notas(raiz->esq, codigo_disciplina);
                }
                else
                {
                    aux = buscar_notas(raiz->dir, codigo_disciplina);
                }
            }
        }
    }
    return aux;
}


arvore_notas *remover_nota(arvore_notas *raiz, int codigo_disciplina)
{
    // Procede apenas se a raiz não for NULL
    if (raiz != NULL) 
    {
        // Busca o nó a ser removido
        if (codigo_disciplina < raiz->codigo_disciplina)
        {
            raiz->esq = remover_nota(raiz->esq, codigo_disciplina);
        }
        else if (codigo_disciplina > raiz->codigo_disciplina)
        {
            raiz->dir = remover_nota(raiz->dir, codigo_disciplina);
        }
        else // Encontrou o nó a ser removido
        {
            // Caso 1: Nó com apenas um filho ou nenhum
            if (raiz->esq == NULL)
            {
                arvore_notas *temp = raiz->dir;
                free(raiz);
                raiz = temp;  // Atualiza raiz para o filho que não é NULL
            }
            else if (raiz->dir == NULL)
            {
                arvore_notas *temp = raiz->esq;
                free(raiz);
                raiz = temp;  // Atualiza raiz para o filho que não é NULL
            }
            else
            {
                // Caso 2: Nó com dois filhos
                // Encontrar o menor nó na subárvore da direita
                arvore_notas *temp = raiz->dir;
                while (temp->esq != NULL)
                {
                    temp = temp->esq;
                }

                // Substitui o código do nó a ser removido pelo menor nó da subárvore da direita
                raiz->codigo_disciplina = temp->codigo_disciplina;

                // Remove o menor nó da subárvore da direita
                raiz->dir = remover_nota(raiz->dir, temp->codigo_disciplina);
            }
        }

        // Atualiza a altura do nó atual, se raiz ainda é válida
        if (raiz != NULL) 
        {
            raiz->altura = maior_no_nota(altura_do_no_nota(raiz->esq), altura_do_no_nota(raiz->dir)) + 1;

            // Balanceia a árvore
            raiz = balencar_arvore_nota(raiz);
        }
    }

    return raiz; // Retorna a raiz balanceada apenas no final
}


void imprimir_notas_periodo(arvore_notas* raiz_notas, int periodo){
    if(raiz_notas != NULL){
        imprimir_notas_periodo(raiz_notas->esq, periodo);
        if(raiz_notas->semestre_cursado[5] == periodo + '0'){
            printf("Codigo da disciplina: %d\n", raiz_notas->codigo_disciplina);
            printf("Semestre cursado: %s\n", raiz_notas->semestre_cursado);
            printf("Nota Final: %f\n", raiz_notas->nota_final);
        }
        imprimir_notas_periodo(raiz_notas->dir, periodo);
    }
}

arvore_notas *buscar_nota_periodo(arvore_notas *raiz, int periodo)
{
    arvore_notas *aux = NULL;
    if (raiz != NULL)
    {
        aux = buscar_nota_periodo(raiz->esq, periodo);
        if (raiz->semestre_cursado[5] == periodo + '0')
        {
            aux = raiz;
        }
        if (aux == NULL)
        {
            aux = buscar_nota_periodo(raiz->dir, periodo);
        }
    }
    return aux;
}