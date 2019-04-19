#pragma once

#include <string>
#include <vector>
#include "CHero.h"
#include "Pokemon.h"
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
	};

	enum State {
		openAnime, 
		heroAppear, 
		heroLeave, 
		pokemonAppear,
		action, 
		chooseSkill, 
		chooseItem,
		onSkill, 
		onEnemySkill, 
		endAnime, 
		end
	};

	class AtkInterface {
	public:
		AtkInterface();
		void Start();
		void OnMove();
		void OnShow();
		void LoadBitmap();
		void Init(CHero *self, Pokemon *enemy);
		void KeyDownListener(UINT nChar);
		bool IsAtk();
		void Dead(CHero *self);
	private:
		int openCount = 0;
		bool isAtk;
		bool isAnime;
		AtkBar myBar, enemyBar;
		State state;
		Cursor cursor;
		CMovingBitmap black, battleBackground, battleOption, battleDialog, skillOption, battleHero, battleGround[2], atkCursor;
		CHero *self;
		Pokemon *enemy;
		int enemySkill;
	};
}