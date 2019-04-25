#pragma once

#include <string>
#include <vector>
#include "CHero.h"
#include "PokemonMenu.h"
#include "Pokemon.h"
#include "PmValue.h"
#include "AtkBar.h"

using namespace std;
namespace game_framework {
	class CHero;

	constexpr auto SELFPM_Y = 225;
	constexpr auto ENEMYPM_Y = 35;

	enum Cursor {
		fight,
		bag,
		pokemon,
		escape,

		skill1 = 0, // 左上
		skill2 = 1, // 右上
		skill3 = 2, // 左下
		skill4 = 3, // 右下

		yes = 0,
		no = 1
	};

	enum State {
		openAnime, 
		heroAppear, 
		heroLeave, 
		pokemonAppear,
		action, 
		chooseSkill,
		choosePokemon, 
		chooseItem,
		onSkill, 
		onEnemySkill, 
		endAnime, 
		endDialog, 
		end
	};

	class AtkInterface {
	public:
		AtkInterface();
		void Start();
		void OnMove();
		void OnShow();
		void LoadBitmap();
		void Init(PokemonMenu *pmMenu);
		void ReceiveData(CHero *self, Pokemon *enemy);
		void KeyDownListener(UINT nChar);
		void End();
		bool IsAtk();
	private:
		const int LVUP_PANEL_LEFT = 385;
		const int LVUP_PANEL_TOP = 170;
		const int LVUP_VALUE_TOP = 195;
		const int LVUP_VALUE_LEFT = 590;
		const int LVUP_VALUE_RIGHT = 615;
		const int LVUP_VALUE_INTERVAL = 45;

		void SetAtkPm();
		int GetAddExp(Pokemon *enemy);
		void AddExp(int order);
		void SetValue(int order);
		void SltPm();

		int openCount = 0, cursor, enemySkill, textCount, lvupCount;
		bool isAtk, isAnime;
		vector<Pokemon*> joinAtkPm, lvupPm;
		AtkBar myBar, enemyBar;
		State state;
		CMovingBitmap black, battleBackground, battleOption, battleDialog, skillOption, battleHero, battleGround[2];
		CMovingBitmap  atkCursor, ynPanel, lvupPanel, lvupFpanel;
		CText outcomeText;
		CText valueUpText[6], valueFinalText[6];
		CHero *self;
		Pokemon *enemy, *myPm;
		PokemonMenu *pmMenu;
		PmValue value;
	};
}