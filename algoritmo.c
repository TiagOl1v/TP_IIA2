#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritno.h"



int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
    int *nova_sol, custo = 10000, custo_viz = 0, i;

    nova_sol = malloc(sizeof(int)*vert);

    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
// Avalia solucao inicial

    custo = calcula_fit(sol, mat, vert);

    if(solucao_valida(sol,mat,vert) == 0)
        custo *= 100;


    for(i=0; i < num_iter; i++)
    {
// Gera vizinho

        gera_vizinho(sol, nova_sol, vert);

        custo_viz = calcula_fit(nova_sol, mat, vert);

       if(solucao_valida(nova_sol,mat,vert) == 0)
           custo_viz *= 100;


        // Aceita vizinho se o custo diminuir
        if(custo_viz < custo && custo_viz !=0 )
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
    }


    free(nova_sol);
    return custo;
}

void gera_vizinho(int a[], int b[], int n){
    int i, p1, p2;

    for(i = 0; i < n; i++)
        b[i] = a[i];
// Encontra posicao com valor 0
    do
        p1=random_l_h(0, n-1);
    while(b[p1] != 0);
// Encontra posicao com valor 0
    do
        p2=random_l_h(0, n-1);

    while(b[p2] != 1);
// Troca
       b[p1] = 1;
         b[p2] = 0;
}

void substitui(int a[], int b[], int n){
    int i;
    for (i = 0; i < n; i++)
        a[i] = b[i];
}


void tournament(pchrom pop, struct info d, pchrom parents)
{
    int i, x1, x2;

    // Realiza popsize torneios
    for (i=0; i<d.popsize;i++)
    {
        x1 = random_l_h(0, d.popsize-1);
        do
            x2 = random_l_h(0, d.popsize-1);
        while (x1==x2);
        if (pop[x1].fitness < pop[x2].fitness)
            parents[i] = pop[x1];
        else
            parents[i] = pop[x2];
    }
}


void crossover(pchrom parents, struct info d, pchrom offspring)
{
    int i, j, point;

    for (i=0; i<d.popsize; i+=2)
    {
        if (rand_01() < d.pr)
        {
            point = random_l_h(0, d.numGenes-1);
            for (j=0; j<point; j++)
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i+1].p[j] = parents[i+1].p[j];
            }
            for (j=point; j<d.numGenes; j++)
            {
                offspring[i].p[j]= parents[i+1].p[j];
                offspring[i+1].p[j] = parents[i].p[j];
            }
        }
        else
        {
            offspring[i] = parents[i];
            offspring[i+1] = parents[i+1];
        }
    }
}

void mutacao_por_troca(pchrom offspring, struct info d)
{
    int pos1, pos2, aux;

    for (int i=0; i<d.popsize; i++)
        if (rand_01() < d.pm)
        {
            do
                pos1 = random_l_h(0, d.numGenes-1);
            while (offspring[i].p[pos1] == 1);
            do
                pos2 = random_l_h(0, d.numGenes-1);
            while (offspring[i].p[pos2] == 0);
            aux = offspring[i].p[pos1];
            offspring[i].p[pos1] = offspring[i].p[pos2];
            offspring[i].p[pos2] = aux;
        }
}

void genetic_operators(pchrom parents, struct info d, pchrom offspring)
{
     crossover(parents, d, offspring);
    mutacao_por_troca(offspring, d);
}