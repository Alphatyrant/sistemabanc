/**
 * @file opcoes.h
 * @author rafael (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-10-15
 *
 * @copyright Copyright (c) 2021
 *
 **/
#include <stdio.h>
#define QTD_CONTA 10

int menuop();
int menuconta();
int procuraconta();
void salvar();


typedef struct Conta {
    char titular[50];
    char cpf[12];
    float saldo;
    int posicao;
} Conta;


typedef struct ListaContas {
    Conta contas[QTD_CONTA];
    int tamanho;
} ListaContas;
ListaContas pegarsalvos(ListaContas lista);

ListaContas *d;