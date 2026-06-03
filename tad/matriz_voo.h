#ifndef MATRIZ_VOO_H
#define MATRIZ_VOO_H
#include "meustipos.h"


typedef struct Coluna {
    I16 numero;
    I16 voo;
    struct Coluna *esquerda;
    struct Coluna *direita;
} Coluna;

typedef struct Linha {
    I16 numero;
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

boolean armazenar(Raiz *matriz, I16 num_linha, I16 num_coluna, I16 voo);
I16 recuperar_voo(Raiz *matriz, I16 num_linha, I16 num_coluna);
I16 recuperar_origem(Raiz *matriz, I16 voo);
I16 recuperar_destino(Raiz *matriz, I16 voo);


#endif // MATRIZ_VOO_H