#ifndef COM_BR_HAGENIX_GAMES_UTIL_OS_CHECK_USE_H
#define COM_BR_HAGENIX_GAMES_UTIL_OS_CHECK_USE_H

#include <iostream>

#if _WIN32    /*verifica qual o sistema operacional para definir o tipo de comando a usar*/
#define OPERATIONAL_SYSTEM 1
#else
#define OPERATIONAL_SYSTEM 0
#endif // _WIN32

/*abaixo toda as declara��es de fun��es, estruturas, ponteiros e vari�veis de aux�lio*/

void limpa_tela() {    /*ir� limpar a tela a depender do sistema operacional*/
    if (OPERATIONAL_SYSTEM)
        system("cls");
    else
        system("clear");
}

void tecla_buff() {    /*ir� limpar o buff no teclado a depender do sistema operacional*/
    setbuf(stdin, nullptr);
}

void entrada_buff(FILE *file) {    /*ir� limpar o buff do arquivo a depender do sistema operacional*/
    setbuf(file, nullptr);
}

void continuar_enter() {    /*fun��o para reset das informa��es exibidas e continua��o da execu��o do programa*/
    tecla_buff();
    printf("\nPressione ENTER para continuar. . . ");
    getchar();
    tecla_buff();
}

#endif /* COM_BR_HAGENIX_GAMES_UTIL_OS_CHECK_USE_H */
