//
// Created by Isaac-PC on 13/06/2024.
//

#include "rubronegra.h"
#include <stdio.h>
#include <stdlib.h>

NoRB* criarNoRB(int chave) {
    NoRB* no = (NoRB*)malloc(sizeof(NoRB));
    no->chave = chave;
    no->esquerda = no->direita = no->pai = NULL;
    no->cor = VERMELHO;
    return no;
}

void rotacaoEsquerda(NoRB** raiz, NoRB* x, int* rotacoes) {
    NoRB* y = x->direita;
    x->direita = y->esquerda;
    if (y->esquerda != NULL) {
        y->esquerda->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == NULL) {
        *raiz = y;
    } else if (x == x->pai->esquerda) {
        x->pai->esquerda = y;
    } else {
        x->pai->direita = y;
    }
    y->esquerda = x;
    x->pai = y;
    (*rotacoes)++;
}

void rotacaoDireita(NoRB** raiz, NoRB* y, int* rotacoes) {
    NoRB* x = y->esquerda;
    y->esquerda = x->direita;
    if (x->direita != NULL) {
        x->direita->pai = y;
    }
    x->pai = y->pai;
    if (y->pai == NULL) {
        *raiz = x;
    } else if (y == y->pai->direita) {
        y->pai->direita = x;
    } else {
        y->pai->esquerda = x;
    }
    x->direita = y;
    y->pai = x;
    (*rotacoes)++;
}

void corrigirInsercao(NoRB** raiz, NoRB* z, int* rotacoes) {
    while (z->pai != NULL && z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esquerda) {
            NoRB* y = z->pai->pai->direita;
            if (y != NULL && y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->direita) {
                    z = z->pai;
                    rotacaoEsquerda(raiz, z, rotacoes);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoDireita(raiz, z->pai->pai, rotacoes);
            }
        } else {
            NoRB* y = z->pai->pai->esquerda;
            if (y != NULL && y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esquerda) {
                    z = z->pai;
                    rotacaoDireita(raiz, z, rotacoes);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(raiz, z->pai->pai, rotacoes);
            }
        }
    }
    (*raiz)->cor = PRETO;
}

void inserirNoRB(NoRB** raiz, NoRB* z, int* rotacoes) {
    NoRB* y = NULL;
    NoRB* x = *raiz;
    while (x != NULL) {
        y = x;
        if (z->chave < x->chave) {
            x = x->esquerda;
        } else {
            x = x->direita;
        }
    }
    z->pai = y;
    if (y == NULL) {
        *raiz = z;
    } else if (z->chave < y->chave) {
        y->esquerda = z;
    } else {
        y->direita = z;
    }
    corrigirInsercao(raiz, z, rotacoes);
}

NoRB* menorValorNoRB(NoRB* no) {
    NoRB* atual = no;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

void corrigirRemocao(NoRB** raiz, NoRB* x, int* rotacoes) {
    while (x != *raiz && x->cor == PRETO) {
        if (x == x->pai->esquerda) {
            NoRB* w = x->pai->direita;
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoEsquerda(raiz, x->pai, rotacoes);
                w = x->pai->direita;
            }
            if (w->esquerda->cor == PRETO && w->direita->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (w->direita->cor == PRETO) {
                    w->esquerda->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoDireita(raiz, w, rotacoes);
                    w = x->pai->direita;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->direita->cor = PRETO;
                rotacaoEsquerda(raiz, x->pai, rotacoes);
                x = *raiz;
            }
        } else {
            NoRB* w = x->pai->esquerda;
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoDireita(raiz, x->pai, rotacoes);
                w = x->pai->esquerda;
            }
            if (w->direita->cor == PRETO && w->esquerda->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (w->esquerda->cor == PRETO) {
                    w->direita->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoEsquerda(raiz, w, rotacoes);
                    w = x->pai->esquerda;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->esquerda->cor = PRETO;
                rotacaoDireita(raiz, x->pai, rotacoes);
                x = *raiz;
            }
        }
    }
    x->cor = PRETO;
}

void deletarNoRB(NoRB** raiz, NoRB* z, int* rotacoes) {
    NoRB* y = z;
    NoRB* x;
    Cor corOriginalDeY = y->cor;

    if (z->esquerda == NULL) {
        x = z->direita;
        if (z->pai == NULL) {
            *raiz = x;
        } else if (z == z->pai->esquerda) {
            z->pai->esquerda = x;
        } else {
            z->pai->direita = x;
        }
        if (x != NULL) {
            x->pai = z->pai;
        }
    } else if (z->direita == NULL) {
        x = z->esquerda;
        if (z->pai == NULL) {
            *raiz = x;
        } else if (z == z->pai->esquerda) {
            z->pai->esquerda = x;
        } else {
            z->pai->direita = x;
        }
        if (x != NULL) {
            x->pai = z->pai;
        }
    } else {
        y = menorValorNoRB(z->direita);
        corOriginalDeY = y->cor;
        x = y->direita;
        if (y->pai == z) {
            if (x != NULL) {
                x->pai = y;
            }
        } else {
            if (y->pai != NULL) {
                if (y == y->pai->esquerda) {
                    y->pai->esquerda = x;
                } else {
                    y->pai->direita = x;
                }
            }
            y->direita = z->direita;
            if (z->direita != NULL) {
                z->direita->pai = y;
            }
        }
        if (z->pai == NULL) {
            *raiz = y;
        } else if (z == z->pai->esquerda) {
            z->pai->esquerda = y;
        } else {
            z->pai->direita = y;
        }
        y->pai = z->pai;
        y->cor = z->cor;
        y->esquerda = z->esquerda;
        if (z->esquerda != NULL) {
            z->esquerda->pai = y;
        }
    }
    free(z);

    if (corOriginalDeY == PRETO) {
        corrigirRemocao(raiz, x, rotacoes);
    }
}

int buscarRB(NoRB* raiz, int chave) {
    while (raiz != NULL && raiz->chave != chave) {
        if (chave < raiz->chave) {
            raiz = raiz->esquerda;
        } else {
            raiz = raiz->direita;
        }
    }
    return raiz != NULL;
}
