#include <stdio.h>
#include "indice_aeroporto.h"
#include "meustipos.h"


IndiceAeroporto* criar_vetor(I16 capacidade){
    IndiceAeroporto *vetor_de_aeroportos = (IndiceAeroporto *) malloc(capacidade * sizeof(IndiceAeroporto));
    if (vetor_de_aeroportos == NULL) return NULL;

    vetor_de_aeroportos->aeroporto = (Aeroporto **) malloc(capacidade * sizeof(Aeroporto*));
    if (vetor_de_aeroportos->aeroporto == NULL) return NULL;

    for (I16 i = 0; i < capacidade; i++) vetor_de_aeroportos->aeroporto[i] = NULL;

    vetor_de_aeroportos->capacidade = capacidade;
    vetor_de_aeroportos->quantidade = 0;

    return vetor_de_aeroportos;
}

boolean free_vetor(IndiceAeroporto *vetor){
    if (vetor == NULL) return false;

    for (I16 i = 0; i < vetor->capacidade; i++){
        if (vetor->aeroporto[i] != NULL) {
            free(vetor->aeroporto[i]);
        }
    }

    free(vetor->aeroporto);
    free(vetor);

    return true;
}

boolean inserir_no_vetor(IndiceAeroporto *vetor, I8 nome[50], I16 sigla){
    if (vetor == NULL || vetor->capacidade >= vetor->quantidade) return false;

    Aeroporto *novo_aeroporto = (Aeroporto *) malloc(sizeof(Aeroporto));
    if (novo_aeroporto == NULL) return false;

    strcpy((char*)novo_aeroporto->nome, (char*)nome);
    novo_aeroporto->sigla = sigla;

    vetor->aeroporto[vetor->capacidade] = novo_aeroporto;

    vetor->capacidade++;

    return true;
}

boolean remover_do_vetor(IndiceAeroporto *vetor, I16 sigla){
    if (vetor == NULL|| vetor->quantidade == 0) return false;

    for (I16 i = 0; i < vetor->quantidade; i++){
        if (vetor->aeroporto[i]->sigla = sigla){

            free(vetor->aeroporto[i]);
            while (i < vetor->quantidade - 1){
                vetor->aeroporto[i] = vetor->aeroporto[i + 1];
                i++;
            }
            vetor->aeroporto[vetor->quantidade - 1] = NULL;
            vetor->quantidade--;

            return true;
        }
    }

    return false;
}

Aeroporto recuperar(IndiceAeroporto *vetor, U16 indice) {
    Aeroporto aeroporto_vazio = { .nome = "", .sigla = 0 };

    if (vetor == NULL || indice >= vetor->quantidade || vetor->aeroporto[indice] == NULL) {
        return aeroporto_vazio;
    }

    return *(vetor->aeroporto[indice]);
}