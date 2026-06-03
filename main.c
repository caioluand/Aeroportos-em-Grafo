#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tad/meustipos.h"
#include "tad/listar.h"

I32 main () {
    I8 nome[50], sigla[4], sigla2[4], opcao_menu[10];
    I16 voo;
    boolean sair = false;

    IndiceAeroporto *vetor = criar_vetor(100);
    Raiz *matriz = nova_matriz(-1);
    hard_code(matriz, vetor);

    while (1) {

        printf("################################### Aeroportos em Grafos ###################################\n\n");

        printf("[1] Cadastrar novo aeroporto\n");
        printf("[2] Cadastrar novo voo\n");
        printf("[3] Remover aeroporto\n");
        printf("[4] Remover voo\n");
        printf("[5] Listar voos\n");
        printf("[6] Listar trajetos\n");
        printf("[0] Sair\n");

        printf("\n############################################################################################\n\n");

        fgets(opcao_menu, sizeof(opcao_menu), stdin);

        if (opcao_menu[1] == '\n') {
            switch (opcao_menu[0]) {
                case '1':
                    printf("Digite o nome do aeroporto (Ex. 'Guarulhos'): ");
                    scanf("%49[^\n]", nome);
                    printf("Digite a sigla do aeroporto (Ex. 'GRU'): ");
                    scanf("%3s", sigla);
                    getchar();
                    cadastrar_novo_aeroporto(vetor, nome, sigla);
                    break;
                case '2':
                    printf("Digite a sigla do aeroporto de origem (Ex. 'GRU'): ");
                    scanf("%3s", sigla);
                    printf("Digite a sigla do voo (Ex. '123'): ");
                    scanf("%hd", &voo);
                    printf("Digite a sigla do aeroporto de destino (Ex. 'GRU'): ");
                    scanf("%3s", sigla2);
                    getchar();

                    I16 orig = recuperar_indice(vetor, sigla);
                    I16 dest = recuperar_indice(vetor, sigla2);
                    
                    if (orig == -1 || dest == -1) {
                        printf("Erro: Aeroporto de origem ou destino nao encontrado!\n\n");
                    } else {
                        cadastrar_novo_voo(matriz, voo, orig, dest);
                    }
                    
                    break;
                case '3':
                    printf("Digite a sigla do aeroporto a ser removido (Ex. 'GRU'): ");
                    scanf("%3s", sigla);
                    getchar();
                    remover_aeroporto(matriz, vetor, sigla);
                    break;
                case '4':
                    printf("Digite a sigla do voo a ser removido (Ex. '123'): ");
                    scanf("%hd", &voo);
                    getchar();
                    remover_voo(matriz, voo);
                    break;
                case '5':
                    listar_voos(matriz, vetor);
                    break;
                case '6':
                    printf("Digite a sigla do voo de origem (Ex. 'GRU'): ");
                    scanf("%3s", sigla);
                    printf("Digite a sigla do voo de destino (Ex. 'SSA'): ");
                    scanf("%3s", sigla2);
                    getchar();
                    listar_trajetos(matriz, vetor, sigla, sigla2);
                    break;

                case '0':
                    printf("Saindo do programa...\n");
                    sair = true;
                    break;
                default:
                    printf("Opcao invalida. Por favor, selecione uma opcao valida.\n\n");
                    break;
            }

            if (sair) break;

        } else { // caso o usuário tenha digitado mais de um caractere
            printf("Entrada invalida. Por favor, selecione uma opcao valida.\n\n");
            if (strchr(opcao_menu, '\n') == NULL) {
                while(getchar() != '\n');
            }
            continue;
        }
    }

    free_tudo(matriz, vetor);
    return 0;
}