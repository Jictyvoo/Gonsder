/*
 * LiveThing.h
 *
 *  Created on: 30 de abr de 2017
 *      Author: jictyvoo
 */

#ifndef COM_BR_HAGENIX_GAMES_MODEL_LIVETHING_H_
#define COM_BR_HAGENIX_GAMES_MODEL_LIVETHING_H_

#include <string>
using namespace std;

class LiveThing {
	public:
		LiveThing();
		virtual ~LiveThing();

	protected:
		long int VIDA;
		long int have_life;

		long int AGILIDADE;
		long int have_agility;

		long int DEFESA;
		long int have_defense;

		long int ATAQUE;
		long int have_attack;

		long int CHARME;
		long int have_charm;

		long int CARISMA;
		long int have_charism;

		unsigned long int EXPERIENCIA;
		unsigned long int NIVEL;

		string NOME_PERSONAGEM;

	protected:
		void level_up();
		void life_regen();

	public:

		void all_regen();

		bool setDamage(long int dano);

		string getName();

		void setName(string newName);

		long int attackDamage();

		short int criticalHit(string nome_defensor);

		bool willEvade(long int oponentStrength);

		long int* getCharacterStatus();
};

#endif /* COM_BR_HAGENIX_GAMES_MODEL_LIVETHING_H_ */
