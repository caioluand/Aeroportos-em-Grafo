#include <stdio.h>
#include "matriz.h"
#include "meustipos.h"

boolean nova_matriz(Raiz *matriz, I8 t) {
    matriz->tipico = t;
    matriz->no_linha = NULL;
    return true;
}

boolean free_matriz(Raiz *matriz) {
    if (matriz == NULL || matriz->no_linha==NULL) return false;

    free_arvore_linhas(matriz->no_linha);

    matriz->no_linha = NULL;

    return true;
}
        void free_arvore_colunas(Coluna *col) {
            if (col == NULL) return;

            free_arvore_colunas(col->esquerda);
            free_arvore_colunas(col->direita);

            free(col->valor); 

            free(col);
        }
        void free_arvore_linhas(Linha *lin) {
            if (lin == NULL) return;

            free_arvore_linhas(lin->esquerda);
            free_arvore_linhas(lin->direita);

            free_arvore_colunas(lin->no_coluna);

            free(lin);
        }

boolean armazenar(Raiz *matriz, U16 num_linha, U16 num_coluna, valor valor){
    if (matriz == NULL) return false;

    Linha *linha_atual = (Linha *)matriz->no_linha;

    if (valor != matriz->tipico){

        boolean linha_ja_existe = false;
        linha_atual = criar_linha_com_coluna(linha_atual, num_linha, num_coluna, valor, &linha_ja_existe);// se linha e coluna não existirem, e não é o valor tipico, é armazenamento
        if (linha_ja_existe == false) return true;

        Coluna *coluna_atual = (Coluna *)linha_atual->no_coluna;

        boolean coluna_ja_existe = false;
        coluna_atual = criar_coluna(coluna_atual, num_coluna, valor, &coluna_ja_existe);// se linha e coluna não existirem, e não é o valor tipico, é armazenamento
        if (coluna_ja_existe == false) return true;

        coluna_atual->valor = valor;// se linha e coluna existirem, e não é o valor tipico, é atualização
        

    } else {

        linha_atual = achar_no_linha(linha_atual, num_linha);

        if (linha_atual == NULL) return false;// se linha e coluna não existirem, e é o valor tipico, faz nada

        
        linha_atual->no_coluna = remover_coluna(linha_atual->no_coluna, num_coluna);// se linha e coluna existirem, e é o valor tipico, é remoção (remove o nó da linha e coluna)
        if (linha_atual->no_coluna == NULL) matriz->no_linha = remover_linha(matriz->no_linha, num_linha);

        return true;
    }
}
        Coluna* remover_coluna(Coluna* raiz, U16 num_coluna) {
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
                raiz->valor = temp->valor;

                if (pai->esquerda == temp){
                    pai->esquerda = temp->direita;
                } else {
                    pai->direita = temp->direita;
                }

                free(temp);
            }
            return raiz;
        }
        Linha* remover_linha(Linha* raiz, U16 num_linha) {
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
        Linha* achar_no_linha(Linha *raiz, U16 num_linha){

            if (raiz == NULL) return NULL;

            if (num_linha > raiz->numero){
                return achar_no_linha(raiz->direita, num_linha);
            } else if (num_linha < raiz->numero){
                return achar_no_linha(raiz->esquerda, num_linha);
            }

            return raiz;
        }
        Linha* criar_linha_com_coluna(Linha *raiz, U16 num_linha, U16 num_coluna, valor valor, boolean *linha_ja_existe){
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
                coluna_nova->valor = valor;
                coluna_nova->esquerda = NULL;
                coluna_nova->direita = NULL;

                return linha_nova;
            }

            if (num_linha < raiz->numero) {
                raiz->esquerda = criar_linha_com_coluna(raiz->esquerda, num_linha, num_coluna, valor, linha_ja_existe);
            } else if (num_linha > raiz->numero) {
                raiz->direita = criar_linha_com_coluna(raiz->direita, num_linha, num_coluna, valor, linha_ja_existe);
            } else {
                *linha_ja_existe = true;
            }

            return raiz;
        }
        Coluna* criar_coluna(Coluna *raiz, U16 num_coluna, valor valor, boolean *coluna_ja_existe){
            if (raiz == NULL) {
                Coluna *coluna_nova = (Coluna *)malloc(sizeof(Coluna));
                if (coluna_nova == NULL) return NULL;

                coluna_nova->numero = num_coluna;
                coluna_nova->valor = valor;
                coluna_nova->esquerda = NULL;
                coluna_nova->direita = NULL;

                return coluna_nova;
            }

            if (num_coluna < raiz->numero) {
                raiz->esquerda = criar_coluna(raiz->esquerda, num_coluna, valor, coluna_ja_existe);
            } else if (num_coluna > raiz->numero) {
                raiz->direita = criar_coluna(raiz->direita, num_coluna, valor, coluna_ja_existe);
            } else {
                *coluna_ja_existe = true;
            }

            return raiz;
        }













/*
boolean armazenar(Raiz *matriz, U16 num_linha, U16 num_coluna, valor valor_novo){
    if (matriz == NULL) return false;

    if (valor_novo != matriz->tipico){
        boolean linha_ja_existe = false;
        
        // CORREÇÃO: Atualiza a raiz de linhas da matriz diretamente
        matriz->no_linha = criar_linha_com_coluna(matriz->no_linha, num_linha, num_coluna, valor_novo, &linha_ja_existe);
        if (matriz->no_linha == NULL) return false; // Falha de memória
        
        // Se a linha foi criada agora, a coluna interna também já foi criada. Pronto.
        if (linha_ja_existe == false) return true;

        // Se caiu aqui, a linha já existia. Precisamos buscar esse nó da linha para mexer nas colunas.
        Linha *linha_atual = achar_no_linha(matriz->no_linha, num_linha);
        
        boolean coluna_ja_existe = false;
        linha_atual->no_coluna = criar_coluna(linha_atual->no_coluna, num_coluna, valor_novo, &coluna_ja_existe);
        
        // Se a coluna não existia e foi criada, pronto.
        if (coluna_ja_existe == false) return true;

        // Se a linha E a coluna já existiam, é uma ATUALIZAÇÃO de valor
        // Precisamos buscar a coluna para atualizar o valor dela
        Coluna *coluna_atual = linha_atual->no_coluna;
        while (coluna_atual != NULL && coluna_atual->numero != num_coluna) {
            if (num_coluna < coluna_atual->numero) coluna_atual = coluna_atual->esquerda;
            else coluna_atual = coluna_atual->direita;
        }
        if (coluna_atual != NULL) {
            coluna_atual->valor = valor_novo;
        }
        
        return true;

    } else { // Caso de REMOÇÃO (valor == típico)
        Linha *linha_alvo = achar_no_linha(matriz->no_linha, num_linha);

        if (linha_alvo == NULL) return false; 

        linha_alvo->no_coluna = remover_coluna(linha_alvo->no_coluna, num_coluna);
        
        if (linha_alvo->no_coluna == NULL) {
            matriz->no_linha = remover_linha(matriz->no_linha, num_linha);
        }

        return true;
    }
}
*/