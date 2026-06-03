#include <stdio.h>
#include <stdlib.h>
#include "matriz_voo.h"
#include "meustipos.h"


Raiz* nova_matriz(I16 t) {
    Raiz *matriz = (Raiz *) malloc(sizeof(Raiz));
    if (matriz == NULL) return NULL;

    matriz->tipico = t;
    matriz->no_linha = NULL;
    
    return matriz;
}

        void free_arvore_colunas(Coluna *col) {
            if (col == NULL) return;

            free_arvore_colunas(col->esquerda);
            free_arvore_colunas(col->direita);

            //free(col->voo); 

            free(col);
        }
        void free_arvore_linhas(Linha *lin) {
            if (lin == NULL) return;

            free_arvore_linhas(lin->esquerda);
            free_arvore_linhas(lin->direita);

            free_arvore_colunas(lin->no_coluna);

            free(lin);
        }
boolean free_matriz(Raiz *matriz) {
    if (matriz == NULL || matriz->no_linha==NULL) return false;

    free_arvore_linhas(matriz->no_linha);

    matriz->no_linha = NULL;

    return true;
}


        Linha* criar_linha_com_coluna(Linha *raiz, I16 num_linha, I16 num_coluna, I16 voo, boolean *linha_ja_existe){
            if (raiz == NULL) {
                Linha *linha_nova = (Linha *)malloc(sizeof(Linha));
                if (linha_nova == NULL) return NULL;

                Coluna *coluna_nova = (Coluna *)malloc(sizeof(Coluna));
                if (coluna_nova == NULL) return NULL;

                linha_nova->numero = num_linha;
                linha_nova->no_coluna = coluna_nova;
                linha_nova->esquerda = NULL;
                linha_nova->direita = NULL;  

                coluna_nova->numero = num_coluna;
                coluna_nova->voo = voo;
                coluna_nova->esquerda = NULL;
                coluna_nova->direita = NULL;

                return linha_nova;
            }

            if (num_linha < raiz->numero) {
                raiz->esquerda = criar_linha_com_coluna(raiz->esquerda, num_linha, num_coluna, voo, linha_ja_existe);
            } else if (num_linha > raiz->numero) {
                raiz->direita = criar_linha_com_coluna(raiz->direita, num_linha, num_coluna, voo, linha_ja_existe);
            } else {
                *linha_ja_existe = true;
            }

            return raiz;
        }
        Linha* achar_no_linha(Linha *raiz, I16 num_linha){

            if (raiz == NULL) return NULL;

            if (num_linha > raiz->numero){
                return achar_no_linha(raiz->direita, num_linha);
            } else if (num_linha < raiz->numero){
                return achar_no_linha(raiz->esquerda, num_linha);
            }

            return raiz;
        }
        Coluna* criar_coluna(Coluna *raiz, I16 num_coluna, I16 voo, boolean *coluna_ja_existe){
            if (raiz == NULL) {
                Coluna *coluna_nova = (Coluna *)malloc(sizeof(Coluna));
                if (coluna_nova == NULL) return NULL;

                coluna_nova->numero = num_coluna;
                coluna_nova->voo = voo;
                coluna_nova->esquerda = NULL;
                coluna_nova->direita = NULL;

                return coluna_nova;
            }

            if (num_coluna < raiz->numero) {
                raiz->esquerda = criar_coluna(raiz->esquerda, num_coluna, voo, coluna_ja_existe);
            } else if (num_coluna > raiz->numero) {
                raiz->direita = criar_coluna(raiz->direita, num_coluna, voo, coluna_ja_existe);
            } else {
                *coluna_ja_existe = true;
                //raiz->voo = voo; // deixar essa linha inutiliza achar_no_coluna depois de um criar_coluna
            }

            return raiz;
        }
        Coluna* achar_no_coluna(Coluna *raiz, I16 num_coluna){

            if (raiz == NULL) return NULL;

            if (num_coluna > raiz->numero){
                return achar_no_coluna(raiz->direita, num_coluna);
            } else if (num_coluna < raiz->numero){
                return achar_no_coluna(raiz->esquerda, num_coluna);
            }

            return raiz;
        }
        Linha* remover_linha(Linha* raiz, I16 num_linha) {
            if (raiz == NULL) return NULL;

            if (num_linha < raiz->numero) {
                raiz->esquerda = remover_linha(raiz->esquerda, num_linha);
            } else if (num_linha > raiz->numero) {
                raiz->direita = remover_linha(raiz->direita, num_linha);
            } else {
                if (raiz->esquerda == NULL) {
                    Linha *temp = raiz->direita;
                    free(raiz);
                    return temp;
                } else if (raiz->direita == NULL) {
                    Linha *temp = raiz->esquerda;
                    free(raiz);
                    return temp;
                }

                // so essa estrutura que muda de uma função pra outra
                Linha *pai = raiz;
                Linha *temp = raiz->direita;

                while (temp->esquerda != NULL) {
                    pai = temp;
                    temp = temp->esquerda;
                }

                raiz->numero = temp->numero;
                raiz->no_coluna = temp->no_coluna;

                if (pai->esquerda == temp){
                    pai->esquerda = temp->direita;
                } else {
                    pai->direita = temp->direita;
                }

                free(temp);
            }
            return raiz;
        }
        Coluna* remover_coluna(Coluna* raiz, I16 num_coluna) {
            if (raiz == NULL) return NULL;

            if (raiz->numero > num_coluna) {
                raiz->esquerda = remover_coluna(raiz->esquerda, num_coluna);
            } else if (raiz->numero < num_coluna) {
                raiz->direita = remover_coluna(raiz->direita, num_coluna);
            } else {
                if (raiz->esquerda == NULL) {
                    Coluna *temp = raiz->direita;
                    free(raiz);
                    return temp;
                } else if (raiz->direita == NULL) {
                    Coluna *temp = raiz->esquerda;
                    free(raiz);
                    return temp;
                }

                Coluna *pai = raiz;
                Coluna *temp = raiz->direita;
                
                while (temp->esquerda != NULL) {
                    pai = temp;
                    temp = temp->esquerda;
                }

                raiz->numero = temp->numero;
                raiz->voo = temp->voo;

                if (pai->esquerda == temp){
                    pai->esquerda = temp->direita;
                } else {
                    pai->direita = temp->direita;
                }

                free(temp);
            }
            return raiz;
        }


boolean armazenar(Raiz *matriz, I16 num_linha, I16 num_coluna, I16 voo){
    if (matriz == NULL) return false;

    if (voo != matriz->tipico){

        boolean linha_ja_existe = false;
        matriz->no_linha = criar_linha_com_coluna(matriz->no_linha, num_linha, num_coluna, voo, &linha_ja_existe);// se linha e coluna não existirem, e não é o voo tipico, é armazenamento
        if (linha_ja_existe == false) return true;

        Linha *linha_atual = achar_no_linha(matriz->no_linha, num_linha);
        
        boolean coluna_ja_existe = false;
        linha_atual->no_coluna = criar_coluna((Coluna *)linha_atual->no_coluna, num_coluna, voo, &coluna_ja_existe);// se linha e coluna não existirem, e não é o voo tipico, é armazenamento
        if (coluna_ja_existe == false) return true;

        Coluna *coluna_atual = achar_no_coluna((Coluna *)linha_atual->no_coluna, num_coluna);
        coluna_atual->voo = voo;// se linha e coluna existirem, e não é o voo tipico, é atualização

        return true;

    } else {

        Linha *linha_atual = achar_no_linha(matriz->no_linha, num_linha);
        if (linha_atual == NULL) return false;// se linha e coluna não existirem, e é o voo tipico, faz nada
        
        Coluna *coluna_atual = achar_no_coluna((Coluna *)linha_atual->no_coluna, num_coluna);
        if (coluna_atual == NULL) return false;// se linha e coluna não existirem, e é o voo tipico, faz nada
        
        linha_atual->no_coluna = remover_coluna(linha_atual->no_coluna, num_coluna);// se linha e coluna existirem, e é o voo tipico, é remoção (remove o nó da linha e coluna)
        if (linha_atual->no_coluna == NULL) matriz->no_linha = remover_linha(matriz->no_linha, num_linha);

        return true;
    }
}


I16 recuperar_voo(Raiz *matriz, I16 num_linha, I16 num_coluna) {
    if (matriz == NULL) return -1;

    Linha *linha_atual = achar_no_linha(matriz->no_linha, num_linha);
    if (linha_atual == NULL) return matriz->tipico;

    Coluna *coluna_atual = achar_no_coluna((Coluna *)linha_atual->no_coluna, num_coluna);
    if (coluna_atual == NULL) return matriz->tipico;

    return coluna_atual->voo;
}
        Coluna* buscar_coluna_por_voo(Coluna *raiz, I16 voo) {
            if (raiz == NULL) return NULL;
            
            if (raiz->voo == voo) return raiz;
            
            Coluna *achou_esq = buscar_coluna_por_voo(raiz->esquerda, voo);
            if (achou_esq != NULL) return achou_esq;
            return buscar_coluna_por_voo(raiz->direita, voo);
        }
        Linha* buscar_linha_por_voo(Linha *raiz, I16 voo, Coluna **coluna_destino) {
            if (raiz == NULL) return NULL;
            
            Coluna *col = buscar_coluna_por_voo(raiz->no_coluna, voo);
            if (col != NULL) {
                if (coluna_destino != NULL) *coluna_destino = col;
                return raiz;
            }
            
            Linha *achou_esq = buscar_linha_por_voo(raiz->esquerda, voo, coluna_destino);
            if (achou_esq != NULL) return achou_esq;
            return buscar_linha_por_voo(raiz->direita, voo, coluna_destino);
        }
I16 recuperar_origem(Raiz *matriz, I16 voo) {
    if (matriz == NULL) return 65535;

    Linha *linha = buscar_linha_por_voo(matriz->no_linha, voo, NULL);
    
    if (linha != NULL) return linha->numero;
    
    return 65535;
}
I16 recuperar_destino(Raiz *matriz, I16 voo) {
    if (matriz == NULL) return 65535;

    Coluna *coluna = NULL;

    buscar_linha_por_voo(matriz->no_linha, voo, &coluna);
    
    if (coluna != NULL) return coluna->numero;
    
    return 65535;
}
