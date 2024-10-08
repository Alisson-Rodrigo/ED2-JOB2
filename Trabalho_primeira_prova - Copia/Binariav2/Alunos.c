#include "Alunos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



Aluno *criar_aluno(){
    Aluno *a = (Aluno *)malloc(sizeof(Aluno));
    if(a == NULL){
        printf("Erro ao alocar aluno\n");
        exit(1);
    }
    
    a->raiz_notas = NULL;
    a->raiz_matriculas = NULL;
    a->prox = NULL;
    return a;
}

Aluno *inserir_aluno(Aluno *aluno, Aluno *no) {

    // Se a lista estiver vazia, o novo aluno será o primeiro
    if (aluno == NULL) {
        no->prox = NULL;
        return no;
    }

    Aluno *anterior = NULL;
    Aluno *atual = aluno;

    // Percorre a lista até encontrar a posição correta com base no nome
    while (atual != NULL && strcmp(atual->nome, no->nome) < 0) {
        anterior = atual;
        atual = atual->prox;
    }

    // Insere no início da lista (caso o nome do novo aluno seja menor)
    if (anterior == NULL) {
        no->prox = aluno;
        return no;
    }

    // Insere no meio ou no final da lista
    anterior->prox = no;
    no->prox = atual;

    return aluno;
}

Aluno *remover_aluno(Aluno *aluno, int matricula){
    Aluno *aux = aluno;
    Aluno *ant = NULL;

    while(aux != NULL && aux->matricula != matricula){
        ant = aux;
        aux = aux->prox;
    }

    if(aux == NULL){
        return aluno;
    }

    if(ant == NULL){
        aluno = aux->prox;
    }else{
        ant->prox = aux->prox;
    }

    free(aux);
    return aluno;
}

Aluno *buscar_aluno(Aluno *aluno, int matricula){
    Aluno *aux = aluno;

    while(aux != NULL && aux->matricula != matricula){
        aux = aux->prox;
    }

    return aux;
}

void imprimir_alunos(Aluno *aluno,int codigo_curso){
    Aluno *aux = aluno;
    while(aux != NULL){
        if(aux->codigo_curso == codigo_curso){
            printf("Matricula: %d\n", aux->matricula);
            printf("Nome: %s\n", aux->nome);
            printf("Codigo do curso: %d\n", aux->codigo_curso);
        }
        aux = aux->prox;
    }

}

int verificar_matricula_disciplinas(Aluno *raiz_alunos, int codigo_disciplina) {
    int encontrado = 0;

    for (Aluno *atual = raiz_alunos; atual != NULL; atual = atual->prox) {
        // Verifica a matrícula do aluno atual
        arvore_matricula *matricula = buscar_matricula(atual->raiz_matriculas, codigo_disciplina);
        if (matricula != NULL) {
            encontrado = 1; // Define como encontrado
        }
    }

    return encontrado;
}

