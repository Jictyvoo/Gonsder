#ifndef COM_BR_HAGENIX_GAMES_MODEL_SAVEGAME_H_
#define COM_BR_HAGENIX_GAMES_MODEL_SAVEGAME_H_


class SaveGame{
	
	private: MainCharacter *PRINCIPAL;
	private: MainCharacter *COMPANHEIROS[4];
	private: unsigned short int trecho_historia;

	public: SaveGame(MainCharacter *MAIN_PERSONAGEM, MainCharacter *convertidos[], unsigned short int atual_trecho);

	public: SaveGame();

	public: ~SaveGame();

	public: MainCharacter *GetMainCharacterPrincipal();

	public: void GetCompanheiros(MainCharacter *meus_amigos[]);

	public: unsigned short int GetTrechoHistoria();

};

#endif /* COM_BR_HAGENIX_GAMES_MODEL_SAVEGAME_H_ */
