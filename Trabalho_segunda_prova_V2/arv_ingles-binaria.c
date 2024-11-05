#include "arv_ingles-binaria.h"

// Função para criar um novo nó na árvore binária de busca
TreeNode* createNode(const char* word, int unit) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode != NULL) {
        strcpy(newNode->englishWord, word);
        newNode->unit = unit;
        newNode->left = newNode->right = NULL;
    }
    return newNode;
}

// Função para inserir uma palavra em inglês na árvore binária de busca
TreeNode* insertEnglishWord(TreeNode* root, const char* word, int unit) {
    TreeNode *result;
    if (root == NULL) {
        result = createNode(word, unit);
    } else {
        if (strcmp(word, root->englishWord) < 0) {
            root->left = insertEnglishWord(root->left, word, unit);
        } else if (strcmp(word, root->englishWord) > 0) {
            root->right = insertEnglishWord(root->right, word, unit);
        }
        result = root;
    }
    return result;
}

// Função para buscar uma palavra em inglês na árvore binária de busca
TreeNode* searchEnglishWord(TreeNode* root, const char* word) {
    TreeNode *result;
    if (root == NULL || strcmp(root->englishWord, word) == 0) {
        result = root;
    } else {
        if (strcmp(word, root->englishWord) < 0) {
            result = searchEnglishWord(root->left, word);
        } else {
            result = searchEnglishWord(root->right, word);
        }
    }
    return result;
}

// Função para imprimir a árvore binária em ordem alfabética (simples visualização)
void printBinaryTree(TreeNode* root) {
    if (root != NULL) {
        printBinaryTree(root->left);
        printf("%s (Unit %d)\n", root->englishWord, root->unit);
        printBinaryTree(root->right);
    }
}

int main () {
    TreeNode *root = NULL;
    TreeNode *searchResult;
    root = insertEnglishWord(root, "apple", 1);
    root = insertEnglishWord(root, "banana", 1);
    root = insertEnglishWord(root, "cherry", 1);
    root = insertEnglishWord(root, "date", 1);
    root = insertEnglishWord(root, "elderberry", 1);
    root = insertEnglishWord(root, "fig", 1);
    root = insertEnglishWord(root, "grape", 1);
    root = insertEnglishWord(root, "honeydew", 1);
    root = insertEnglishWord(root, "kiwi", 1);
    root = insertEnglishWord(root, "lemon", 1);
    root = insertEnglishWord(root, "mango", 1);
    root = insertEnglishWord(root, "nectarine", 1);
    root = insertEnglishWord(root, "orange", 1);
    root = insertEnglishWord(root, "pear", 1);
    root = insertEnglishWord(root, "quince", 1);
    root = insertEnglishWord(root, "raspberry", 1);
    root = insertEnglishWord(root, "strawberry", 1);
    root = insertEnglishWord(root, "tangerine", 1);
    root = insertEnglishWord(root, "ugli", 1);
    root = insertEnglishWord(root, "vanilla", 1);
    root = insertEnglishWord(root, "watermelon", 1);
    printBinaryTree(root);
    searchResult = searchEnglishWord(root, "banana");
    if (searchResult != NULL) {
        printf("Word found: %s (Unit %d)\n", searchResult->englishWord, searchResult->unit);
    } else {
        printf("Word not found.\n");
    }
    searchResult = searchEnglishWord(root, "grapefruit");
    if (searchResult != NULL) {
        printf("Word found: %s (Unit %d)\n", searchResult->englishWord, searchResult->unit);
    } else {
        printf("Word not found.\n");
    }
    return 0;
}
