/**
 * @file projeto1.c
 * @author rafael (you@domain.com)
 * @brief
 * @version hollow
 * @date 2021-10-06
 *
 * @copyright Copyright (c) 2021
 *
 */

// 01 ) Criar um programa bancário em C capaz de depositar / sacar dinheiro na conta pessoal,
// o programa não deve permitir saques de dinheiro que não existe, assim como depósitos de dinheiro negativo.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/foo/opcoes.h"

// menus
int imprimeMenuOperacao();
int imprimeMenuConta();
int procuraconta(ListaContas lista);

// ops
ListaContas criaconta(ListaContas lista);
ListaContas exclui(ListaContas lista);
ListaContas pegarsalvos(ListaContas lista);
void extrato(Conta conta);

Conta deposito(Conta conta);
Conta saque(Conta conta);

int main() {
    ListaContas lista;

    lista.tamanho = 0;
    int opcao, opcao2 = 0;
    int posicaoConta = 0;
    int i = 0;
    lista = pegarsalvos(lista);
    posicaoConta = lista.tamanho;

    do {
        opcao = menuop();
        switch (opcao) {
            case 1:
                if (lista.tamanho <= QTD_CONTA) {
                    lista = criaconta(lista);
                    printf("Lista nome: %s \n", lista.contas->cpf);
                    printf("Lista tamanho: %d \n", lista.tamanho);
                } else {
                    printf("lista está cheia nao dá mais \n");
                }
                break;

            case 2:
                if (lista.tamanho != 0)
                    lista = exclui(lista);
                else
                    printf("\n nao existe nenhuma conta criada no momento");
                break;

            case 3:
                if (lista.tamanho != 0) {
                    posicaoConta = procuraconta(lista);
                    if (posicaoConta != -1)
                        opcao2 = menuconta();
                    else
                        printf("\n nao existe nenhuma conta para o cpf informado");
                } else {
                    printf("\n nao existe nenhuma conta criada no momento");
                }
                break;

            default:
                salvar(lista);
                printf("\n fechando o programa");
                break;
        }

        if (opcao2 != 0) {
            do {
                switch (opcao2) {
                    case 1:
                        extrato(lista.contas[posicaoConta]);
                        break;
                    case 2:
                        lista.contas[posicaoConta] = deposito(lista.contas[posicaoConta]);
                        break;

                    case 3:
                        lista.contas[posicaoConta] = saque(lista.contas[posicaoConta]);
                        break;

                    default:
                        break;
                }

                opcao2 = menuconta();
            } while (opcao2 != 0);
        }
    } while (opcao != 0);  // loopzinho

    return 0;
}
