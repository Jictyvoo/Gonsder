#ifndef COM_BR_HAGENIX_GAMES_MODEL_BACKPACK_H_
#define COM_BR_HAGENIX_GAMES_MODEL_BACKPACK_H_

#include <string>
using namespace std;

class Backpack{
	private:
		unsigned short int francis_essence;
		unsigned short int elixir;
		unsigned short int aumenta_atk;
		unsigned short int aumenta_def;
		unsigned short int aumenta_agi;

	public:
		Backpack();

		~Backpack();

		unsigned short int drop_itens(unsigned short int chance);

		bool SetItensQuantity(string nome_item);

		unsigned short int* getStoredItems();
	
		void setStoredItems(unsigned short int itemsVector[]);

};

#endif /* COM_BR_HAGENIX_GAMES_MODEL_BACKPACK_H_ */
