//
// Created by Utilizador on 06/12/2023.
//

#ifndef TP_IIA2_ALGORITNO_H
#define TP_IIA2_ALGORITNO_H
#include "untils.h"

int trepa_colinas(int sol[], int *mat, int vert, int num_iter);
void gera_vizinho(int a[], int b[], int n);
void substitui(int a[], int b[], int n);

void tournament(pchrom pop, struct info d, pchrom parents);

void genetic_operators(pchrom parents, struct info d, pchrom offspring);


#endif //TP_IIA2_ALGORITNO_H
