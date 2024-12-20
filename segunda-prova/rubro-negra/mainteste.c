#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Disciplina.C"
#include "Curso.C"

#define TOTAL_CODES 100
#define NUM_SEARCHES 30

void menu();

#ifdef _WIN32
#include <windows.h>

// Função para obter o tempo em alta resolução no Windows
void get_current_time(struct timespec *ts) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER currentTime;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&currentTime);
    ts->tv_sec = currentTime.QuadPart / frequency.QuadPart;
    ts->tv_nsec = (currentTime.QuadPart % frequency.QuadPart) * 1E9 / frequency.QuadPart;
}

#else
// Para sistemas POSIX, como Linux
#include <unistd.h>
#include <sys/time.h>

void get_current_time(struct timespec *ts) {
    clock_gettime(CLOCK_MONOTONIC, ts);
}
#endif

double get_elapsed_time(struct timespec *start, struct timespec *end) {
    return (end->tv_sec - start->tv_sec) + (end->tv_nsec - start->tv_nsec) / 1E9;
}

// Função para gerar códigos de curso únicos e contar os passos e tempo
int generate_unique_codes(int *codes, int total, int *passos, double *tempo) {
    int generated = 0;
    bool is_unique;
    struct timespec start_time, end_time;

    *passos = 0;
    get_current_time(&start_time);

    while (generated < total) {
        int new_code = rand() % 10000 + 1; // Gerar código aleatório entre 1 e 1000
        int i;

        // Verificar se new_code já foi gerado
        is_unique = true;
        for (i = 0; i < generated; ++i) {
            (*passos)++;
            if (codes[i] == new_code) {
                is_unique = false;
                break;
            }
        }

        // Se único, adicionar ao array de códigos
        if (is_unique) {
            codes[generated] = new_code;
            generated++;
        }
    }

    get_current_time(&end_time);
    *tempo = get_elapsed_time(&start_time, &end_time);

    return generated; // Retornar o número de códigos gerados (deve ser igual a total)
}

// Função para buscar um curso na árvore e contar os passos
arv_curso *buscar_disciplina_curso_contador(arv_curso *raiz, int codigo, int *passos) {
    *passos = 0;
    struct timespec start_time, end_time;

    get_current_time(&start_time);

    arv_curso *atual = raiz;
    while (atual != NULL && atual->dados->codigo != codigo) {
        (*passos)++;
        if (codigo < atual->dados->codigo)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    get_current_time(&end_time);
    double tempo = get_elapsed_time(&start_time, &end_time);
    printf("Tempo gasto na busca: %.9f segundos\n", tempo);

    return atual;
}

int main() {
    srand(time(NULL)); // Inicializar semente para números aleatórios

    arv_curso *raiz_curso = NULL;
    int opcao;
    int codigo_curso, bloco, carga_horaria;

    // Array para armazenar os códigos de curso gerados
    int unique_codes[TOTAL_CODES];
    int passos;
    double tempo;
    int i;

    // Gerar códigos únicos e contar passos e tempo
    int num_generated = generate_unique_codes(unique_codes, TOTAL_CODES, &passos, &tempo);
    if (num_generated != TOTAL_CODES) {
        printf("Erro ao gerar códigos de curso únicos.\n");
        return 1;
    }

    // Inserir cursos com códigos únicos na árvore
    for (i = 0; i < TOTAL_CODES; ++i) {
        arv_curso *novo_curso = cria_no_curso();
        if (novo_curso == NULL) {
            printf("Erro ao criar novo curso.\n");
            break;
        }

        novo_curso->dados->codigo = unique_codes[i]; // Atribuir código único ao curso

        raiz_curso = inserir_curso(raiz_curso, novo_curso);
    }

    // Realizar busca 30 vezes por códigos gerados anteriormente
    for (i = 0; i < NUM_SEARCHES; ++i) {
        // Escolher um código aleatório gerado anteriormente para buscar
        int codigo_busca = unique_codes[rand() % TOTAL_CODES];

        printf("\nBusca %d:\n", i + 1);
        printf("Codigo buscado: %d\n", codigo_busca);

        arv_curso *curso_encontrado = buscar_disciplina_curso_contador(raiz_curso, codigo_busca, &passos);

        printf("Passos na busca: %d\n", passos);
    }

    // Restante da lógica do programa guiado por menu
    // Exemplo: menu(), switch case, etc.

    return 0;
}
