#pragma once

#include <string>
#include <vector>
#include <stack>
#include <set>
#include "CHero.h"
#include "PokemonMenu.h"
#include "Bag.h"
#include "Pokemon.h"
#include "PmValue.h"
#include "AtkBar.h"
#include "ActionObject.h"

using namespace std;
namespace game_framework {
	class CHero;

	constexpr auto SELFPM_Y = 225;
	constexpr auto ENEMYPM_Y = 35;

	enum Cursor {
		fight,
		openbag,
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
		loadStartStatu, 
		action, 
		chooseSkill,
		choosePokemon, 
		chooseItem,
		onSkill, 
		loadProgressStatu,
		loadEndStatu,
		enemyLoadStartStatu, 
		onEnemySkill, 
		enemyLoadProgressStatu,
		enemyLoadEndStatu,
		atkStatu, 
		hpAnime, 
		endAnime, 
		endDialog, 
		end
	};

	class AtkInterface : public ActionObject {
	public:
		AtkInterface();
		virtual void Init();
		virtual void OnMove();
		virtual void OnShow();
		virtual void LoadBitmap();
		virtual void SetTopLeft() {}
		void ReceivePmMenu(PokemonMenu *pmMenu);
		void ReceiveBag(Bag *bag);
		void ReceiveData(CHero *self, Pokemon *enemy);
		void KeyDownListener(UINT nChar);
		void Start();
		void End();
	private:
		const int LVUP_PANEL_LEFT = 385;
		const int LVUP_PANEL_TOP = 170;
		const int LVUP_VALUE_TOP = 190;
		const int LVUP_VALUE_LEFT = 590;
		const int LVUP_VALUE_RIGHT = 615;
		const int LVUP_VALUE_INTERVAL = 45;

		const int SKILL_LEFT = 50;
		const int SKILL_TOP = 365;
		const int SKILL_RIGHT = 220;
		const int SKILL_DOWN = 415;

		const int REMAINPP_RIGHT = 555;
		const int ALLPP_LEFT = 575;
		const int SKTYPE_LEFT = 495;

		void SetAtkPm();
		void SetSkillText();
		int GetAddExp(Pokemon *enemy);
		void AddExp(int order);
		void SetValue(int order);
		void UseItem();
		void SltPm();
		void SetCursorPosition(int cursor, State state);
		

		int delayCount = 0, audioCounter = 0;
		int openCount = 0, cursor, enemySkill, textCount, lvupCount;
		bool isAnime, isBattleEnd;
		stack<State> states;
		string atkStatuTemp;
		set<Pokemon*> joinAtkPm, lvupPm;
		AtkBar myBar, enemyBar;
		State state;
		CAnimation *statuAnime;
		CMovingBitmap black, battleBackground, battleOption, battleDialog, skillOption, battleHero, battleGround[2];
		CMovingBitmap  atkCursor, ynPanel, lvupPanel, lvupFpanel;
		CText outcomeText;
		CText atkText, atkStatuText;
		CText valueUpText[6], valueFinalText[6];
		CText remainPPText, allPPText, skTypeText;
		vector<CText> skillText;
		CHero *self;
		Pokemon *enemy, *myPm;
		PokemonMenu *pmMenu;
		Bag *bag;
		PmValue value;
	};
}