#include <stdio.h>
#include <stdlib.h>
#include "cidades.h"

int main() {
    const char *nomeArquivo = "teste01.txt";

    // Calcular e imprimir a menor vizinhança
    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    if (menorVizinhanca < 0) {
        printf("Erro ao calcular a menor vizinhanca.\n");
        return 1;
    }
    printf("Menor vizinhanca: %.2f\n", menorVizinhanca);

    // Obter e imprimir a cidade com a menor vizinhança
    char *cidade = cidadeMenorVizinhanca(nomeArquivo);
    if (!cidade) {
        printf("Erro ao obter a cidade com a menor vizinhanca.\n");
        return 1;
    }

    return 0;
}



