#ifndef COM_BR_HAGENIX_GAMES_UTIL_NAME_PARTNER_H
#define COM_BR_HAGENIX_GAMES_UTIL_NAME_PARTNER_H

#include <iostream>
#include <string>

using namespace std;

int verifyPartner(string nome_arquivo, string padrao_nome) {

    unsigned short int auxiliar;

    int quantidade_TOTAL = static_cast<int>(padrao_nome.size());
    int quantidade_compara = static_cast<int>(nome_arquivo.size());

    string pra_comparar(quantidade_compara + 1, '\0');

    if (quantidade_compara > quantidade_TOTAL) {
        int j = 0;
        while (j < quantidade_TOTAL) {
            pra_comparar[j] = nome_arquivo[quantidade_compara - quantidade_TOTAL + j];
            j = j + 1;
        }
    } else
        pra_comparar = nome_arquivo;

    int i = 0;
    do {

        if ((pra_comparar[i] >= 48 && pra_comparar[i] <= 57) && (padrao_nome[i] >= 48 && padrao_nome[i] <= 57))
            auxiliar = 0;
        else if (pra_comparar[i] == padrao_nome[i])
            auxiliar = 0;
        else
            return 1;
        i = i + 1;
    } while (padrao_nome[i] != '\0');

    return auxiliar;
}

unsigned short int nomainus(string fileName, string namePartner, char ending) {

    unsigned short int aux;

    int totalQuantity = static_cast<int>(namePartner.size());
    int amountToCompare = static_cast<int>(fileName.size());

    string toCompare(amountToCompare + 1, '\0');

    if (amountToCompare > totalQuantity) {
        int j = 0;
        while (j < totalQuantity) {
            toCompare[j] = fileName[amountToCompare - totalQuantity + j];
            j = j + 1;
        }
    } else
        toCompare = fileName;

    int i = 0;
    do {
        if ((toCompare[i] >= 48 && toCompare[i] <= 57) && (namePartner[i] >= 48 && namePartner[i] <= 57))
            aux = 0;
        else if ((toCompare[i] == namePartner[i]) || (toCompare[i] == (namePartner[i] + 32)) ||
                 (toCompare[i] == (namePartner[i] - 32)))
            aux = 0;
        else
            return 1;
        i = i + 1;
    } while (namePartner[i] != ending);

    return aux;
}

#endif /* COM_BR_HAGENIX_GAMES_UTIL_NAME_PARTNER_H */
