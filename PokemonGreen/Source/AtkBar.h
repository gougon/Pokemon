#pragma once

#include <string>
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	constexpr auto MYX = 340;
	constexpr auto ENEX = 30;
	constexpr auto MYY = 220;
	constexpr auto ENEY = 40;
	constexpr auto HP_MYX = 462;
	constexpr auto HP_MYY = 268;
	constexpr auto HP_ENEX = 132;
	constexpr auto HP_ENEY = 85;
	constexpr auto HP_LEN = 135.0;
	constexpr auto EXP_X = 424;
	constexpr auto EXP_Y = 318;
	constexpr auto EXP_LEN = 173.0;

	enum barType {
		barTypeMy, barTypeEnemy
	};

	class AtkBar {
	public:
		AtkBar() { /* empty body */ }
		void LoadBitmap();
		void Init(barType type);
		void OnMove(Pokemon *pm);
		void OnShow();
		bool IsAddExp();
	private:
		int x; // right
		float rate;
		bool isAddExp;
		barType type;
		CMovingBitmap myBar, enemyBar, greenHP, yellowHP, redHP, expBar;
	};
}
