
typedef struct arvore_disciplinas {
    int codigo;
    char nome[50];
    struct arvore_disciplinas *esq;
    struct arvore_disciplinas *dir;
}Arvore_disciplinas;

Arvore_disciplinas *criar_disciplina();
Arvore_disciplinas *inserir_disciplina(Arvore_disciplinas *raiz, Arvore_disciplinas *no);