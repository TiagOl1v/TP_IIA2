//
// Created by Utilizador on 02/12/2023.
//

#include "untils.h"




int solucao_valida(int sol[], int *mat, int v) {

    for (int i = 0; i < v; i++) {
        if (sol[i] == 1) {
            int valida = 0;
            for (int j = 0; j < v; j++) {
                if (sol[j] == 1 && *(mat + i * v + j) != 0) {
                    valida = 1;
                    break;
                }
            }
            if (!valida) {
                return 0;
            }
        }
    }
    return 1;
}

int pos_inv(int sol[], int *mat, int v) {

    for (int i = 0; i < v; i++) {
        if (sol[i] == 1) {
            int valida = 0;
            for (int j = 0; j < v; j++) {
                if (sol[j] == 1 && *(mat + i * v + j) != 0) {
                    valida = 1;
                    break;
                }
            }
            if (!valida) {
                return i;
            }
        }
    }
    return 1;
}

int calcula_fit(int a[], int *mat, int vert){
    int total = 0;

    for (int i = 0; i < vert; i++) {
        if (a[i] == 1) {
            for (int j = i; j < vert; j++) {
                if (a[j] == 1) {
                    total += *(mat + i * vert + j); // Adiciona o custo da conexão
                }
            }
        }
    }

    return total;
}



int* lerDadosFich(char *nomeFich, int *vert, int *a, int *k){

    FILE *ficheiro;
    int linhas, colunas;
    int *m = NULL;
    int custo;
    int numV, numA;
    char aux[10];

    ficheiro = fopen(nomeFich, "r");

    if(!ficheiro){
        printf("Erro ao abrir ficheiro\n");
        exit(1);
    }

    fscanf(ficheiro, "k %d", k);

    fscanf(ficheiro, "%*s %*s"); //nao ler o "p edge"

    fscanf(ficheiro, "%d %d", vert, a);

    m = malloc(sizeof(int)*(*vert)*(*vert));
    if(!m){
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }


    for (int i = 0; i < *vert; i++) {
        for (int j = 0; j < *vert; j++) {
            m[i * (*vert) + j] = 0;
        }
    }

    for (int i = 0; i < *a; i++) {

        fscanf(ficheiro, " e %d %d %d", &linhas, &colunas, &custo);

        m[(linhas - 1) * (*vert) + colunas - 1] = custo;
        m[(colunas - 1) * (*vert) + linhas - 1] = custo;
    }

    fclose(ficheiro);

    return m;
}


struct info init_dataEvul(int a)
{
    struct  info x;

    x.popsize =  100;
    x.pm = 0.01;
    x.pr = 0.5 ;
    x.tsize =  2;
    x.numGenerations = 1000;
    x.numGenes = a;

    if (x.numGenes > MAX_OBJ)
    {
        printf("Number of itens is superior to MAX_OBJ\n");
        exit(1);
    }
    x.ro = 0.0;

    return x;
}

int flip()
{
    if ((((float)rand()) / RAND_MAX) < 0.5)
        return 0;
    else
        return 1;
}

pchrom init_pop(struct info d, int k)
{

    int  countador;
    pchrom  indiv;

    indiv = malloc(sizeof(chrom)*d.popsize);

    if (indiv==NULL)
    {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    for (int i=0; i<d.popsize; i++)
    {
        countador = 0;
        for (int j = 0; j<d.numGenes; j++){

            indiv[i].p[j] = flip();

            if(indiv[i].p[j] == 1){
                countador++;

                }
            }

        }
    return indiv;

    /*
    printf("\n Foi gerado :");
    for (int i = 0; i < d.numGenes; ++i) {
        for (int j = 0; j < d.numGenes; ++j) {
            printf("%d", indiv[i].p[j]);
        }
        printf("\n");
          }
*/


}


int eval_rep(int sol[], struct info d, int *mat, int *v, int k) {
    int sumPeso,  pos ;
    int aux_pos, pos_2;
    int flag;
    int count_1s = 0;

    for (int i = 0; i < d.numGenes; ++i) {
        if(sol[i] == 1)
            count_1s ++;
    }

    while(count_1s != k){

        if(count_1s > k){

            aux_pos = random_l_h(0, d.numGenes - 1);
            if(sol[aux_pos] == 1) {
                sol[aux_pos] = 0;
                count_1s --;
            }
        }

        else if(count_1s < k){
            aux_pos = random_l_h(0, d.numGenes - 1);
            if(sol[aux_pos] == 0) {
                sol[aux_pos] = 1;
                count_1s ++;
            }
        }

        
    }
    
    /*
    printf("\n solucao antes ");
    for (int i = 0; i < d.numGenes; ++i)
        printf("%d",sol[i]);
*/
    while (solucao_valida(sol, mat, d.numGenes) != 1) {

        aux_pos = pos_inv(sol, mat, d.numGenes);
        sol[aux_pos] = 0;
        do {

            do
             pos = random_l_h(0, d.numGenes - 1);
             while (sol[pos] != 1);

            do
                pos_2 = random_l_h(0, d.numGenes - 1);
             while (sol[pos_2] != 0);

                if (sol[pos_2] == 0 && *(mat + pos_2 * d.numGenes + pos) > 0 ) {
                    sol[pos_2] = 1;
                    flag = 1;

                    }

        }while(flag !=1);
    }
    /*
    printf("\n solucao gerada ");
    for (int i = 0; i < d.numGenes; ++i)
        printf("%d",sol[i]);
    */
    *v = 1;
    sumPeso = calcula_fit(sol, mat, d.numGenes);

    return sumPeso;
}


chrom getBest(pchrom pop, struct info d, chrom best)
{

    for (int i=0; i < d.popsize; i++)
    {

        if (best.fitness > pop[i].fitness)
            best=pop[i];
    }
    return best;
}

void evaluate(pchrom pop, struct info d, int *mat, int k)
{

   for (int i=0; i<d.popsize; i++) {

       //pop[i].fitness = eval_penali(pop[i].p, d, mat, &pop[i].valido);
       pop[i].fitness = eval_rep(pop[i].p, d, mat, &pop[i].valido, k);
   }

}


void gera_sol_inicial(int *sol, int v ,int k) {
    int x;
    int contador = 0;

    for (int i = 0; i < v; i++)
        sol[i] = 0;

    while (contador < k) {
        x = random_l_h(0, v - 1);
        if (sol[x] == 0) {
            sol[x] = 1;
            contador++;
        }
    }
}


void escreve_sol(int *sol, int vert, int n)
{
    printf("\nConjunto S%d: [",n);
    for (int i = 0; i < vert; i++)
        printf(" %d", sol[i]);

    printf(" ]\n");
}

void init_rand()
{
    srand((unsigned)time(NULL));
}

// Gera um valor inteiro aleat�rio entre min e max
// Par�metros de entrada: Valor inferior do intervalo, min, Valor superior do intervalo, max
// Par�metros de sa�da: Valor aleat�rio entre min e max
int random_l_h(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// Gera um valor inteiro aleat�rio entre 0 e 1
float rand_01()
{
    return ((float)rand()) / RAND_MAX;
}

void escreve_Best_evul(chrom x, struct info d){

    printf("\nBest individual: %d\n", x.fitness);
    for (int i=0; i<d.numGenes; i++)
        printf("%d", x.p[i]);
    putchar('\n');

}



