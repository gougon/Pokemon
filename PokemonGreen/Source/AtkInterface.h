#pragma once
#include <string>
#include <vector>
#include <stack>
#include <set>
#include "PokemonMenu.h"
#include "Bag.h"
#include "Pokemon.h"
#include "PmValue.h"
#include "AtkBar.h"
#include "PmList.h"
#include "ActionObject.h"

using namespace std;
namespace game_framework {
	class CHero;
	class Trainer;

	constexpr auto SELFPM_X = 110;
	constexpr auto SELFPM_Y = 225;
	constexpr auto ENEMYPM_X = 420;
	constexpr auto ENEMYPM_Y = 35;

	enum Cursor {
		fight, openbag, pokemon, escape,

		skill1 = 0, // 左上
		skill2 = 1, // 右上
		skill3 = 2, // 左下
		skill4 = 3, // 右下

		yes = 0, no = 1
	};

	enum State {
		openAnime, heroAppear, heroStay, heroLeave, pokemonAppear,
		loadStartStatu,
		action,
		chooseSkill, choosePokemon, chooseItem,
		usePokeBall, enemyInStruggle, unCatch,
		onSkill,
		loadProgressStatu,
		loadEndStatu,
		enemyLoadStartStatu, 
		onEnemySkill, 
		enemyLoadProgressStatu,
		enemyLoadEndStatu,
		atkStatu, 
		hpAnime, 
		endAnime, endDialog, end
	};

	class AtkInterface : public ActionObject {
	public:
		AtkInterface();
		virtual ~AtkInterface();
		virtual void Init();
		virtual void OnMove();
		virtual void OnShow();
		virtual void LoadBitmap();
		virtual void SetTopLeft() {}
		void ReceivePmMenu(PokemonMenu *pmMenu);
		void ReceiveBag(Bag *bag);
		void ReceiveEnemy(CHero *self, Pokemon *enemy);
		void ReceiveTrainer(CHero *self, Trainer *trainer);
		void KeyDownListener(UINT nChar);
		void Start();
		void End();
	private:
		const int PMLIST_LEFT_LEFT = 0;
		const int PMLIST_LEFT_TOP = 95;
		const int PMLIST_RIGHT_LEFT = 360;
		const int PMLIST_RIGHT_TOP = 263;
		const int PMLIST_LEN = 278;

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

		void SetMyAtkPm();
		void SetTrainerAtkPm();
		void SetSkillText();
		int GetAddExp(Pokemon *enemy);
		void AddExp(int order);
		void SetValue(int order);
		void UseItem();
		void SltPm();
		void SetCursorPosition(int cursor, State state);

		int delayCount = 0, audioCounter = 0, enemyStruggleCounter = 0;
		int openCount = 0, cursor, enemySkill, textCount, lvupCount;
		bool isAnime, isBattleEnd;
		stack<State> states;
		string atkStatuTemp;
		set<Pokemon*> joinAtkPm, lvupPm;
		AtkBar myBar, enemyBar;
		State state;
		PmList myList, trainerList;
		CMovingBitmap black, battleBackground, battleOption, battleDialog, skillOption, battleGround[2];
		CMovingBitmap  atkCursor, ynPanel, lvupPanel, lvupFpanel;
		CMovingBitmap  *battleTrainer, battleHero;
		CText outcomeText;
		CText atkText, atkStatuText;
		CText valueUpText[6], valueFinalText[6];
		CText remainPPText, allPPText, skTypeText;
		vector<CText> skillText;
		CHero *self;
		Trainer *trainer;
		Pokemon *enemy, *myPm;
		PokemonMenu *pmMenu;
		Bag *bag;
		PmValue value;
		CItem* pokeball;
		ItemFactory itemFactory;
	};
}