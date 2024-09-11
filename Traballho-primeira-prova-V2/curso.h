#include "disciplinas.h"

typedef struct arvore_curso {
    int codigo;
    char nome[50];
    int periodo;
    Arvore_disciplinas *raiz_disciplinas; 
    struct arvore_curso *esq;
    struct arvore_curso *dir;
}Arvore_curso;

Arvore_curso *criar_curso();
Arvore_curso *inserir_curso(Arvore_curso *curso, Arvore_curso *no);