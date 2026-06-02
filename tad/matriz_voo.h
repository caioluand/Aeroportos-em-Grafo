#ifndef MATRIZ_VOO_H
#define MATRIZ_VOO_H
#include "meustipos.h"

typedef I16 *voo;

typedef struct {
    I8 tipico;
    Linha *no_linha;
} Raiz;

typedef struct Linha {
    I32 numero;
    Coluna *no_coluna;
    struct Linha *esquerda;
    struct Linha *direita;
} Linha;

typedef struct Coluna {
    I32 numero;
    voo voo;
    struct Coluna *esquerda;
    struct Coluna *direita;
} Coluna;

boolean nova_matriz(Raiz *matriz, I8 tipico);
boolean free_matriz(Raiz *matriz);

boolean armazenar(Raiz *matriz, U16 num_linha, U16 num_coluna, voo voo);
voo recuperar(Raiz *matriz, U16 num_linha, U16 num_coluna);

#endif // MATRIZ_VOO_H