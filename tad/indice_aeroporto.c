#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indice_aeroporto.h"
#include "meustipos.h"


IndiceAeroporto* criar_vetor(U16 capacidade){
    IndiceAeroporto *vetor_de_aeroportos = (IndiceAeroporto *) malloc(/*capacidade **/sizeof(IndiceAeroporto));
    if (vetor_de_aeroportos == NULL) return NULL; //free(vetor_de_aeroportos);

    vetor_de_aeroportos->aeroporto = (Aeroporto **) malloc(capacidade * sizeof(Aeroporto*));
    if (vetor_de_aeroportos->aeroporto == NULL) return NULL;

    for (U16 i = 0; i < capacidade; i++) vetor_de_aeroportos->aeroporto[i] = NULL;

    vetor_de_aeroportos->capacidade = capacidade;
    vetor_de_aeroportos->quantidade = 0;

    return vetor_de_aeroportos;
}


boolean free_vetor(IndiceAeroporto *vetor){
    if (vetor == NULL) return false;

    for (U16 i = 0; i < vetor->capacidade; i++){
        if (vetor->aeroporto[i] != NULL) {
            free(vetor->aeroporto[i]);
        }
    }

    free(vetor->aeroporto);
    free(vetor);

    return true;
}


boolean inserir_no_vetor(IndiceAeroporto *vetor, I8 nome[50], I8 sigla[4]){
    if (vetor == NULL || vetor->quantidade >= vetor->capacidade) return false;

    Aeroporto *novo_aeroporto = (Aeroporto *) malloc(sizeof(Aeroporto));
    if (novo_aeroporto == NULL) return false;

    strcpy((char*)novo_aeroporto->nome, (char*)nome);
    strcpy((char*)novo_aeroporto->sigla, (char*)sigla);

    for(U16 i = 0; i < vetor->capacidade; i++){
        if (vetor->aeroporto[i] == NULL){
            vetor->aeroporto[i] = novo_aeroporto;
            vetor->quantidade++;
            return true;
        }
    }

    return false;
}


boolean remover_do_vetor(IndiceAeroporto *vetor, I8 sigla[4]){
    if (vetor == NULL || vetor->quantidade == 0) return false;

    U16 elementos_encontrados = 0;

    for (U16 i = 0; i < vetor->capacidade; i++){
        if (elementos_encontrados == vetor->quantidade) break;

        if (vetor->aeroporto[i] == NULL) continue;

        elementos_encontrados++;

        if (strcmp((char*)vetor->aeroporto[i]->sigla, (char*)sigla) == 0){

            free(vetor->aeroporto[i]);
            vetor->aeroporto[i] = NULL;
            vetor->quantidade--;

            return true;
        }
    }

    return false;
}


Aeroporto recuperar_aeroporto(IndiceAeroporto *vetor, U16 indice) {
    Aeroporto aeroporto_vazio = { .nome = "", .sigla = "" };

    if (vetor == NULL || indice >= vetor->capacidade || vetor->aeroporto[indice] == NULL) {
        return aeroporto_vazio;
    }

    return *(vetor->aeroporto[indice]);
}


U16 recuperar_indice(IndiceAeroporto *vetor, I8 sigla[4]){
    if (vetor == NULL || vetor->quantidade == 0) return 65535;

    U16 elementos_encontrados = 0;

    for(U16 i = 0; i < vetor->capacidade; i++){
        if (elementos_encontrados == vetor->quantidade) break;

        if (vetor->aeroporto[i] == NULL) continue;

        elementos_encontrados++;

        if (strcmp((char*)vetor->aeroporto[i]->sigla, (char*)sigla) == 0){
            return i;
        }
    }


    return 65535;
}