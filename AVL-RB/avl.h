//
// Created by Isaac-PC on 13/06/2024.
//

#ifndef INC_1_AVL_H
#define INC_1_AVL_H

typedef struct NoAVL {
    int chave;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
    int altura;
} NoAVL;

NoAVL* criarNo(int chave);
NoAVL* inserirNoAVL(NoAVL* no, int chave, int* rotacoes);
NoAVL* deletarNoAVL(NoAVL* raiz, int chave, int* rotacoes);
int buscarAVL(NoAVL* raiz, int chave);

#endif //INC_1_AVL_H
