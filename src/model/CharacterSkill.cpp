#include "CharacterSkill.h"

CharacterSkill :: CharacterSkill(){
	this -> TOTAL_MANA = 120 + (rand() % 61);
	this -> have_mana = this -> TOTAL_MANA;
	this -> skill_points = 0;

	this -> INSPIRACAO = 0;
	this -> SUMMON_TRETA = 0;
	this -> BE_DWARF = 0;
	this -> BE_GIANT = 0;
	for(int temporaria = 0; temporaria < 4; temporaria++)
		ativadas[temporaria] = false;
	this -> mudanca_aurelio = 0;
	this -> mudanca_abel = 0;
	this -> mudanca_inspira = 0;
}

CharacterSkill :: ~CharacterSkill(){}

void CharacterSkill :: SetMudancaPelasSkills(string nome_skill, long int novo_valor){
	if(nome_skill == "INSPIRACAO")
		this -> mudanca_inspira = novo_valor;
	else if(nome_skill == "BE_DWARF")
		this -> mudanca_abel = novo_valor;
	else if(nome_skill == "BE_GIANT")
		this -> mudanca_aurelio = novo_valor;
}

long int CharacterSkill :: GetMudancaPelasSkills(string nome_skill){
	if(nome_skill == "INSPIRACAO")
		return this -> mudanca_inspira;
	else if(nome_skill == "BE_DWARF")
		return this -> mudanca_abel;
	else if(nome_skill == "BE_GIANT")
		return this -> mudanca_aurelio;
	return 0;
}

unsigned long int CharacterSkill::getSkillPoints(){
	return this -> skill_points;
}

void CharacterSkill::addSkillPoints(unsigned long int addedPoints){
	this -> skill_points = addedPoints;
}

unsigned short int* CharacterSkill::GetHaveSkills(){
	unsigned short int *vetor_skills = new unsigned short int[4];
	vetor_skills[0] = this -> INSPIRACAO;
	vetor_skills[1] = this -> SUMMON_TRETA;
	vetor_skills[2] = this -> BE_DWARF;
	vetor_skills[3] = this -> BE_GIANT;
	return vetor_skills;
}

void CharacterSkill::SetHaveSkills(unsigned short int vetor_skills[]){
	this -> INSPIRACAO = vetor_skills[0];
	this -> SUMMON_TRETA = vetor_skills[1];
	this -> BE_DWARF = vetor_skills[2];
	this -> BE_GIANT = vetor_skills[3];
}

unsigned short int* CharacterSkill::GetTotalHaveMana(){
	unsigned short int *vetor_skills = new unsigned short int[2];
	vetor_skills[0] = this -> have_mana;
	vetor_skills[1] = this -> TOTAL_MANA;
	return vetor_skills;
}

void CharacterSkill::SetTotalHaveMana(string have_total, long int novo_valor){
	if(have_total == "HAVE")
		this -> have_mana = novo_valor;
	else if(have_total == "TOTAL")
		this -> TOTAL_MANA = novo_valor;
}
