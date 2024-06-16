#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"
#include "rubronegra.h"

#define NUM_INSERTS 50000
#define NUM_SEARCHES 5000

int main() {
    NoAVL* raizAVL = NULL;
    NoRB* raizRB = NULL;
    int rotacoesAVLInsercao = 0;
    int rotacoesAVLRemocao = 0;
    int rotacoesRBInsercao = 0;
    int rotacoesRBRemocao = 0;
    int valores[NUM_INSERTS];

    FILE * avlFile;

    for (int i = 0; i < NUM_INSERTS; i++) {
        valores[i] = i + 1;
    }
    
    struct timespec inicio, fim;

    // Inserção na árvore AVL
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int i = 0; i < NUM_INSERTS; i++) {
        raizAVL = inserirNoAVL(raizAVL, valores[i], &rotacoesAVLInsercao);
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempoInsercaoAVL = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    // Inserção na árvore Rubro-Negra
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int i = 0; i < NUM_INSERTS; i++) {
        inserirNoRB(&raizRB, criarNoRB(valores[i]), &rotacoesRBInsercao);
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempoInsercaoRB = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    // Remoção na árvore AVL
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int i = 0; i < NUM_INSERTS; i++) {
        raizAVL = deletarNoAVL(raizAVL, valores[i], &rotacoesAVLRemocao);
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempoRemocaoAVL = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    // Remoção na árvore Rubro-Negra
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int i = 0; i < NUM_INSERTS; i++) {
        deletarNoRB(&raizRB, criarNoRB(valores[i]), &rotacoesRBRemocao);
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempoRemocaoRB = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    // Busca na árvore AVL
    int valoresAleatorios[NUM_SEARCHES];
    for (int i = 0; i < NUM_SEARCHES; i++) {
        valoresAleatorios[i] = rand() % NUM_INSERTS + 1;
    }

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int i = 0; i < NUM_SEARCHES; i++) {
        buscarAVL(raizAVL, valoresAleatorios[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempoBuscaAVL = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    // Busca na árvore Rubro-Negra
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int i = 0; i < NUM_SEARCHES; i++) {
        buscarRB(raizRB, valoresAleatorios[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempoBuscaRB = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    printf("Arvore AVL - Tempo de insercao: %f segundos\n", tempoInsercaoAVL);
    printf("Arvore AVL - Rotacoes na insercao: %d\n", rotacoesAVLInsercao);
    printf("Arvore AVL - Tempo de remocao: %f segundos\n", tempoRemocaoAVL);
    printf("Arvore AVL - Rotacoes na remocao: %d\n", rotacoesAVLRemocao);
    printf("Arvore AVL - Tempo de busca: %f segundos\n", tempoBuscaAVL);
    printf("Arvore Rubro-Negra - Tempo de insercao: %f segundos\n", tempoInsercaoRB);
    printf("Arvore Rubro-Negra - Rotacoes na insercao: %d\n", rotacoesRBInsercao);
    printf("Arvore Rubro-Negra - Tempo de remocao: %f segundos\n", tempoRemocaoRB);
    printf("Arvore Rubro-Negra - Rotacoes na remocao: %d\n", rotacoesRBRemocao);
    printf("Arvore Rubro-Negra - Tempo de busca: %f segundos\n", tempoBuscaRB);

    //inserir em arquivo csv
    printf("%d;%f;%d;%d;%f;%d;%d;%f;", NUM_INSERTS, tempoInsercaoRB, rotacoesRBInsercao, NUM_INSERTS, tempoRemocaoRB, rotacoesRBRemocao, NUM_SEARCHES, tempoBuscaRB);
    return 0;
}
