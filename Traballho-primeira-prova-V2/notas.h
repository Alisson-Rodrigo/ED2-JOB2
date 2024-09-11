typedef struct Arvore_notas
{
    int codigo_disciplina;
    int semestre_cursado;
    float nota_final;
    struct arvore_notas *esq;
    struct arvore_notas *dir;
}arvore_notas;

