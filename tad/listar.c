#include <stdio.h>
#include <stdlib.h>
#include "meustipos.h"
#include "indice_aeroporto.h"
#include "matriz_voo.h"

// IndiceAeroporto *vetor = criar_vetor(100);
// Raiz *matriz = nova_matriz(-1);

boolean hard_code(Raiz *matriz, IndiceAeroporto *vetor){

    inserir_no_vetor(vetor, "Brasilia", "BSB");
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
    return inserir_no_vetor(vetor, nome, sigla);
}


boolean cadastrar_novo_voo(Raiz *matriz, I16 voo, I16 indice_origem, I16 indice_destino){
    return armazenar(matriz, indice_origem, indice_destino, voo);
}


boolean remover_voo(Raiz *matriz, I16 voo){
    return armazenar(matriz, recuperar_origem(matriz, voo), recuperar_destino(matriz, voo), -1);
}


boolean remover_aeroporto(Raiz *matriz, IndiceAeroporto *vetor, I8 sigla[4]) {
    I16 indice_alvo = recuperar_indice(vetor, sigla);
    
    if (indice_alvo == -1) return false;

    for (I16 i = 0; i < vetor->capacidade; i++) {
        I16 voo_origem = recuperar_voo(matriz, indice_alvo, i);
        if (voo_origem != matriz->tipico) {
            remover_voo(matriz, voo_origem);
        }

        I16 voo_destino = recuperar_voo(matriz, i, indice_alvo);
        if (voo_destino != matriz->tipico) {
            remover_voo(matriz, voo_destino);
        }
    }

    return remover_do_vetor(vetor, sigla);
}


boolean listar_voos(Raiz *matriz, IndiceAeroporto *vetor) {

    printf("\n+------------------------------------------------------------------------------------------+\n");
    printf("| %-35s | %-10s | %-37s |\n", "Aeroporto Origem", "Voo", "Aeroporto Destino");
    printf("+------------------------------------------------------------------------------------------+\n");

    I16 voos_encontrados = 0;

    for (I16 i = 0; i < vetor->capacidade; i++) {
        Aeroporto origem = recuperar_aeroporto(vetor, i);
        
        if (origem.sigla[0] == '\0') continue; 

        for (I16 j = 0; j < vetor->capacidade; j++) {
            Aeroporto destino = recuperar_aeroporto(vetor, j);
            if (destino.sigla[0] == '\0') continue;

            I16 voo = recuperar_voo(matriz, i, j);

            if (voo != matriz->tipico) {
                voos_encontrados++;
                
                char str_origem[60];
                char str_destino[60];
                sprintf(str_origem, "%s (%s)", origem.nome, origem.sigla);
                sprintf(str_destino, "%s (%s)", destino.nome, destino.sigla);

                printf("| %-35s | %03d        | %-37s |\n", str_origem, voo, str_destino);
            }
        }
    }

    if (voos_encontrados == 0) printf("| %-88s |\n", "Nenhum voo cadastrado no sistema no momento.");

    printf("+------------------------------------------------------------------------------------------+\n\n");
    
    return true;
}


        void buscar_caminhos_dfs(Raiz *matriz, IndiceAeroporto *vetor, 
                                I16 atual, I16 destino, 
                                I16 *caminho, I16 passos, 
                                boolean *visitados, boolean *encontrou) {
            
            caminho[passos] = atual;
            visitados[atual] = true;

            if (atual == destino) {
                *encontrou = true;
                
                for (I16 i = 0; i < passos; i++) {
                    Aeroporto orig = recuperar_aeroporto(vetor, caminho[i]);
                    Aeroporto dest = recuperar_aeroporto(vetor, caminho[i + 1]);
                    I16 voo = recuperar_voo(matriz, caminho[i], caminho[i + 1]);

                    char str_origem[60], str_destino[60], str_voo[15];
                    sprintf(str_origem, "%s (%s)", orig.nome, orig.sigla);
                    sprintf(str_destino, "%s (%s)", dest.nome, dest.sigla);
                    sprintf(str_voo, "%03d", voo);

                    printf("| %-35s | %-10s | %-37s |\n", str_origem, str_voo, str_destino);
                }
                printf("+------------------------------------------------------------------------------------------+\n");
            } else {
                for (I16 proximo = 0; proximo < vetor->capacidade; proximo++) {
                    if (!visitados[proximo]) {
                        Aeroporto aero_prox = recuperar_aeroporto(vetor, proximo);
                        if (aero_prox.sigla[0] == '\0') continue;

                        I16 voo = recuperar_voo(matriz, atual, proximo);
                        if (voo != matriz->tipico) {
                            buscar_caminhos_dfs(matriz, vetor, proximo, destino, caminho, passos + 1, visitados, encontrou);
                        }
                    }
                }
            }

            visitados[atual] = false;
        }
boolean listar_trajetos(Raiz *matriz, IndiceAeroporto *vetor, I8 sigla_origem[4], I8 sigla_destino[4]) {
    if (matriz == NULL || vetor == NULL) return false;

    I16 indice_origem = recuperar_indice(vetor, sigla_origem);
    I16 indice_destino = recuperar_indice(vetor, sigla_destino);

    if (indice_origem == -1 || indice_destino == -1) {
        printf("\n+------------------------------------------------------------------------------------------+\n");
        printf("| %-35s | %-10s | %-37s |\n", "Aeroporto Origem", "Voo", "Aeroporto Destino");
        printf("+------------------------------------------------------------------------------------------+\n");
        printf("| %-88s |\n", "Erro: Aeroporto de origem ou destino nao encontrado no sistema.");
        printf("+------------------------------------------------------------------------------------------+\n");
        return false;
    }

    printf("\n+------------------------------------------------------------------------------------------+\n");
    printf("| %-35s | %-10s | %-37s |\n", "Aeroporto Origem", "Voo", "Aeroporto Destino");
    printf("+------------------------------------------------------------------------------------------+\n");

    boolean *visitados = (boolean *)calloc(vetor->capacidade, sizeof(boolean));
    I16 *caminho = (I16 *)malloc(vetor->capacidade * sizeof(I16));
    boolean encontrou_trajeto = false;

    buscar_caminhos_dfs(matriz, vetor, indice_origem, indice_destino, caminho, 0, visitados, &encontrou_trajeto);

    if (!encontrou_trajeto) {
        printf("| %-88s |\n", "Nenhum trajeto encontrado entre estes aeroportos.");
        printf("+------------------------------------------------------------------------------------------+\n");
    }

    free(visitados);
    free(caminho);

    printf("\n"); 
    return true;
}


boolean free_tudo(Raiz *matriz, IndiceAeroporto *vetor){
    free_matriz(matriz);
    return free_vetor(vetor);
}