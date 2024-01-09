#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "untils.h"
#include "algoritno.h"


void imprime_matriz(int *grafo, int vert){
    printf("\n");
    for (int i = 0; i < vert; i++) {
        for (int j = 0; j < vert; j++) {
            printf("%3d ", grafo[i * vert + j]);
        }
        printf("\n");
    }
}


int main (){

    struct info EA_param;
    char nomeFich[30];

    pchrom pop = NULL, parentes = NULL;
    chrom melhor_round_atual, melhor_round_final;

    int geracao_atual, invalido = 0;
    int *grafo, *sol_Inic, *best_Sol, vert,arestas, custo=0, k,i;
    float MBF = 0;
    int op, nInteracoes, menorCusto = 0, n_int = 0;

    //escolha do ficheiro
    printf("Nome do ficheiro: ");
    gets(nomeFich);

    //obtencao dos dados do ficheiro
    grafo = lerDadosFich(nomeFich, &vert, &arestas, &k);

    //imprime_matriz(grafo, vert);

    // escolha do algoritmo
    printf("\n1 - Trepa colinas\n 2 - Evolotivo\n 3 - Hibrido\n ");
    scanf("%d",&op);

    //escolha do numero de interacoes
    printf("Numero de interacoes: ");
    scanf("%d",&nInteracoes);


    if (nInteracoes <= 0)
        return 0;

    sol_Inic = malloc(sizeof(int)*vert);
    if(!sol_Inic){
        printf("Erro na alocacao de memoria sol_Inc\n");
        return 0;
    }

    best_Sol = malloc(sizeof(int)*vert);
    if(!best_Sol){
        printf("Erro na alocacao de memoria best_Sol\n");
        return 0;
    }

    switch (op) {

        case 1:

            for (i = 0; i < nInteracoes; ++i) {

                gera_sol_inicial(sol_Inic, vert, k);

                escreve_sol(sol_Inic, vert, i + 1);

                custo = trepa_colinas(sol_Inic, grafo, vert, nInteracoes);

                escreve_sol(sol_Inic, vert, i + 1);

                printf("\nRepeticao %d com custo: %2d\n", i + 1, custo);

                if(custo < menorCusto || i == 0){

                    menorCusto = custo;

                    substitui(best_Sol,sol_Inic,vert);

                    n_int = i;

                }
                MBF += custo;

            }

            printf("\n ----------Trepa Colinas--------- \n");
            printf("A melhor solucao foi:");
            escreve_sol(best_Sol,vert,n_int);
            printf("Com custo = %d", menorCusto);
            printf("\nMFB = %.4f", MBF/i);

            break;

        case 2:      // evolutivo

            EA_param = init_dataEvul(vert);

            for (i = 0; i < nInteracoes; ++i) {


                pop = init_pop(EA_param, k); //gerar a populacao inicial

                evaluate(pop, EA_param, grafo, k); //avaliar popilacao

                melhor_round_atual = pop[0];

                melhor_round_atual = getBest(pop,EA_param,melhor_round_atual);

                parentes = malloc(sizeof(chrom)*EA_param.popsize);

                if (parentes==NULL)
                {
                    printf("Erro na alocacao de memoria\n");
                    exit(1);
                }

                geracao_atual = 1;

                while (geracao_atual <= EA_param.numGenerations) {

                  /*  printf("\n Antes do torneio: ");
                    for (int i = 0; i < EA_param.numGenes; ++i) {
                        for (int j = 0; j < EA_param.numGenes; ++j) {
                            printf("%d", pop[i].p[j]);
                        }
                        printf("\n");
                    }*/
                    tournament(pop, EA_param, parentes);

                /*printf("\n Depois do torneio: ");
                    for (int i = 0; i < EA_param.numGenes; ++i) {
                        for (int j = 0; j < EA_param.numGenes; ++j) {
                            printf("%d", pop[i].p[j]);
                        }
                        printf("\n");
                    } */
                  genetic_operators(parentes, EA_param, pop);

                    /*printf("\n Depois do operador: ");
                    for (int i = 0; i < EA_param.numGenes; ++i) {
                        for (int j = 0; j < EA_param.numGenes; ++j) {
                            printf("%d", pop[i].p[j]);
                        }
                        printf("\n");
                    }*/

                    evaluate(pop, EA_param, grafo, k);

                    melhor_round_atual = getBest(pop, EA_param,  melhor_round_atual);


                    geracao_atual++;

                }

                printf("\nRepeticao %d:", i + 1);
                escreve_Best_evul(melhor_round_atual, EA_param);

                if (i==0 ||melhor_round_atual.fitness < melhor_round_final.fitness)
                    melhor_round_final = melhor_round_atual;

                free(pop);
                free(parentes);
            }

            printf("\nMelhor solucao encontrada");
            escreve_Best_evul(melhor_round_final, EA_param);


            break;
        case 3:
            // hibrido
            break;
        default:
            printf("Essa opcao nao existe\n Escolha entre 1-2-3 por favor\n");
            break;
    }

    free(grafo);
}