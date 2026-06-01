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
    boolean achou_linha = true;

    if (valor != matriz->tipico){// se linha e coluna existirem, e não é o valor tipico, é atualização
        boolean achou_coluna = true;


        if (matriz->no_linha == NULL) {
            Linha *linha_nova = (Linha *)malloc(sizeof(Linha));
            if (linha_nova == NULL) return false;

            Coluna *coluna_nova = (Coluna *)malloc(sizeof(Coluna));
            if (coluna_nova == NULL) return false;

            linha_nova->numero = num_linha;
            linha_nova->no_coluna = coluna_nova;
            linha_nova->esquerda = NULL;
            linha_nova->direita = NULL;

            matriz->no_linha = linha_nova;

            coluna_nova->numero = num_coluna;
            coluna_nova->valor = valor;
            coluna_nova->esquerda = NULL;
            coluna_nova->direita = NULL;

            achou_linha = false;

            return true;// se linha e coluna não existirem, e não é o valor tipico, é armazenamento
        }


        while (linha_atual->numero != num_linha){

            if (linha_atual->numero < num_linha) {
                if (linha_atual->direita != NULL) {
                    linha_atual = linha_atual->direita;
                } else {
                    Linha *linha_nova = (Linha *)malloc(sizeof(Linha));
                    if (linha_nova == NULL) return false;

                    Coluna *coluna_nova = (Coluna *)malloc(sizeof(Coluna));
                    if (coluna_nova == NULL) return false;

                    linha_nova->numero = num_linha;
                    linha_nova->no_coluna = coluna_nova;
                    linha_nova->esquerda = NULL;
                    linha_nova->direita = NULL;

                    linha_atual->direita = linha_nova;

                    coluna_nova->numero = num_coluna;
                    coluna_nova->valor = valor;
                    coluna_nova->esquerda = NULL;
                    coluna_nova->direita = NULL;

                    achou_linha = false;

                    return true;// se linha e coluna não existirem, e não é o valor tipico, é armazenamento
                }
            }
            if (linha_atual->numero > num_linha) {
                if (linha_atual->esquerda != NULL) {
                    linha_atual = linha_atual->esquerda;
                } else {
                    Linha *linha_nova = (Linha *)malloc(sizeof(Linha));
                    if (linha_nova == NULL) return false;

                    Coluna *coluna_nova = (Coluna *)malloc(sizeof(Coluna));
                    if (coluna_nova == NULL) return false;

                    linha_nova->numero = num_linha;
                    linha_nova->no_coluna = coluna_nova;
                    linha_nova->esquerda = NULL;
                    linha_nova->direita = NULL;

                    linha_atual->esquerda = linha_nova;

                    coluna_nova->numero = num_coluna;
                    coluna_nova->valor = valor;
                    coluna_nova->esquerda = NULL;
                    coluna_nova->direita = NULL;

                    achou_linha = false;
                
                    return true;// se linha e coluna não existirem, e não é o valor tipico, é armazenamento
                }
            }

        }

        if (achou_linha == true) {
            Coluna *coluna_atual = (Coluna *)linha_atual->no_coluna;

            while (coluna_atual->numero != num_coluna){

                if (coluna_atual->numero < num_coluna) {
                    if (coluna_atual->direita != NULL) {
                        coluna_atual = coluna_atual->direita;
                    } else {
                        Coluna *coluna_nova = (Coluna *)malloc(sizeof(Coluna));
                        if (coluna_nova == NULL) return false;

                        coluna_nova->numero = num_coluna;
                        coluna_nova->valor = valor;
                        coluna_nova->esquerda = NULL;
                        coluna_nova->direita = NULL;

                        coluna_atual->direita = coluna_nova;

                        achou_coluna = false;

                        return true;// se linha e coluna não existirem, e não é o valor tipico, é armazenamento
                    }
                }
                if (coluna_atual->numero > num_coluna) {
                    if (coluna_atual->esquerda != NULL) {
                        coluna_atual = coluna_atual->esquerda;
                    } else {
                        Coluna *coluna_nova = (Coluna *)malloc(sizeof(Coluna));
                        if (coluna_nova == NULL) return false;

                        coluna_nova->numero = num_coluna;
                        coluna_nova->valor = valor;
                        coluna_nova->esquerda = NULL;
                        coluna_nova->direita = NULL;

                        coluna_atual->esquerda = coluna_nova;

                        achou_coluna = false;

                        return true;// se linha e coluna não existirem, e não é o valor tipico, é armazenamento
                    }
                }

            }

            if (achou_coluna == true) coluna_atual->valor = valor;
        }


    } else {// se linha e coluna existirem, e é o valor tipico, é remoção (remove o nó da linha e coluna)]
        
        //boolean removeu_coluna = false;

        while (linha_atual->numero != num_linha) {
            if (linha_atual->numero < num_linha) {
                if (linha_atual->direita != NULL) {
                    linha_atual = linha_atual->direita;
                } else {
                    achou_linha = false;
                    return false;// se linha e coluna não existirem, e é o valor tipico, faz nada
                }
            }
            if (linha_atual->numero > num_linha) {
                if (linha_atual->esquerda != NULL) {
                    linha_atual = linha_atual->esquerda;
                } else {
                    achou_linha = false;
                    return false;// se linha e coluna não existirem, e é o valor tipico, faz nada
                }
            }
        }
        
        if (achou_linha == true) {
            Coluna *coluna_atual = (Coluna *)linha_atual->no_coluna;

            while (coluna_atual->numero != num_coluna){
                if (coluna_atual->numero < num_coluna) {
                    if (coluna_atual->direita != NULL) {
                        coluna_atual = coluna_atual->direita;
                    } else {
                        return false;// se linha e coluna não existirem, e é o valor tipico, faz nada
                    }
                }
                if (coluna_atual->numero > num_coluna) {
                    if (coluna_atual->esquerda != NULL) {
                        coluna_atual = coluna_atual->esquerda;
                    } else {
                        return false;// se linha e coluna não existirem, e é o valor tipico, faz nada
                    }
                }
            }
        }
        /*
        if (achou_linha == true) {
            // 2. Remove a coluna usando recursão
            linha_atual->no_coluna = remover_coluna_bst(linha_atual->no_coluna, num_coluna, &removeu_coluna);
            
            // 3. Se a linha ficou completamente sem colunas, removemos a linha
            if (linha_atual->no_coluna == NULL) {
                matriz->no_linha = remover_linha_bst(matriz->no_linha, num_linha);
            }
        }
        return removeu_coluna;
        */
        return true;
    }
}
        Coluna* remover_coluna_bst(Coluna* raiz, U16 num_coluna, boolean *sucesso) {
            if (raiz == NULL) return NULL;

            // Busca o nó a ser removido
            if (num_coluna < raiz->numero) {
                raiz->esquerda = remover_coluna_bst(raiz->esquerda, num_coluna, sucesso);
            } else if (num_coluna > raiz->numero) {
                raiz->direita = remover_coluna_bst(raiz->direita, num_coluna, sucesso);
            } else {
                // Encontrou o nó
                *sucesso = true;

                // Caso 1 e 2: Sem filhos ou apenas um filho
                if (raiz->esquerda == NULL) {
                    Coluna *temp = raiz->direita;
                    free(raiz);
                    return temp;
                } else if (raiz->direita == NULL) {
                    Coluna *temp = raiz->esquerda;
                    free(raiz);
                    return temp;
                }

                // Caso 3: Dois filhos (Busca o menor valor da subárvore direita)
                Coluna *temp = raiz->direita;
                while (temp->esquerda != NULL) temp = temp->esquerda;

                // Copia os dados do sucessor
                raiz->numero = temp->numero;
                raiz->valor = temp->valor;

                // Remove o sucessor
                raiz->direita = remover_coluna_bst(raiz->direita, temp->numero, sucesso);
            }
            return raiz;
        }
        Linha* remover_linha_bst(Linha* raiz, U16 num_linha) {
            if (raiz == NULL) return NULL;

            if (num_linha < raiz->numero) {
                raiz->esquerda = remover_linha_bst(raiz->esquerda, num_linha);
            } else if (num_linha > raiz->numero) {
                raiz->direita = remover_linha_bst(raiz->direita, num_linha);
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

                Linha *temp = raiz->direita;
                while (temp->esquerda != NULL) temp = temp->esquerda;

                raiz->numero = temp->numero;
                raiz->no_coluna = temp->no_coluna;
                raiz->direita = remover_linha_bst(raiz->direita, temp->numero);
            }
            return raiz;
        }