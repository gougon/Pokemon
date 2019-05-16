#pragma once

#include "Pokemon.h"
namespace game_framework {
	class PmList {
	public:
		PmList();
		PmList(PmType type, vector<Pokemon*>* pokemons);
		~PmList();
		void LoadBitmap();
		void SetTopLeft(int left, int top);
		void OnShow();
		void LoadPokemonData(PmType type, vector<Pokemon*>* pokemons);
		int Left();
		int Top();
	private:
		const int PMLIST_BALL_LEFT_RIGHT = 202;
		const int PMLIST_BALL_RIGHT_LEFT = 55;
		const int PMLIST_BALL_INTERVAL = 27;

		int left, top;
		CMovingBitmap pmlistLeft, pmlistRight;
		vector<CMovingBitmap*> targetBall;
		PmType type;
		vector<Pokemon*>* pokemons;
	};
}