/*#ifndef OS_CHECK_USE_H
#define OS_CHECK_USE_H*/

#include <stdio.h>

#if _WIN32    /*verifica qual o sistema operacional para definir o tipo de comando a usar*/
#define OPERATIONAL_SYSTEM 1
#else
#define OPERATIONAL_SYSTEM 0
#endif // _WIN32

void limpa_tela() {    /*irá limpar a tela a depender do sistema operacional*/
    if (OPERATIONAL_SYSTEM)
        system("cls");
    else
        system("clear");
}

void tecla_buff() {    /*irá limpar o buff no teclado a depender do sistema operacional*/
    setbuf(stdin, NULL);
}

void entrada_buff(FILE *input) {    /*irá limpar o buff do arquivo a depender do sistema operacional*/
    setbuf(input, NULL);
}
