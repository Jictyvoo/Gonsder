#ifndef COM_BR_HAGENIX_GAMES_UTIL_OS_CHECK_USE_H
#define COM_BR_HAGENIX_GAMES_UTIL_OS_CHECK_USE_H

#include <iostream>

#if _WIN32    /*verifica qual o sistema operacional para definir o tipo de comando a usar*/
#define OPERATIONAL_SYSTEM 1
#else
#define OPERATIONAL_SYSTEM 0
#endif // _WIN32

/*abaixo toda as declaracoes de funcoes, estruturas, ponteiros e variaveis de auxilio*/

void clearScreen() {    /*ira limpar a tela a depender do sistema operacional*/
    system("cls || clear");
}

void clearKeyboardBuff() {    /*irá limpar o buff no teclado a depender do sistema operacional*/
    setbuf(stdin, nullptr);
}

void entrada_buff(FILE *file) {    /*ir� limpar o buff do arquivo a depender do sistema operacional*/
    setbuf(file, nullptr);
}

void continuar_enter() {    /*funcao para reset das informacoes exibidas e continuacao da execucao do programa*/
    clearKeyboardBuff();
    printf("\nPressione ENTER para continuar. . . ");
    getchar();
    clearKeyboardBuff();
}

#endif /* COM_BR_HAGENIX_GAMES_UTIL_OS_CHECK_USE_H */
