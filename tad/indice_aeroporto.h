#ifndef INDICE_AEROPORTO_H
#define INDICE_AEROPORTO_H
#include "meustipos.h"


typedef struct {
    I8 nome[50];
    I8 sigla[4];
} Aeroporto;

typedef struct {
    Aeroporto **aeroporto;
    I16 capacidade;
    I16 quantidade;
} IndiceAeroporto;


IndiceAeroporto* criar_vetor(I16 capacidade);
boolean free_vetor(IndiceAeroporto *vetor);
I16 recuperar_indice(IndiceAeroporto *vetor, I8 sigla[4]);

boolean inserir_no_vetor(IndiceAeroporto *vetor, I8 nome[50], I8 sigla[4]);
boolean remover_do_vetor(IndiceAeroporto *vetor, I8 sigla[4]);
Aeroporto recuperar_aeroporto(IndiceAeroporto *vetor, I16 indice);


#endif // INDICE_AEROPORTO_H