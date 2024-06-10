#include <stdio.h>
#include <stdlib.h>
#include "cidades.h"

int main() {
    const char *nomeArquivo = "teste01.txt";

    double menor_vizinhanca = calcularMenorVizinhanca(nomeArquivo);
    if (menor_vizinhanca < 0) {
        printf("Erro ao calcular a menor vizinhanca\n");
        return 1;
    }
    printf("Menor vizinhanca: %.2f\n", menor_vizinhanca);

    char *cidade_menor_vizinhanca = cidadeMenorVizinhanca(nomeArquivo);
    if (cidade_menor_vizinhanca == NULL) {
        printf("Erro ao encontrar a cidade com a menor vizinhanca\n");
        return 1;
    }
    printf("Cidade com a menor vizinhanca: %s\n", cidade_menor_vizinhanca);
    free(cidade_menor_vizinhanca);

    return 0;
}



