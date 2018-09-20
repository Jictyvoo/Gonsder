/*Pequeno Teste*/

#include <stdio.h>

int main(){
	long int inimi_agi = 25, inimi_att = 11, inimi_def = 42;
	long friend_agi = 17, friend_att = 34, friend_def = 8;

	unsigned int dano = 0;
	long int suporte_agilidade;
	suporte_agilidade = friend_agi - inimi_agi;
	printf("%ld suporte_agilidade\n", suporte_agilidade);
	long int suporte_ataque;
	suporte_ataque = (friend_att * 1.15);
	printf("%ld suporte_ataque\n", suporte_ataque);
	dano = suporte_ataque - inimi_def;
	printf("%u ATque - Defesa\n", dano);
	suporte_agilidade = suporte_agilidade * 0.50;
	printf("%ld suporte_agi * 0.50\n", suporte_agilidade);
	dano = dano + suporte_agilidade;
	printf("DANO: %u\n", dano);
	return 0;

	/*Solução: alterar dano de unsigned pra long*/
}