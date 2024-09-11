
typedef struct Arvore_disciplinas {
    int codigo;
    char nome[50];
    struct arvore_disciplinas *esq;
    struct arvore_disciplinas *dir;
}arvore_disciplinas;

arvore_disciplinas *criar_disciplina();
arvore_disciplinas *inserir_disciplina(arvore_disciplinas *raiz, arvore_disciplinas *no);