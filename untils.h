//
// Created by Utilizador on 02/12/2023.
//

#ifndef TP_IIA2_UNTILS_H
#define TP_IIA2_UNTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define  MAX_OBJ 1000

struct info
{
    // Tamanho da popula��o
    int     popsize;
    // Probabilidade de muta��o
    float   pm;
    // Probabilidade de recombina��o
    float   pr;
    // Tamanho do torneio para sele��o do pai da pr�xima gera��o
    int     tsize;
    // Constante para avalia��o com penaliza��o
    float   ro;
    // N�mero de objetos que se podem colocar na mochila
    int     numGenes;
    // Capacidade da mochila
    int     capacity;
    // N�mero de gera��es
    int     numGenerations;
};


typedef struct individual chrom, *pchrom;

struct individual
{

    int     p[MAX_OBJ];
    // Valor da qualidade da solucao
    int  fitness;
    // 1 para valido/ 0 para invalido
    int     valido;
};


int* lerDadosFich(char *nomeFich, int *vert, int *a, int *k);
int random_l_h(int min, int max);
float rand_01();
void init_rand();
void gera_sol_inicial(int *sol, int v ,int k);
void escreve_sol(int *sol, int vert, int i);
int solucao_valida(int sol[], int *mat, int vert);


int calcula_fit(int a[], int *mat, int vert);

void evaluate(pchrom pop, struct info d, int *mat, int k);
pchrom init_pop(struct info d, int k);
chrom getBest(pchrom pop, struct info d, chrom best);
void escreve_Best_evul(chrom x, struct info d);

int eval_rep(int sol[], struct info d, int *mat, int *v, int k);

        struct info init_dataEvul(int a);
#endif //TP_IIA2_UNTILS_H
