/*
 * LiveThing.cpp
 *
 *  Created on: 30 de abr de 2017
 *      Author: jictyvoo
 */

#include "LiveThing.h"

LiveThing::LiveThing() {
	this -> NIVEL = 1;
	this -> EXPERIENCIA = 0;
	this -> VIDA =  20 + (rand() % 20);
	this -> AGILIDADE = 10 + (rand() % 20);
	this -> DEFESA = 10 + (rand() % 10);
	this -> ATAQUE = 15 + (rand() % 20);
	this -> CHARME = 10 + (rand() % 30);
	this -> CARISMA = 20 + (rand() % 6);

	this -> have_life = this -> VIDA;
	this -> have_agility = this -> AGILIDADE;
	this -> have_defense = this -> DEFESA;
	this -> have_attack = this -> ATAQUE;
	this -> have_charm = this -> CHARME;
	this -> have_charism = this -> CARISMA;

}

LiveThing::~LiveThing() {}

void LiveThing::all_regen(){
	this -> have_life = this -> VIDA;
	this -> have_agility = this -> AGILIDADE;
	this -> have_defense = this -> DEFESA;
	this -> have_attack = this -> ATAQUE;
	this -> have_charm = this -> CHARME;
	this -> have_charism = this -> CARISMA;
}

void LiveThing::life_regen(){
	this -> have_life = this -> VIDA;
}

bool LiveThing::setDamage(long int dano){
	if(dano > 0){
		this -> have_life = this -> have_life - dano;
		return true;
	}
	return false;
}

string LiveThing::getName(){
	return this -> NOME_PERSONAGEM;
}

void LiveThing::setName(string newName){
	this -> NOME_PERSONAGEM = newName;
}

long int LiveThing::attackDamage(){
	long int dano = (long int) (this -> have_attack * 1.15) + (this -> have_agility * 0.50);

	if(dano < 0)
		return 0;

	return dano;
}

short int LiveThing::criticalHit(string defenderName){
	unsigned int variation;
	unsigned int criticalChance;

	short int criticalPercent;

	variation = defenderName.size();
	criticalChance = (unsigned int) (this -> have_attack + this -> have_defense);
	if(criticalChance <= 2)
		return 0;
	if(this -> have_agility > 1)
		criticalChance = (unsigned int) (this -> have_agility * variation) / criticalChance;
	criticalPercent = 1 + rand() % 50;

	if(criticalChance <= 2)
		return 0;

	long int doCritical;
	doCritical = rand() % (criticalChance * (criticalPercent));
	if(doCritical <= criticalChance)
		return criticalPercent;
	return 0;
}

bool LiveThing::willEvade(long int oponentStrength){
	unsigned long int avoidAttack = 0;
	if(this -> have_agility > oponentStrength){
		avoidAttack = this -> have_agility - oponentStrength;
		while(avoidAttack > 100)
			avoidAttack = avoidAttack / (2 + (rand() % 2));

		unsigned long int needsToAvoid = 1 + rand() % 100;

		if(needsToAvoid <= avoidAttack)
			return true;
		else
			return false;
	}
	return false;
}

long int* LiveThing::getCharacterStatus(){
	long int *statusVector = new long int[14];
	statusVector[0] = this -> VIDA;	statusVector[1] = this -> have_life;
	statusVector[2] = this -> AGILIDADE;	statusVector[3] = this -> have_agility;
	statusVector[4] = this -> DEFESA;	statusVector[5] = this -> have_defense;
	statusVector[6] = this -> ATAQUE;	statusVector[7] = this -> have_attack;
	statusVector[8] = this -> CHARME;	statusVector[9] = this -> have_charm;
	statusVector[10] = this -> CARISMA;	statusVector[11] = this -> have_charism;
	statusVector[12] = this -> EXPERIENCIA;	statusVector[13] = this -> NIVEL;
	return statusVector;
}

void LiveThing::level_up(){
	this -> VIDA = this -> VIDA + (rand() % (10 * this -> NIVEL) );
	this -> AGILIDADE = this -> AGILIDADE + (rand() % (5 * this -> NIVEL) );
	this -> DEFESA = this -> DEFESA + (rand() % (8 * this -> NIVEL) );
	this -> ATAQUE = this -> ATAQUE + (rand() % (9 * this -> NIVEL) );
	this -> CHARME = this -> CHARME + (rand() % (31 * this -> NIVEL) );
	this -> CARISMA = this -> CARISMA + (rand() % (15 * this -> NIVEL) );
	all_regen();
}

