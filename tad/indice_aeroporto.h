#ifndef INDICE_AEROPORTO_H
#define INDICE_AEROPORTO_H
#include "meustipos.h"


typedef struct {
    I8 nome[50];
    I16 sigla;
} Aeroporto;

typedef struct {
    Aeroporto **aeroporto;
    I16 capacidade;
    I16 quantidade;
} IndiceAeroporto;


IndiceAeroporto* criar_vetor(I16 capacidade);
boolean free_vetor(IndiceAeroporto *vetor);

boolean inserir_no_vetor(IndiceAeroporto *vetor, I8 nome[50], I16 sigla);
boolean remover_do_vetor(IndiceAeroporto *vetor, I16 sigla);
Aeroporto recuperar(IndiceAeroporto *vetor, U16 indice);

#endif // INDICE_AEROPORTO_H