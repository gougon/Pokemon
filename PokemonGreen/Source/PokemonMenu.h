#pragma once
#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"
#include "Pokemon.h"
#include "PmOprtPanel.h"
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
		virtual void KeyDownListener(UINT nChar);
		void ReceiveData(vector<Pokemon*> &pms);
	private:
		const int POKEMON_BAR_LEFT = 235;
		const int POKEMON_BAR_TOP = 30;
		const int POKEMON_BAR_FIRST_LEFT = 5;
		const int POKEMON_BAR_FIRST_TOP = 60;
		const int POKEMON_BAR_INTERVAL = 70;

		CMovingBitmap selectPanel, pokemonBar_Unselect, pokemonBar_Select, pokemonFirstBar_Unselect, pokemonFirstBar_Select;
		vector<Pokemon*> pokemons;
		PokemonBar *pokemonBar;
		PmOprtPanel pmOprtPanel;
		int order;
	};
}
