#include "portugues.h"
#include "ingles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 1
#define BLACK 0
Info criaInfo(char *palavra, char *palavraIngles, int unidade)
{
    Info info;

    info.palavraPortugues = malloc(strlen(palavra) + 1);
    strcpy(info.palavraPortugues, palavra);

    info.palavraIngles = NULL;
    info.palavraIngles = insertpalavraIngles(info.palavraIngles, palavraIngles, unidade);
    return info;
}

PortuguesRB *criaNo(Info *informacao)
{
    PortuguesRB *novo = (PortuguesRB *)malloc(sizeof(PortuguesRB));
    novo->info = *informacao;
    novo->cor = 1;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}
int cor(PortuguesRB *raiz)
{
    int cor;

    if (raiz == NULL)
        cor = BLACK;
    else
        cor = raiz->cor;

    return cor;
}

void troca_cor(PortuguesRB **raiz)
{
    (*raiz)->cor = !(*raiz)->cor;
    if ((*raiz)->esq)
        (*raiz)->esq->cor = !(*raiz)->esq->cor;
    if ((*raiz)->dir)
        (*raiz)->dir->cor = !(*raiz)->dir->cor;
}

void rotacao_direita(PortuguesRB **raiz)
{
    PortuguesRB *aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = RED;
    (*raiz) = aux;
}

void rotacao_esquerda(PortuguesRB **raiz)
{
    PortuguesRB *aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = RED;
    (*raiz) = aux;
}

void balancear(PortuguesRB **raiz)
{
    if (*raiz)
    {
        if (cor((*raiz)->dir) == RED && cor((*raiz)->esq) == BLACK)
            rotacao_esquerda(raiz);
        if (cor((*raiz)->esq) == RED && cor((*raiz)->esq->esq) == RED)
            rotacao_direita(raiz);
        if (cor((*raiz)->esq) == RED && cor((*raiz)->dir) == RED)
            troca_cor(raiz);
    }
}

int inserirRB(PortuguesRB **raiz, Info *informacao)
{

    int inseriu = 1;
    if (*raiz == NULL)
    {
        *raiz = criaNo(informacao);
    }
    else
    {
        if (strcmp(informacao->palavraPortugues, (*raiz)->info.palavraPortugues) < 0)
        {
            inseriu = inserirRB(&(*raiz)->esq, informacao);
        }
        else
        {
            inseriu = inserirRB(&(*raiz)->dir, informacao);
        }
        balancear(&(*raiz));
    }

    return inseriu;
}

int inserirArvRB(PortuguesRB **raiz, Info *informacao)
{
    int inseriu = inserirRB(raiz, informacao);
    if (inseriu)
    {
        (*raiz)->cor = BLACK;
    }
    return inseriu;
}

void moveEsqVermelha(PortuguesRB **raiz)
{
    troca_cor(raiz);

    if ((*raiz)->dir && cor((*raiz)->dir->esq) == RED)
    {
        rotacao_direita(&(*raiz)->dir);
        rotacao_esquerda((raiz));
        troca_cor(raiz);
    }
}

void moveDirVermelha(PortuguesRB **raiz)
{
    troca_cor(raiz);

    if ((*raiz)->esq && cor((*raiz)->esq->esq) == RED)
    {
        rotacao_direita(raiz);
        troca_cor(raiz);
    }
}

void removeMenor(PortuguesRB **raiz)
{
    if (!((*raiz)->esq))
    {
        free(*raiz);
        *raiz = NULL;
    }
    else
    {
        if (cor((*raiz)->esq) == BLACK && cor((*raiz)->esq->esq) == BLACK)
            moveEsqVermelha(raiz);

        removeMenor(&(*raiz)->esq);
        balancear(raiz);
    }
}

PortuguesRB *procuraMenor(PortuguesRB *raiz)
{
    PortuguesRB *menor;
    menor = raiz;

    if (raiz)
        if (raiz->esq)
            menor = procuraMenor(raiz->esq);

    return menor;
}

int removerNoArvVP(PortuguesRB **raiz, char *valor)
{
    int existe = 0;
    printf("\nEntrou \n");

    if (*raiz)
    {
        if (strcmp(valor, (*raiz)->info.palavraPortugues) < 0)
        {
            if ((*raiz)->esq && cor((*raiz)->esq) == BLACK && cor((*raiz)->esq->esq) == BLACK)
                moveEsqVermelha(raiz);

            existe = removerNoArvVP(&(*raiz)->esq, valor);
        }
        else
        {
            if (cor((*raiz)->esq) == RED)
                rotacao_direita(raiz);

            if (strcmp(valor, (*raiz)->info.palavraPortugues) == 0 && (*raiz)->dir == NULL)
            {
                free(*raiz);
                *raiz = NULL;

                existe = 1;
            }else{
                if ((*raiz)->dir && cor((*raiz)->dir) == BLACK && cor((*raiz)->dir->esq) == BLACK)
                moveDirVermelha(raiz);

                if (strcmp(valor, (*raiz)->info.palavraPortugues) == 0)
                {
                    PortuguesRB *aux;
                    aux = procuraMenor((*raiz)->dir);
                    (*raiz)->info = aux->info;
                    removeMenor(&(*raiz)->dir);

                    existe = 1;
                }
                else
                {
                    existe = removerNoArvVP(&(*raiz)->dir, valor);
                }
            }
        }
    }
    balancear(raiz);
    return existe;
}

void adicionarTraducaoEmIngles(PortuguesRB *raiz, char *palavraIng, int unidade)
{
    raiz->info.palavraIngles = insertpalavraIngles(raiz->info.palavraIngles, palavraIng, unidade);
}

PortuguesRB *BuscarPalavra(PortuguesRB **arvore, char *palavraPortugues)
{
    PortuguesRB *atual = NULL;

    if (*arvore != NULL)
    {
        if (strcmp(palavraPortugues, (*arvore)->info.palavraPortugues) == 0)
        {
            atual = *arvore;
        }
        else if (strcmp(palavraPortugues, (*arvore)->info.palavraPortugues) < 0)
        {
            atual = BuscarPalavra(&(*arvore)->esq, palavraPortugues);
        }
        else
        {
            atual = BuscarPalavra(&(*arvore)->dir, palavraPortugues);
        }
    }
    return atual;
}

void exibirArvore(PortuguesRB *raiz)
{
    if (raiz)
    {
        exibirArvore(raiz->esq);
        printf("Cor - %d\n", raiz->cor);
        printf("Valor - %s\n", raiz->info.palavraPortugues);
        printBinaryTree(raiz->info.palavraIngles);
        printf("\n");
        exibirArvore(raiz->dir);
    }
}

void BuscarPalavraIngles(PortuguesRB **raiz, char *palavraIngles, int unidade)
{
    if (*raiz != NULL)
    {
        BuscarPalavraIngles(&(*raiz)->esq, palavraIngles, unidade);

        if ((*raiz)->info.palavraIngles != NULL && (*raiz)->info.palavraIngles->unidade == unidade)
            removerPalavraIngles(&(*raiz)->info.palavraIngles, palavraIngles);
        BuscarPalavraIngles(&(*raiz)->dir, palavraIngles, unidade);
    }
}