#include "MainCharacter.h"

MainCharacter::MainCharacter(string nome){
	this -> the_skills = new CharacterSkill();
	this -> mochila = new Backpack();

	this -> NIVEL = 1;
	this -> EXPERIENCIA = 0;
	this -> VIDA =  20 + (rand() % 20);
	this -> AGILIDADE = 10 + (rand() % 20);
	this -> DEFESA = 10 + (rand() % 10);
	this -> ATAQUE = 15 + (rand() % 20);
	this -> CHARME = 10 + (rand() % 30);
	this -> CARISMA = 20 + (rand() % 6);

	this -> NOME_PERSONAGEM = nome;

	if(nomainus(this -> NOME_PERSONAGEM, "DISNEY", '\0') == 0)
		this -> CHARME = -9990;

	else if((nomainus(this -> NOME_PERSONAGEM, "FRANCIS", '\0') == 0) || (nomainus(this -> NOME_PERSONAGEM, "TITO", '\0') == 0))
		this -> CHARME = 9990;

	else if((nomainus(this -> NOME_PERSONAGEM, "JICTYVOO", '\0') == 0) || (nomainus(this -> NOME_PERSONAGEM, "JOAO", '\0') == 0)){
		this -> ATAQUE = 40;
		this -> DEFESA = 30;
	}

	else if((nomainus(this -> NOME_PERSONAGEM, "ABEL", '\0') == 0) || (nomainus(this -> NOME_PERSONAGEM, "HOBBIT", '\0') == 0))
		this -> AGILIDADE = 30;

	else if(nomainus(this -> NOME_PERSONAGEM, "VINICIUS", '\0') == 0)
		this -> CARISMA = 500;

	all_regen();
}

MainCharacter::MainCharacter(){
	this -> the_skills = new CharacterSkill();
	this -> mochila = new Backpack();
}

MainCharacter::~MainCharacter(){
	delete this -> the_skills;
	delete this -> mochila;
}

bool MainCharacter::verifica_upa(){
	unsigned long int novo_nivel;
	unsigned short int temporaria = 0;
	do{
		novo_nivel = (unsigned long int) this -> EXPERIENCIA/ (100 * (this -> NIVEL + 1));

		if(novo_nivel >= this -> NIVEL){
			if(novo_nivel > this -> NIVEL){
				this -> NIVEL = (unsigned long int) this -> NIVEL + 1;
				temporaria = temporaria + 1;
				level_up();
			}
			else if(novo_nivel == this -> NIVEL){
				if(temporaria != 0)
					return true;
				return false;
			}
		}

		else
			return false;

	}while(this -> NIVEL != novo_nivel);
	return true;
}

void MainCharacter::SetTotalAtributos(long int vetor_mudanca[]){
	this -> VIDA = vetor_mudanca[0];
	this -> AGILIDADE = vetor_mudanca[1];
	this -> DEFESA = vetor_mudanca[2];
	this -> ATAQUE = vetor_mudanca[3];
	this -> CHARME = vetor_mudanca[4];
	this -> CARISMA = vetor_mudanca[5];
	this -> EXPERIENCIA = vetor_mudanca[6];
	this -> the_skills -> TOTAL_MANA = vetor_mudanca[7];
	this -> NIVEL = vetor_mudanca[8];
}

void MainCharacter::SetHaveAtributos(string atributo, long int novo_valor){
	if(atributo == "DEFESA")
		this -> have_defense = novo_valor;
	else if(atributo == "AGILIDADE")
		this -> have_agility = novo_valor;
	else if(atributo == "CARISMA")
		this -> have_charism = novo_valor;
	else if(atributo == "ATAQUE")
		this -> have_attack = novo_valor;
	else if(atributo == "VIDA")
		this -> have_life = novo_valor;
}

char* MainCharacter::GetSkillAtiva(){
	return this -> the_skills -> ativadas;
}

void MainCharacter::SetSkillAtiva(unsigned short int indentificador, char novo_valor){
	this -> the_skills -> ativadas[indentificador] = novo_valor;
}

void MainCharacter::SetMudancaSkill(string nome_skill, long int novo_valor){
	this -> the_skills -> SetMudancaPelasSkills(nome_skill, novo_valor);
}

void MainCharacter::ResetaSkillMudanca(string nome_skill){
	long int mudanca_atributos = this -> the_skills -> GetMudancaPelasSkills(nome_skill);
	if(nome_skill == "INSPIRACAO")
		this -> have_charism = this -> have_charism - mudanca_atributos;
	else if(nome_skill == "BE_DWARF"){
		this -> have_agility = this -> have_agility - mudanca_atributos;
		this -> have_attack = this -> have_attack + mudanca_atributos;
	}
	else if(nome_skill == "BE_GIANT"){
		this -> have_attack = this -> have_attack - mudanca_atributos;
		this -> have_agility = this -> have_agility + mudanca_atributos;
	}
}

void MainCharacter::Utiliza_itens(string nome_mudanca, long int mudanca){
	if(nome_mudanca == "Essencia de Francis"){
		if(this -> mochila -> SetItensQuantity(nome_mudanca) == true){
			this -> CHARME = this -> CHARME + mudanca;
			this -> have_charm = this -> have_charm + mudanca;
		}
	}
	else if(nome_mudanca == "Elixir")
		if(this -> mochila -> SetItensQuantity(nome_mudanca) == true)
			this -> life_regen();
	else if(nome_mudanca == "Ataque Booster"){
		if(this -> mochila -> SetItensQuantity(nome_mudanca) == true){
			this -> ATAQUE = this -> ATAQUE + mudanca;
			this -> have_attack = this -> have_attack + mudanca;
		}
	}
	else if(nome_mudanca == "Defesa Booster"){
		if(this -> mochila -> SetItensQuantity(nome_mudanca) == true){
			this -> DEFESA = this -> DEFESA + mudanca;
			this -> have_defense = this -> have_defense + mudanca;
		}
	}
	else if(nome_mudanca == "Agilidade Booster"){
		if(this -> mochila -> SetItensQuantity(nome_mudanca) == true){
			this -> AGILIDADE = this -> AGILIDADE + mudanca;
			this -> have_agility = this -> have_agility + mudanca;
		}
	}
}

unsigned short int MainCharacter::UpaSkills(string skill_selected){
	if(skill_selected == "INSPIRACAO" && (this -> the_skills -> skill_points > 0)){
		this -> the_skills -> INSPIRACAO = this -> the_skills -> INSPIRACAO + 1;
		this -> the_skills -> skill_points = this -> the_skills -> skill_points - 1;
		return this -> the_skills -> INSPIRACAO;
	}
	else if(skill_selected == "ABEL'S POWER" && (this -> the_skills -> skill_points > 0)){
		this -> the_skills -> BE_DWARF = this -> the_skills -> BE_DWARF + 1;
		this -> the_skills -> skill_points = this -> the_skills -> skill_points - 1;
		return this -> the_skills -> BE_DWARF;
	}
	else if(skill_selected == "AURELIO'S POWER" && (this -> the_skills -> skill_points > 0)){
		this -> the_skills -> BE_GIANT = this -> the_skills -> BE_GIANT + 1;
		this -> the_skills -> skill_points = this -> the_skills -> skill_points - 1;
		return this -> the_skills -> BE_GIANT;
	}
	else if(skill_selected == "INVOCAR TRETA" && (this -> the_skills -> skill_points > 0)){
		this -> the_skills -> SUMMON_TRETA = this -> the_skills -> SUMMON_TRETA + 1;
		this -> the_skills -> skill_points = this -> the_skills -> skill_points - 1;
		return this -> the_skills -> SUMMON_TRETA;
	}
	return 0;
}

bool MainCharacter::teste_fuga(unsigned short int chance){
	if(chance == 100000)
		return false;
	unsigned short int conseguido;
	conseguido = this -> NIVEL + (rand() % (this -> have_agility + (rand() % 5)) );
	if(conseguido >= chance)
		return true;
	else
		return false;
}

long int MainCharacter::win_battle(long int COMMENEMY[], unsigned long int chance, unsigned short int mensagens_retorno[]){
	long int experiencia_ganha;
	if(COMMENEMY[12] > 2)
		experiencia_ganha = (long int) ((COMMENEMY[12] / 2) + rand() % (COMMENEMY[12] / 2));
	else
		experiencia_ganha = (long int) COMMENEMY[12];

	this -> EXPERIENCIA = (long int) this -> EXPERIENCIA + experiencia_ganha;

	if(verifica_upa() == true)
		mensagens_retorno[0] = 1;
	else
		mensagens_retorno[0] = 0;

	mensagens_retorno[1] = mochila -> drop_itens(chance);

	return experiencia_ganha;
}

/*sobrecarga do operador <<*/
/*friend ostream& operator<<(ostream& os, const Personagem& ESTE_PERSONAGEM){

	os << ESTE_PERSONAGEM.VIDA << ESTE_PERSONAGEM.have_life;
	os << ESTE_PERSONAGEM.AGILIDADE << ESTE_PERSONAGEM.have_agility;
	os << ESTE_PERSONAGEM.DEFESA << ESTE_PERSONAGEM.have_defense;
	os << ESTE_PERSONAGEM.ATAQUE << ESTE_PERSONAGEM.have_attack;
	os << ESTE_PERSONAGEM.CHARME << ESTE_PERSONAGEM.have_charm;
	os << ESTE_PERSONAGEM.CARISMA << ESTE_PERSONAGEM.have_charism;
	os << ESTE_PERSONAGEM.EXPERIENCIA << ESTE_PERSONAGEM.NIVEL;
	os << ESTE_PERSONAGEM.DEFESA << ESTE_PERSONAGEM.have_defense;
	os << ESTE_PERSONAGEM.NOME_PERSONAGEM;

	/*Salvando valores da classe CharacterSkill*/
	/*os << ESTE_PERSONAGEM.the_skills -> TOTAL_MANA;
	os << ESTE_PERSONAGEM.the_skills -> have_mana;
	os << ESTE_PERSONAGEM.the_skills -> skill_points;
	os << ESTE_PERSONAGEM.the_skills -> INSPIRACAO;
	os << ESTE_PERSONAGEM.the_skills -> SUMMON_TRETA;
	os << ESTE_PERSONAGEM.the_skills -> BE_DWARF;
	os << ESTE_PERSONAGEM.the_skills -> BE_GIANT;
	for(unsigned short int temporaria = 0; temporaria < 4; temporaria = temporaria + 1)
		os << ESTE_PERSONAGEM.the_skills -> ativadas[temporaria];

	/*Salvando valores da classe Backpack*/
	/*os << ESTE_PERSONAGEM.mochila -> francis_essence;
	os << ESTE_PERSONAGEM.mochila -> elixir;
	os << ESTE_PERSONAGEM.mochila -> aumenta_atk;
	os << ESTE_PERSONAGEM.mochila -> aumenta_def;
	os << ESTE_PERSONAGEM.mochila -> aumenta_agi;

	return os;
}

/*sobrecarga do operador >>*/
/*friend istream& operator>>(istream& is, Personagem& ESTE_PERSONAGEM){

	is >> ESTE_PERSONAGEM.VIDA >> ESTE_PERSONAGEM.have_life;
	is >> ESTE_PERSONAGEM.AGILIDADE >> ESTE_PERSONAGEM.have_agility;
	is >> ESTE_PERSONAGEM.DEFESA >> ESTE_PERSONAGEM.have_defense;
	is >> ESTE_PERSONAGEM.ATAQUE >> ESTE_PERSONAGEM.have_attack;
	is >> ESTE_PERSONAGEM.CHARME >> ESTE_PERSONAGEM.have_charm;
	is >> ESTE_PERSONAGEM.CARISMA >> ESTE_PERSONAGEM.have_charism;
	is >> ESTE_PERSONAGEM.EXPERIENCIA >> ESTE_PERSONAGEM.NIVEL;
	is >> ESTE_PERSONAGEM.DEFESA >> ESTE_PERSONAGEM.have_defense;
	is >> ESTE_PERSONAGEM.NOME_PERSONAGEM;

	/*Recebendo valores da classe CharacterSkill*/
	/*is >> ESTE_PERSONAGEM.the_skills -> TOTAL_MANA;
	is >> ESTE_PERSONAGEM.the_skills -> have_mana;
	is >> ESTE_PERSONAGEM.the_skills -> skill_points;
	is >> ESTE_PERSONAGEM.the_skills -> INSPIRACAO;
	is >> ESTE_PERSONAGEM.the_skills -> SUMMON_TRETA;
	is >> ESTE_PERSONAGEM.the_skills -> BE_DWARF;
	is >> ESTE_PERSONAGEM.the_skills -> BE_GIANT;
	for(unsigned short int temporaria = 0; temporaria < 4; temporaria = temporaria + 1)
		is >> ESTE_PERSONAGEM.the_skills -> ativadas[temporaria];

	/*Recebendo valores da classe Backpack*/
	/*is >> ESTE_PERSONAGEM.mochila -> francis_essence;
	is >> ESTE_PERSONAGEM.mochila -> elixir;
	is >> ESTE_PERSONAGEM.mochila -> aumenta_atk;
	is >> ESTE_PERSONAGEM.mochila -> aumenta_def;
	is >> ESTE_PERSONAGEM.mochila -> aumenta_agi;

	return is;
}*/
