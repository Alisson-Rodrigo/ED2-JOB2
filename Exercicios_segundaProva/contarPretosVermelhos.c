#include <stdio.h>

typedef struct tree {
    int info;
    int cor; // 0 = vermelho, 1 = preto
    struct tree *esq;
    struct tree *dir;
} Tree;

// Função para contar os nós vermelhos e pretos na árvore
int contarNodosCores(Tree *arv, int *red, int *black) {
    if (arv == NULL) {
        return -1; // Base da recursão: se o nó for NULL, apenas retorna
    }

    // Verificar a cor do nó atual
    if (arv->cor == 0) { // Nó vermelho
        (*red)++;
    } else { // Nó preto
        (*black)++;
    }

    // Chamar recursivamente para os filhos esquerdo e direito
    contarNodosCores(arv->esq, red, black);
    contarNodosCores(arv->dir, red, black);
}

int main() {
    // Inicializar variáveis de contagem
    int red = 0, black = 0;

    // Exemplo de criação da árvore
    Tree *raiz = (Tree *)malloc(sizeof(Tree));
    raiz->info = 10;
    raiz->cor = 1; // Raiz preta
    raiz->esq = (Tree *)malloc(sizeof(Tree));
    raiz->esq->info = 5;
    raiz->esq->cor = 0; // Nó vermelho
    raiz->esq->esq = NULL;
    raiz->esq->dir = NULL;
    raiz->dir = (Tree *)malloc(sizeof(Tree));
    raiz->dir->info = 20;
    raiz->dir->cor = 1; // Nó preto
    raiz->dir->esq = NULL;
    raiz->dir->dir = NULL;

    // Chamar a função de contagem
    contarNodosCores(raiz, &red, &black);

    // Exibir o resultado
    printf("Número de nós vermelhos: %d\n", red);
    printf("Número de nós pretos: %d\n", black);

    // Liberação da memória (para exemplo simples)
    free(raiz->esq);
    free(raiz->dir);
    free(raiz);

    return 0;
}
