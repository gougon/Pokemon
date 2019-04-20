#pragma once
#include <string>
#include <vector>
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class PokemonBar {
	public:
		void OnShow();
		void LoadBitmap();
		void LoadPosition();
		void SetOrder(int order);
		void SetAll(string name, int level, int hp, int remainHp);
		void LoadHpLen();
	private:
		const int BLD_BAR_FIRST_LEFT = 85;
		const int BLD_BAR_FIRST_TOP = 177;
		const int BLD_BAR_LEFT = 490;
		const int BLD_BAR_TOP = 55;
		const int BLD_BAR_INTERVAL = 71;

		CMovingBitmap *targetHp;
		CMovingBitmap greenHp, yellowHp, redHp;
		// CMovingBitmap pmImg;
		int order;
		int hp, remainHp, hpLen, level;
		string name;
	};
}
