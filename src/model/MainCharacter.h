#ifndef COM_BR_HAGENIX_GAMES_MODEL_MAINCHARACTER_H_
#define COM_BR_HAGENIX_GAMES_MODEL_MAINCHARACTER_H_

#include "LiveThing.cpp"

/*aditional classes*/
#include "Backpack.cpp"
#include "CharacterSkill.cpp"

class MainCharacter: protected LiveThing{
	
	private:
		CharacterSkill *the_skills;
		Backpack *mochila;
	
	public:
		MainCharacter(string nome);
	
		MainCharacter();

		~MainCharacter();
	
	private:
		bool verifica_upa();

	public:
		void SetTotalAtributos(long int vetor_mudanca[]);

		void SetHaveAtributos(string atributo, long int novo_valor);

		char* GetSkillAtiva();

		void SetSkillAtiva(unsigned short int indentificador, char novo_valor);

		void SetMudancaSkill(string nome_skill, long int novo_valor);

		void ResetaSkillMudanca(string nome_skill);

		void Utiliza_itens(string nome_mudanca, long int mudanca);

		unsigned short int UpaSkills(string skill_selected);
	
		bool teste_fuga(unsigned short int chance);
	
		long int win_battle(long int COMMENEMY[], unsigned long int chance, unsigned short int mensagens_retorno[]);
	
		/*sobrecarga do operador <<*/
		/*friend ostream& operator<<(ostream& os, const Personagem& ESTE_PERSONAGEM)*/

		/*sobrecarga do operador >>*/
		/*friend istream& operator>>(istream& is, Personagem& ESTE_PERSONAGEM)*/
};

#endif /* COM_BR_HAGENIX_GAMES_MODEL_MAINCHARACTER_H_ */
