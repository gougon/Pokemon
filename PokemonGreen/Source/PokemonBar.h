#pragma once
#include <string>
#include <vector>
#include "Pokemon.h"
#include "CText.h"

using namespace std;
namespace game_framework {
	class PokemonBar {
	public:
		PokemonBar();
		~PokemonBar();
		void OnShow();
		void LoadBitmap();
		void SetTopLeft(int left, int top);
		void SetOrder(int order);
		void GetPokemon(Pokemon *pm);
		void SetIsSelect(bool flag);
	private:
		const int BLD_BAR_FIRST_LEFT = 80;
		const int BLD_BAR_FIRST_TOP = 117;
		const int BLD_BAR_LEFT = 256;
		const int BLD_BAR_TOP = 24;

		const int PM1_NAME_LEFT = 100;
		const int PM1_NAME_TOP = 50;
		const int PM1_LEVEL_LEFT = 125;
		const int PM1_LEVEL_TOP = 85;
		const int PM1_RH_LEFT = 80;
		const int PM1_AH_LEFT = 150;
		const int PM1_HP_TOP = 135;
		const int PM1_ICON_LEFT = 35;
		const int PM1_ICON_TOP = 35;

		const int PM2_NAME_LEFT = 105;
		const int PM2_NAME_TOP = 10;
		const int PM2_LEVEL_LEFT = 130;
		const int PM2_LEVEL_TOP = 42;
		const int PM2_RH_LEFT = 255;
		const int PM2_AH_LEFT = 325;
		const int PM2_HP_TOP = 42;
		const int PM2_ICON_LEFT = 30;
		const int PM2_ICON_TOP = 5;

		void SetPmInformation();
		void LoadHpLen();
		void IconAnime();
		CText nameText, levelText, remainHpText, allHpText;
		CMovingBitmap bar, barSelect;
		CMovingBitmap pmIcon;
		CMovingBitmap *targetHp;
		CMovingBitmap greenHp, yellowHp, redHp;
		// CMovingBitmap pmImg;
		Pokemon *pm;
		int delay;
		int order;
		int left, top;
		int hpLen;
		string name;
		bool isSelect;
	};
}

