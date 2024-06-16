//
// Created by Isaac-PC on 13/06/2024.
//

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int altura(NoAVL* no) {
    return no ? no->altura : 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

NoAVL* criarNo(int chave) {
    NoAVL* no = (NoAVL*)malloc(sizeof(NoAVL));
    no->chave = chave;
    no->esquerda = no->direita = NULL;
    no->altura = 1;
    return no;
}

NoAVL* rotacaoDireitaAvl(NoAVL* y) {
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;
    x->direita = y;
    y->esquerda = T2;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    return x;
}

NoAVL* rotacaoEsquerdaAvl(NoAVL* x) {
    NoAVL* y = x->direita;
    NoAVL* T2 = y->esquerda;
    y->esquerda = x;
    x->direita = T2;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    return y;
}

int obterBalanceamento(NoAVL* no) {
    return no ? altura(no->esquerda) - altura(no->direita) : 0;
}

NoAVL* inserirNoAVL(NoAVL* no, int chave, int* rotacoes) {
    if (no == NULL)
        return criarNo(chave);

    if (chave < no->chave)
        no->esquerda = inserirNoAVL(no->esquerda, chave, rotacoes);
    else if (chave > no->chave)
        no->direita = inserirNoAVL(no->direita, chave, rotacoes);
    else
        return no;

    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    int balanceamento = obterBalanceamento(no);

    if (balanceamento > 1 && chave < no->esquerda->chave) {
        (*rotacoes)++;
        return rotacaoDireitaAvl(no);
    }

    if (balanceamento < -1 && chave > no->direita->chave) {
        (*rotacoes)++;
        return rotacaoEsquerdaAvl(no);
    }

    if (balanceamento > 1 && chave > no->esquerda->chave) {
        no->esquerda = rotacaoEsquerdaAvl(no->esquerda);
        (*rotacoes)++;
        return rotacaoDireitaAvl(no);
    }

    if (balanceamento < -1 && chave < no->direita->chave) {
        no->direita = rotacaoDireitaAvl(no->direita);
        (*rotacoes)++;
        return rotacaoEsquerdaAvl(no);
    }

    return no;
}

NoAVL* menorValorNo(NoAVL* no) {
    NoAVL* atual = no;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

NoAVL* deletarNoAVL(NoAVL* raiz, int chave, int* rotacoes) {
    if (raiz == NULL)
        return raiz;

    if (chave < raiz->chave)
        raiz->esquerda = deletarNoAVL(raiz->esquerda, chave, rotacoes);
    else if (chave > raiz->chave)
        raiz->direita = deletarNoAVL(raiz->direita, chave, rotacoes);
    else {
        if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {
            NoAVL* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else
                *raiz = *temp;

            free(temp);
        } else {
            NoAVL* temp = menorValorNo(raiz->direita);
            raiz->chave = temp->chave;
            raiz->direita = deletarNoAVL(raiz->direita, temp->chave, rotacoes);
        }
    }

    if (raiz == NULL)
        return raiz;

    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));
    int balanceamento = obterBalanceamento(raiz);

    if (balanceamento > 1 && obterBalanceamento(raiz->esquerda) >= 0) {
        (*rotacoes)++;
        return rotacaoDireitaAvl(raiz);
    }

    if (balanceamento > 1 && obterBalanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerdaAvl(raiz->esquerda);
        (*rotacoes)++;
        return rotacaoDireitaAvl(raiz);
    }

    if (balanceamento < -1 && obterBalanceamento(raiz->direita) <= 0) {
        (*rotacoes)++;
        return rotacaoEsquerdaAvl(raiz);
    }

    if (balanceamento < -1 && obterBalanceamento(raiz->direita) > 0) {
        raiz->direita = rotacaoDireitaAvl(raiz->direita);
        (*rotacoes)++;
        return rotacaoEsquerdaAvl(raiz);
    }

    return raiz;
}

int buscarAVL(NoAVL* raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave)
        return raiz != NULL;
    if (chave < raiz->chave)
        return buscarAVL(raiz->esquerda, chave);
    return buscarAVL(raiz->direita, chave);
}
