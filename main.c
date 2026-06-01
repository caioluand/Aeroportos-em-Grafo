#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tad/matriz.h"
#include "tad/meustipos.h"

I32 main () {
    I8 nome [50];
    I8 sigla [3];
    I8 opcao_menu [10];
    boolean sair = false;

    while (1) {
        printf("###### Aeroportos em Grafos ######\n\n");

        printf("[1] Cadastrar novo aeroporto\n");
        printf("[2] Cadastrar novo voo\n");
        printf("[3] Remover aeroporto\n");
        printf("[4] Remover voo\n");
        printf("[5] Listar aeroportos\n");
        printf("[6] Listar voos\n");
        printf("[7] Listar trajetos\n");
        printf("[0] Sair\n");

        printf("\n################################\n\n");

        fgets(opcao_menu, sizeof(opcao_menu), stdin);

        if (opcao_menu[1] == '\n') {
            switch (opcao_menu[0]) {
                case '1':
                    printf("Digite o nome do aeroporto e sua sigla (Ex. 'Guarulhos GRU'): ");
                    scanf("%s", nome);
                    getchar();
                    // funcao
                    break;
                case '2':
                    printf("Digite a sigla do voo (Ex. '123'): ");
                    scanf("%s", sigla);
                    getchar();
                    // funcao
                    break;
                case '3':
                    printf("Digite a sigla do aeroporto a ser removido (Ex. 'GRU'): ");
                    scanf("%s", sigla);
                    getchar();
                    // funcao
                    break;
                case '4':
                    printf("Digite a sigla do voo a ser removido (Ex. '123'): ");
                    scanf("%s", sigla);
                    getchar();
                    // funcao
                    break;
                case '5':
                    printf("");
                    getchar();
                    // funcao
                    break;
                case '6':
                    printf("");
                    getchar();
                    // funcao
                    break;
                case '7':
                    printf("Digite a sigla do voo de origem (Ex. 'GRU'): ");
                    scanf("%s", sigla);
                    printf("Digite a sigla do voo de destino (Ex. 'SSA'): ");
                    scanf("%s", nome);
                    getchar();
                    // funcao
                    break;

                case '0':
                    printf("Saindo do programa...\n");
                    sair = true;
                    break;
                default:
                    printf("Opcao invalida. Por favor, selecione uma opcao valida.\n\n");
                    break;
            }

            if (sair) {
                break;

            } else { // caso o usuário tenha digitado um caractere inválido
                printf("Opcao invalida. Por favor, selecione uma opcao valida.\n\n");
            }
        } else { // caso o usuário tenha digitado mais de um caractere
            printf("Entrada invalida. Por favor, selecione uma opcao valida.\n\n");
            if (strchr(opcao_menu, '\n') == NULL) {
                while(getchar() != '\n');
            }
            continue;
        }
    }

    return 0;
}