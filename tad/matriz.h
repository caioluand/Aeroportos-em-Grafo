#ifndef MATRIZ_H
#define MATRIZ_H
#include "meustipos.h"

typedef void *valor;

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
    valor valor;
    struct Coluna *esquerda;
    struct Coluna *direita;
} Coluna;

boolean nova_matriz(Raiz *matriz, I8 tipico);
boolean free_matriz(Raiz *matriz);
boolean armazenar(Raiz *matriz, U16 num_linha, U16 num_coluna, valor valor);
valor recuperar(Linha *linha, Coluna *coluna);

#endif // MATRIZ_H