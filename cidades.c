#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        return NULL;
    }

    int T, N;
    if (fscanf(file, "%d", &T) != 1 || T < 3 || T > 1000000) {
        fclose(file);
        return NULL;
    }
    
    if (fscanf(file, "%d", &N) != 1 || N < 2 || N > 10000) {
        fclose(file);
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        fclose(file);
        return NULL;
    }

    estrada->T = T;
    estrada->N = N;
    estrada->C = (Cidade *)malloc(N * sizeof(Cidade));
    if (!estrada->C) {
        free(estrada);
        fclose(file);
        return NULL;
    }

    // Comando para que toda a linha seja lida (inclusive espaços) antes de pular para próxima
    char line[256];
    fgets(line, sizeof(line), file);

    for (int i = 0; i < N; i++) {
        if (fgets(line, sizeof(line), file)) {
            int posicao;
            char nome[256];
            if (sscanf(line, "%d %[^\n]", &posicao, nome) == 2 && posicao >= 0 && posicao <= T) {
                estrada->C[i].Posicao = posicao;
                strcpy(estrada->C[i].Nome, nome);
            } else {
                free(estrada->C);
                free(estrada);
                fclose(file);
                return NULL;
            }
        } else {
            free(estrada->C);
            free(estrada);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return estrada;
}

int compareCidades(const void *a, const void *b) {
    Cidade *cidadeA = (Cidade *)a;
    Cidade *cidadeB = (Cidade *)b;
    return cidadeA->Posicao - cidadeB->Posicao;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        return -1;
    }

    int N = estrada->N;
    Cidade *cidades = estrada->C;

    // Ordenando as cidades pela posição
    qsort(cidades, N, sizeof(Cidade), compareCidades);

    double menorVizinhanca = (double) estrada->T;

    // Calculando os pontos médios de cada vizinhança
    double *pontosMedios = (double *)malloc((N - 1) * sizeof(double));
    for (int i = 0; i < N - 1; i++) {
        pontosMedios[i] = (cidades[i].Posicao + cidades[i + 1].Posicao) / 2.0;
    }

    // Calculando a vizinhança de cada cidade
    for (int i = 0; i < N; i++) {
        double inicio, fim;
        if (i == 0) {
            inicio = 0;
            fim = pontosMedios[i];
        } else if (i == N - 1) {
            inicio = pontosMedios[i - 1];
            fim = estrada->T;
        } else {
            inicio = pontosMedios[i - 1];
            fim = pontosMedios[i];
        }
        double vizinhanca = fim - inicio;
        printf("Cidade %s e sua vizinhanca: %.2lf\n", cidades[i].Nome, vizinhanca); // Imprimindo as cidades e as suas vizinhanças
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(pontosMedios);
    free(estrada->C);
    free(estrada);

    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        return NULL;
    }

    int N = estrada->N;
    Cidade *cidades = estrada->C;

    qsort(cidades, N, sizeof(Cidade), compareCidades);

    double menorVizinhanca = (double) estrada->T;
    int indiceMenorVizinhanca = -1;

    double *pontosMedios = (double *)malloc((N - 1) * sizeof(double));
    for (int i = 0; i < N - 1; i++) {
        pontosMedios[i] = (cidades[i].Posicao + cidades[i + 1].Posicao) / 2.0;
    }

    for (int i = 0; i < N; i++) {
        double inicio, fim;
        if (i == 0) {
            inicio = 0;
            fim = pontosMedios[i];
        } else if (i == N - 1) {
            inicio = pontosMedios[i - 1];
            fim = estrada->T;
        } else {
            inicio = pontosMedios[i - 1];
            fim = pontosMedios[i];
        }
        double vizinhanca = fim - inicio;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            indiceMenorVizinhanca = i;
        }
    }

    char *cidadeResultado = (char *)malloc(256 * sizeof(char));
    if (indiceMenorVizinhanca != -1) {
        strcpy(cidadeResultado, cidades[indiceMenorVizinhanca].Nome);
    } else {
        strcpy(cidadeResultado, ""); // Copiando o nome da cidade com a menor vizinhança
    }

    // Imprimindo somente a cidade com a menor vizinhança
    printf("Cidade com menor vizinhanca: %s\n", cidadeResultado);


    free(pontosMedios);
    free(estrada->C);
    free(estrada);

    return cidadeResultado;
}














