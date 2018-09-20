#include <stdio.h>
#include <stdlib.h>

/*BIBLIOTECA QUE CONT?M FUN??ES DE ALOCA??O DIN?MICA DE STRINGS*/
/*A FUN??O dina_scan DEVE RECEBER COMO ARGUMENTO UM ENDERE?O DE MEM?RIA DE UM PONTEIRO DO TIPO CHAR*/
/*A FUN??O libera_dina DEVE RECEBER O PONTEIRO QUE APONTA PARA A MEM?RIA ALOCADA*/
/*EXEMPLOS: dina_scan(&ponteiro);			libera_dina(ponteiro);*/

void dina_scan(char **alocou) {
    int i = 0;
    (*alocou) = (char *) malloc(sizeof(char));
    do {
        (*alocou) = (char *) realloc((*alocou), (i + 1) * sizeof(char));
        fscanf(stdin, "%c", &(*alocou)[i]);
        i = i + 1;
    } while ((*alocou)[i - 1] != '\n');
    (*alocou)[i - 1] = '\0';
}

void fdina_scan(FILE *entrada, char **alocou, char termino) {
    int i = 0;
    (*alocou) = (char *) malloc(sizeof(char));
    do {
        (*alocou) = (char *) realloc((*alocou), (i + 1) * sizeof(char));
        fscanf(entrada, "%c", &(*alocou)[i]);
        i = i + 1;
    } while ((*alocou)[i - 1] != termino);
    (*alocou)[i - 1] = '\0';
}

void libera_dina(char *alocou) {
    free(alocou);
}
