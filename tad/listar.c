#include <stdio.h>
#include "meustipos.h"
#include "indice_aeroporto.h"
#include "matriz_voo.h"

// IndiceAeroporto *vetor = criar_vetor(100);
// Raiz *matriz = nova_matriz(-1);

boolean hard_code(Raiz *matriz, IndiceAeroporto *vetor){

    inserir_no_vetor(vetor, "Brasília", "BSB");
    inserir_no_vetor(vetor, "Belo Horizonte", "CNF");
    inserir_no_vetor(vetor, "Rio de Janeiro", "GIG");
    inserir_no_vetor(vetor, "Guarulhos", "GRU");
    inserir_no_vetor(vetor, "Salvador", "SSA");

    armazenar(matriz, recuperar_indice(vetor, "GRU"), recuperar_indice(vetor, "BSB"), 50);
    armazenar(matriz, recuperar_indice(vetor, "GIG"), recuperar_indice(vetor, "CNF"), 554);  
    armazenar(matriz, recuperar_indice(vetor, "GRU"), recuperar_indice(vetor, "CNF"), 102);
    armazenar(matriz, recuperar_indice(vetor, "SSA"), recuperar_indice(vetor, "CNF"), 215);
    armazenar(matriz, recuperar_indice(vetor, "CNF"), recuperar_indice(vetor, "GIG"), 555);
    armazenar(matriz, recuperar_indice(vetor, "GRU"), recuperar_indice(vetor, "GIG"), 89);
    armazenar(matriz, recuperar_indice(vetor, "CNF"), recuperar_indice(vetor, "GRU"), 101);
    armazenar(matriz, recuperar_indice(vetor, "GIG"), recuperar_indice(vetor, "GRU"), 90);
    armazenar(matriz, recuperar_indice(vetor, "BSB"), recuperar_indice(vetor, "SSA"), 107);
    armazenar(matriz, recuperar_indice(vetor, "CNF"), recuperar_indice(vetor, "SSA"), 214); // lembrar de printar com %03d

    return true;
}


boolean cadastrar_novo_aeroporto(IndiceAeroporto *vetor, I8 nome[50], I8 sigla[4]){
    return inserir_no_vetor(vetor, nome[50], sigla[4]);
}


boolean cadastrar_novo_voo(Raiz *matriz, U16 voo, U16 indice_origem, U16 indice_destino){
    return armazenar(matriz, indice_origem, indice_destino, voo);
}


boolean remover_aeroporto(IndiceAeroporto *vetor, I8 sigla[4]){
    return remover_do_vetor(vetor, sigla[4]);
}


boolean remover_voo(Raiz *matriz, U16 voo){
    //return armazenar(matriz, U16 num_linha, U16 num_coluna, voo);
}


