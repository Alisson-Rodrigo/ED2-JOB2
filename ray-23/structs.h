#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Inglesbin{
    char *palavraIngles;
    struct Inglesbin *dir,*esq;
    int unidade;
} Inglesbin;

typedef struct info {
    char *palavraPortugues;
    Inglesbin *palavraIngles;
} Info;

typedef struct Portugues23{
    Info info1;
    Info info2;
    struct Portugues23 *cent;
    struct Portugues23 *dir;
    struct Portugues23 *esq;
    int nInfos;
} Portugues23;



#endif // STRUCTS_H