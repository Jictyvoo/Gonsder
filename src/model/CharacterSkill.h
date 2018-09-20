#ifndef COM_BR_HAGENIX_GAMES_MODEL_CHARACTERSKILL_H_
#define COM_BR_HAGENIX_GAMES_MODEL_CHARACTERSKILL_H_

#include <string>

#include "LiveThing.h"

using namespace std;

class CharacterSkill: private LiveThing{
	public: long int TOTAL_MANA;
	public: long int have_mana;
	public: unsigned long int skill_points;
	public: unsigned short int INSPIRACAO;	/*Aumenta carisma*/
	private: long int mudanca_inspira;
	public: unsigned short int SUMMON_TRETA;	/*Invoca uma treta entre os inimigos*/
	public: unsigned short int BE_DWARF;	/*Diminui ataque, e aumenta agilidade*/
	private: long int mudanca_abel;
	public: unsigned short int BE_GIANT;	/*Aumenta ataque, e diminui agilidade*/
	private: long int mudanca_aurelio;
	public: char ativadas[4];	/*pra verificar quais skills estão ativas*/

	public: CharacterSkill();

	public: ~CharacterSkill();

	public: void SetMudancaPelasSkills(string nome_skill, long int novo_valor);

	public: long int GetMudancaPelasSkills(string nome_skill);

	public: unsigned long int getSkillPoints();

	public: void addSkillPoints(unsigned long int addedPoints);

	public: unsigned short int *GetHaveSkills();

	public: void SetHaveSkills(unsigned short int vetor_skills[]);

	public: unsigned short int* GetTotalHaveMana();

	public: void SetTotalHaveMana(string have_total, long int novo_valor);
};

#endif /* COM_BR_HAGENIX_GAMES_MODEL_CHARACTERSKILL_H_ */
