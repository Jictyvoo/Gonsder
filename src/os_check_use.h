/*#ifndef OS_CHECK_USE_H
#define OS_CHECK_USE_H*/

#include <stdio.h>
#if _WIN32	/*verifica qual o sistema operacional para definir o tipo de comando a usar*/
#define SISTEMAOPERACIONAL 1
#else
#define SISTEMAOPERACIONAL 0
#endif // _WIN32

/*abaixo toda as declarações de funções, estruturas, ponteiros e variáveis de auxílio*/

void limpa_tela(){	/*irá limpar a tela a depender do sistema operacional*/
	if (SISTEMAOPERACIONAL)
		system("cls");
	else
		system("clear");
}

void tecla_buff(){	/*irá limpar o buff no teclado a depender do sistema operacional*/
	if (SISTEMAOPERACIONAL)
		fflush(stdin);
	else
		__fpurge(stdin);
}

void entrada_buff(FILE *entrada){	/*irá limpar o buff do arquivo a depender do sistema operacional*/
	if (SISTEMAOPERACIONAL)
		fflush(entrada);
	else
		__fpurge(entrada);
}
