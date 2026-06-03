#ifndef MATRIZ_VOO_H
#define MATRIZ_VOO_H
#include "meustipos.h"


typedef struct Coluna {
    U16 numero;
    I16 voo;
    struct Coluna *esquerda;
    struct Coluna *direita;
} Coluna;

typedef struct Linha {
    U16 numero;
    Coluna *no_coluna;
    struct Linha *esquerda;
    struct Linha *direita;
} Linha;

typedef struct {
    I16 tipico;
    Linha *no_linha;
} Raiz;


Raiz* nova_matriz(I16 tipico);
boolean free_matriz(Raiz *matriz);

boolean armazenar(Raiz *matriz, U16 num_linha, U16 num_coluna, I16 voo);
I16 recuperar_voo(Raiz *matriz, U16 num_linha, U16 num_coluna);


#endif // MATRIZ_VOO_H