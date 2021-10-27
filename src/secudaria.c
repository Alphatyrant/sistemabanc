/**
 * @file secudaria.c
 * @author rafael (you@domain.com)
 * @brief
 * @version hollow
 * @date 2021-10-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/foo/opcoes.h"
#define QTD_CONTA 10
#define SEEK_SET 0

int menuconta() {
    int opcao2;

    printf(
        "\n\nEscolha a opção desejada:\n"
        "[1] Extrato\n"
        "[2] Deposito\n"
        "[3] Saque\n"
        "[0] Voltar ao menu\n"
        "\nOpção: ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao2);
    return opcao2;
}

int menuop() {
    int opcao;
    opcao = 0;

    printf(
        "\n\nBem vindo\n"
        "[1] Criar\n"
        "[2] Excluir\n"
        "[3] Acessar\n"
        "[0] Sair\n"
        "\n Opção: ");

    setbuf(stdin, NULL);
    scanf("%d", &opcao);
    return opcao;
}

ListaContas criaconta(ListaContas lista) {
    size_t len;
    char buffer[128];
    int i, verificacao = 1;

    printf("\n digite o cpf: ");
    setbuf(stdin, NULL);
    scanf("%127s", buffer);
    len = sizeof(lista.contas[lista.tamanho].cpf);
    snprintf(lista.contas[lista.tamanho].cpf, len, "%s", buffer);
    memset(buffer, 0, sizeof(buffer));

    if (len != 12) {
        setbuf(stdin, NULL);
        scanf("%127s", buffer);
        snprintf(lista.contas[lista.tamanho].cpf, len, "%s", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    for (i = 0; i < lista.tamanho; i++) {
        if (strcmp(lista.contas[i].cpf, lista.contas[lista.tamanho].cpf) == 0) verificacao = 0;
    }
    if (verificacao == 1) {  // se nao existir
        len = sizeof(lista.contas[lista.tamanho].titular);
        printf("\n digite o nome: ");
        setbuf(stdin, NULL);
        scanf("%127s", buffer);
        snprintf(lista.contas[lista.tamanho].titular, len, "%s", buffer);
        memset(buffer, 0, sizeof(buffer));

        lista.contas[lista.tamanho].saldo = 0;
        lista.contas[i].posicao = lista.tamanho;
        printf(" o tamanho da lista está %d", lista.tamanho);
        printf(" a posicao é %d", lista.contas->posicao);
    } else {
        printf("\n existe uma conta com esse cpf");
    }
    lista.tamanho++;
    return lista;
}

ListaContas exclui(ListaContas lista) {
    int posicaoConta;  // aux para percorrer a lista

    posicaoConta = procuraconta(lista);
    if (posicaoConta != -1) {
        int j;
        for (j = posicaoConta; j < lista.tamanho; j++) {
            lista.contas[j] = lista.contas[j + 1];
            lista.contas[j].posicao--;
        }

        lista.tamanho--;
        printf("\n conta deletada");
    } else {
        printf("\n nao há o cpf informado");
    }
    return lista;
}

int procuraconta(ListaContas lista) {
    char cpf[20];

    int i, posicaoConta = -1;  // setado para -1 por padrao na posicaoConta

    printf("\nInforme o nome da conta que deseja: ");
    scanf("%18s", cpf);
    printf("o  numero da conta   é %s \n", cpf);

    for (i = 0; i < lista.tamanho; i++) {
        if (strncmp(lista.contas[i].cpf, cpf, 3) == 0) {
            printf("lis-----%s\n", lista.contas[i].cpf);
            printf("lis-----%s\n", cpf);
            posicaoConta = lista.contas[i].posicao;
        }
    }
    printf(" a posicao da conta é\n %d", posicaoConta);

    return posicaoConta;
}

void extrato(Conta conta) { printf("\nO money é:%.2f", conta.saldo); }

Conta saque(Conta conta) {
    float valor;
    printf("\n digite o valor a ser sacado: ");
    setbuf(stdin, NULL);
    scanf("%f", &valor);
    if (conta.saldo - valor >= 0) {
        conta.saldo -= valor;
        printf("\n saque efetuado no valor de %f ", valor);
    } else {
        printf("\n sem saldo");
    }

    return conta;
}

Conta deposito(Conta conta) {
    float valor;
    printf("\nInforme a quantidade em reais que deseja depoistar na conta: ");
    setbuf(stdin, NULL);
    scanf("%f", &valor);
    if (valor > 0)
        conta.saldo += valor;
    else
        printf("\n nao da pra colocar um valor menor que 0");

    return conta;
}

void salvar(ListaContas lista) {
    FILE *salvar;
    int i;
    i = 0;
    salvar = fopen("conta.txt", "w");
    fseek(salvar, 0, SEEK_SET);
    for (&lista.contas[i] == 0; i < lista.tamanho; i++) {
        fprintf(salvar, "%d\n", lista.contas[i].posicao);
        fprintf(salvar, "%s\n", lista.contas[i].cpf);
        fprintf(salvar, "%s\n", lista.contas[i].titular);
        fprintf(salvar, "%f\n", lista.contas[i].saldo);
    }
    lista.contas->posicao++;
    printf("\n arquivo salvo com os dados \n");
    fclose(salvar);
}

ListaContas pegarsalvos(ListaContas lista) {
    int ret;
    int i = 0;
    FILE *salvar;

    salvar = fopen("conta.txt", "r");

    fseek(salvar, 0, SEEK_SET);

    do {
        ret = 0;
        ret = fscanf(salvar, "%d\n", &lista.contas[i].posicao);
        if (ret == EOF) {
            printf(" chegou ao fim do arquivo -1 \n");
            break;
        }
        ret = fscanf(salvar, "%12s\n", (char *)&lista.contas[i].cpf);

        if (ret == EOF) {
            printf("  chegou ao fim do arquivo -2 \n");
            break;
        }
        ret = fscanf(salvar, "%20s\n", (char *)&lista.contas[i].titular);

        if (ret == EOF) {
            printf("  chegou ao fim do arquivo -3 \n");
            break;
        }
        ret = fscanf(salvar, "%f\n", &lista.contas[i].saldo);

        if (ret == EOF) {
            printf("  chegou ao fim do arquivo -4\n");
        }
        i++;
    } while (ret != EOF);

    if (i >= 1) {
        lista.tamanho = i;
    }

    fclose(salvar);
    return lista;
}
