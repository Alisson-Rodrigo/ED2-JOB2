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

    return 0;
}

//1.Faça uma função que retorne por função a quantidade de elementos pretos da árvore vermelho e preta
void contarPretos(Tree *arv, int *black) {
    if (arv) {
        if (arv->cor == 1) {
            (*black)++;
        }
        contarPretos(arv->esq, black);
        contarPretos(arv->dir, black);
    }
}

//2.Faça uma função que retorne por parâmetro a soma dos múltiplos de 5 que são da cor vermelha e por função o .produto dos múltiplos de 5 que são da cor preta da árvore vermelho e preta

int somarMultiplos5(Tree *arv, int *soma) {
    int produto = 1;

    if (arv) {
        if(arv->cor == 0 && arv->info % 5 == 0) {
            *soma = *soma + arv->info;
        }

        if(arv->cor == 1 && arv->info % 5 == 0) {
            produto = produto * arv->info;
        }

        produto *= somarMultiplos5(arv->esq, soma);
        produto *= somarMultiplos5(arv->dir, soma);
    }

    return produto;
}

//4.Faça uma função que, dado um valor, retorne por parâmetro a quantidade de ascendentes (caso o nó seja preto) e a quantidade de descendentes (caso o nó seja vermelho)

void contarAscDesc(Tree *arv, int valor, int *asc, int *desc) {
    if (arv) {
        if (arv->info == valor) {
            if (arv->cor == 1) {
                *asc = contarNos(arv->dir);
            }
            else {
                *desc = contarNos(arv->esq);
            }
        contarAscDesc(arv->esq, valor, asc, desc);
        contarAscDesc(arv->dir, valor, asc, desc);
        }
    }
}

int contarNos (Tree *arv ) {
    int qtdNos = 0;
     if (arv) {
        qtdNos++;
        qtdNos += contarNos(arv->esq);
        qtdNos += contarNos(arv->dir);
     }
}

//

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
