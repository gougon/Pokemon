#pragma once
#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"
#include "Pokemon.h"
#include "PmOprtView.h"
#include "PokemonBar.h"

using namespace std;
namespace game_framework {
	class Pokemon;

	class PokemonMenu : public ActionObject {
	public:
		PokemonMenu();
		~PokemonMenu();
		virtual void Init();
		virtual void OnShow();
		virtual void OnMove();
		virtual void LoadBitmap();
		virtual void SetTopLeft() {}
		virtual void KeyDownListener(UINT nChar);
		virtual void End();
		void ReceiveData(vector<Pokemon*>* pms);
		void ChangeOnAtk();
	private:
		enum pmOprtPanelSlt {
			pmOprtPanelSltView, pmOprtPanelSltChange, pmOprtPanelSltItem, pmOprtPanelSltClose
		};

		const int POKEMON_BAR_LEFT = 235;
		const int POKEMON_BAR_TOP = 30;
		const int POKEMON_BAR_FIRST_LEFT = 5;
		const int POKEMON_BAR_FIRST_TOP = 60;
		const int POKEMON_BAR_INTERVAL = 70;

		const int PANEL_LEFT = 430;
		const int PANEL_TOP = 245;
		const int CURSOR_LEFT = 445;
		const int CURSOR_TOP = 275;
		const int CURSOR_INTERVAL = 50;

		void SetPmBar();
		void SetPmBarLeftTop(int order);
		void Swap(int order1, int order2);
		CMovingBitmap selectPanel, operationPanel, cursor;
		vector<Pokemon*>* pokemons;
		PokemonBar *pokemonBar;
		PmOprtView pmOprtView;
		int order, sltPm, swapPm;
		bool isOprtPanel, isOprtSlt, isItem, isAtkChange;
	};
}
