#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// Função de comparação para qsort
int compararCidades(const void *a, const void *b) {
    Cidade *cidadeA = (Cidade *)a;
    Cidade *cidadeB = (Cidade *)b;
    return cidadeA->Posicao - cidadeB->Posicao;
}

// Função para inicializar as cidades a partir de um arquivo
Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro: Não foi possível abrir o arquivo.\n");
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        printf("Erro: Falha na alocação de memória para Estrada.\n");
        fclose(arquivo);
        return NULL;
    }

    if (fscanf(arquivo, "%d", &(estrada->T)) != 1) {
        printf("Erro: Falha na leitura do comprimento da estrada.\n");
        free(estrada);
        fclose(arquivo);
        return NULL;
    }
    if (fscanf(arquivo, "%d", &(estrada->N)) != 1) {
        printf("Erro: Falha na leitura do número de cidades.\n");
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    if (estrada->T < 3 || estrada->T > 1000000 || estrada->N < 2 || estrada->N > 10000) {
        printf("Erro: Valores de T ou N fora dos limites permitidos.\n");
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        printf("Erro: Falha na alocação de memória para cidades.\n");
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        if (fscanf(arquivo, "%d %s", &(estrada->C[i].Posicao), estrada->C[i].Nome) != 2) {
            printf("Erro: Falha na leitura dos dados da cidade %d.\n", i + 1);
            free(estrada->C);
            free(estrada);
            fclose(arquivo);
            return NULL;
        }
        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T) {
            printf("Erro: Posição da cidade %d fora dos limites permitidos.\n", i + 1);
            free(estrada->C);
            free(estrada);
            fclose(arquivo);
            return NULL;
        }
    }

    fclose(arquivo);
    return estrada;
}

// Função para calcular a menor vizinhança
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        return -1.0;
    }

    // Ordenando as cidades pela posição na estrada
    qsort(estrada->C, estrada->N, sizeof(Cidade), compararCidades);

    double menor_vizinhanca = estrada->T; // Inicializando com o comprimento total da estrada

    for (int i = 0; i < estrada->N - 1; i++) {
        // Calculando a média das distâncias entre cidades adjacentes
        double vizinhanca = (estrada->C[i+1].Posicao - estrada->C[i].Posicao);
        if (vizinhanca < menor_vizinhanca) {
            menor_vizinhanca = vizinhanca;
        }
    }

    // Considerando a distância até as fronteiras
    double vizinhanca_primeira = estrada->C[0].Posicao;
    double vizinhanca_ultima = estrada->T - estrada->C[estrada->N - 1].Posicao;
    if (vizinhanca_primeira < menor_vizinhanca) {
        menor_vizinhanca = vizinhanca_primeira;
    }
    if (vizinhanca_ultima < menor_vizinhanca) {
        menor_vizinhanca = vizinhanca_ultima;
    }

    free(estrada->C);
    free(estrada);
    return menor_vizinhanca;
}

// Função para encontrar a cidade com a menor vizinhança
char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) {
        return NULL;
    }

    // Ordenando as cidades pela posição na estrada
    qsort(estrada->C, estrada->N, sizeof(Cidade), compararCidades);

    double menor_vizinhanca = estrada->T; // Inicializando com o comprimento total da estrada
    char *cidade_menor_vizinhanca = NULL;

    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhanca = (estrada->C[i+1].Posicao - estrada->C[i].Posicao);
        if (vizinhanca < menor_vizinhanca) {
            menor_vizinhanca = vizinhanca;
            cidade_menor_vizinhanca = estrada->C[i].Nome;
        }
    }

    // Considerar a distância até as fronteiras
    double vizinhanca_primeira = estrada->C[0].Posicao;
    double vizinhanca_ultima = estrada->T - estrada->C[estrada->N - 1].Posicao;
    if (vizinhanca_primeira < menor_vizinhanca) {
        menor_vizinhanca = vizinhanca_primeira;
        cidade_menor_vizinhanca = estrada->C[0].Nome;
    }
    if (vizinhanca_ultima < menor_vizinhanca) {
        menor_vizinhanca = vizinhanca_ultima;
        cidade_menor_vizinhanca = estrada->C[estrada->N - 1].Nome;
    }

    char *result = (char *)malloc(strlen(cidade_menor_vizinhanca) + 1);
    if (result) {
        strcpy(result, cidade_menor_vizinhanca);
    }

    free(estrada->C);
    free(estrada);
    return result;
}














