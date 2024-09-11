struct arvore_notas
{
    int codigo_disciplina;
    int semestre_cursado;
    float nota_final;
    struct arvore_notas *esq;
    struct arvore_notas *dir;
};

typedef struct arvore_notas Arvore_notas;