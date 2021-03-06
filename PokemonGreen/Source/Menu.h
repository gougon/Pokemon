#pragma once
#include <string>
#include <vector>
#include "CText.h"
#include "ActionObject.h"
#include "CHero.h"
#include "Pokemon.h"
#include "PokemonMenu.h"
#include "Bag.h"
#include "Self.h"

using namespace std;
namespace game_framework {
	class CHero;

	class Menu : public ActionObject {
	public:
		Menu();
		~Menu();
		virtual void Init();
		virtual void OnShow();
		virtual void OnMove();
		virtual void LoadBitmap();
		virtual void KeyDownListener(UINT nChar);
		virtual void SetTopLeft() {}
		void Start();
		void End();
		void RecieveItem(int itemID, int amount);
		void SetPokemons(vector<Pokemon*>* pms);
		void SetMoney(int* money);
		PokemonMenu *GetPokemonMenu();
		Bag* GetBag();
	private:
		const int MENU_LEFT = 474;
		const int MENU_TOP = 1;
		const int CURSOR_LEFT = 490;		// �ݧ���
		const int CURSOR_TOP = 60;
		const int MENU_INTERVAL = 47;

		enum MenuItem {
			itemPokemonMenu,
			itemBag,
			itemSelf,
			itemClose
		};
		CText showingText;
		bool isItem;
		int* money;
		int order;
		int itemCount;
		CHero* hero;
		vector<ActionObject*> items;
		vector<Pokemon*>* pokemons;
		CMovingBitmap cursor, menuTop, menuMiddle, menuBottom;
	};
}