//
// Created by Isaac-PC on 13/06/2024.
//

#ifndef INC_1_RUBRONEGRA_H
#define INC_1_RUBRONEGRA_H

typedef enum { VERMELHO, PRETO } Cor;

typedef struct NoRB {
    int chave;
    Cor cor;
    struct NoRB* esquerda;
    struct NoRB* direita;
    struct NoRB* pai;
} NoRB;

NoRB* criarNoRB(int chave);
void inserirNoRB(NoRB** raiz, NoRB* z, int* rotacoes);
void deletarNoRB(NoRB** raiz, NoRB* z, int* rotacoes);
int buscarRB(NoRB* raiz, int chave);

#endif //INC_1_RUBRONEGRA_H
