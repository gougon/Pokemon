#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Functions.cpp"
#include "AtkInterface.h"
#include "ItemPokeBall.h"
#include "CHero.h"
#include "Trainer.h"

namespace game_framework {
	AtkInterface::AtkInterface()
		: ActionObject(), self(nullptr), enemy(nullptr), pokeball(nullptr), textCount(0), lvupCount(0)
	{
		/* empty body */
	}

	AtkInterface::~AtkInterface()
	{
		self = nullptr;
		trainer = nullptr;
		enemy = nullptr;
		myPm = nullptr;
		pmMenu = nullptr;
		bag = nullptr;
		battleTrainer = nullptr;
		for (auto i : joinAtkPm) i = nullptr;
		for (auto i : lvupPm) i = nullptr;
		if (pokeball != nullptr) {
			delete pokeball;
			pokeball = nullptr;
		}
	}

	void AtkInterface::OnShow()
	{
		battleBackground.ShowBitmap();
		battleGround[0].ShowBitmap();
		battleGround[1].ShowBitmap();

		switch (state)
		{
		case heroAppear:
			battleHero.ShowBitmap();
			if(trainer != nullptr)
				battleTrainer->ShowBitmap();
			battleDialog.ShowBitmap();
			break;
		case heroStay:
			battleHero.ShowBitmap();
			if (trainer != nullptr)
				battleTrainer->ShowBitmap();
			battleDialog.ShowBitmap();
			myList.OnShow();
			if(trainer != nullptr)
				trainerList.OnShow();
			outcomeText.OnShow();
			break;
		case heroLeave:
			battleHero.ShowBitmap();
			myList.OnShow();
			if (trainer != nullptr) {
				battleTrainer->ShowBitmap();
				trainerList.OnShow();
			}
			battleDialog.ShowBitmap();
			break;
		case pokemonAppear:
			myPm->OnShow();
			enemy->OnShow();
			battleDialog.ShowBitmap();
			atkText.OnShow();
			break;
		case loadStartStatu:
			myPm->OnShow();
			enemy->OnShow();
			battleOption.ShowBitmap();
			myBar.OnShow();
			enemyBar.OnShow();
			break;
		case action:
			myPm->OnShow();
			enemy->OnShow();
			battleOption.ShowBitmap();
			atkCursor.ShowBitmap();
			myBar.OnShow();
			enemyBar.OnShow();
			break;
		case chooseSkill:
			myPm->OnShow();
			enemy->OnShow();
			skillOption.ShowBitmap(); 
			atkCursor.ShowBitmap();
			myBar.OnShow();
			enemyBar.OnShow();
			remainPPText.OnShow();
			allPPText.OnShow();
			skTypeText.OnShow();
			for (auto i : skillText) i.OnShow();
			break;
		case choosePokemon:
			pmMenu->OnShow();
			break;
		case chooseItem:
			bag->OnShow();
			if(bag->SelectPokeball() == 4 && trainer != nullptr)
				outcomeText.OnShow();
			break;
		case usePokeBall:
			myPm->OnShow();
			enemy->OnShow();
			battleOption.ShowBitmap();
			atkCursor.ShowBitmap();
			myBar.OnShow();
			enemyBar.OnShow();
			dynamic_cast<ItemPokeBall*>(pokeball)->OnShow();
			break;
		case enemyInStruggle:
			myPm->OnShow();
			myBar.OnShow();
			enemyBar.OnShow();
			battleOption.ShowBitmap();
			atkCursor.ShowBitmap();
			dynamic_cast<ItemPokeBall*>(pokeball)->OnShow();
			break;
		case unCatch:
			myPm->OnShow();
			enemy->OnShow();
			battleDialog.ShowBitmap();
			outcomeText.OnShow();
			myBar.OnShow();
			enemyBar.OnShow();
			break;
		case onSkill:
			myPm->OnShow();
			enemy->OnShow();
			(myPm->GetSkill(cursor))->AtkAnimeOnShow();
			enemyBar.OnShow();
			myBar.OnShow();
			battleDialog.ShowBitmap();
			atkText.OnShow();
			break;
		case loadEndStatu:
			myPm->OnShow();
			enemy->OnShow();
			enemyBar.OnShow();
			myBar.OnShow();
			battleDialog.ShowBitmap();
			break;
		case enemyLoadStartStatu:
			myPm->OnShow();
			enemy->OnShow();
			battleDialog.ShowBitmap();
			myBar.OnShow();
			enemyBar.OnShow();
			break;
		case onEnemySkill:
			myPm->OnShow();
			enemy->OnShow();
			(enemy->GetSkill(enemySkill))->AtkAnimeOnShow();
			myBar.OnShow();
			enemyBar.OnShow();
			battleDialog.ShowBitmap();
			atkText.OnShow();
			break;
		case enemyLoadEndStatu:
			myPm->OnShow();
			enemy->OnShow();
			enemyBar.OnShow();
			myBar.OnShow();
			battleDialog.ShowBitmap();
			enemy->GetStatus()->OnShow();
			break;
		case atkStatu:
			myPm->OnShow();
			enemy->OnShow();
			myBar.OnShow();
			enemyBar.OnShow();
			battleDialog.ShowBitmap();
			atkStatuText.OnShow();
			break;
		case hpAnime:
			myPm->OnShow();
			enemy->OnShow();
			enemyBar.OnShow();
			myBar.OnShow();
			battleDialog.ShowBitmap();
			break;
		case endAnime:
			myPm->OnShow("atk");
			enemy->OnShow("atk");
			myBar.OnShow();
			enemyBar.OnShow();
			battleDialog.ShowBitmap();
			atkText.OnShow();
			break;
		case endDialog:
			if (pmMenu->IsWork())
				pmMenu->OnShow();
			else {
				if (myPm->GetRemainHP() > 0) {
					myPm->OnShow("atk");
					myBar.OnShow();
				}
				else {
					enemy->OnShow("atk");
					enemyBar.OnShow();
					myBar.OnShow();
					if (textCount == 1) {
						ynPanel.ShowBitmap();
						atkCursor.ShowBitmap();
					}
				}
				battleDialog.ShowBitmap();
				outcomeText.OnShow();
			}
			if (trainer != nullptr)
				trainerList.OnShow();
			break;
		case end:
			if (myPm->GetRemainHP() > 0) {
				myPm->OnShow();
				trainerList.OnShow();
			}
			else enemy->OnShow();
			battleDialog.ShowBitmap();
			outcomeText.OnShow();
			myBar.OnShow();
			int order = textCount - 2;
			if (myPm->GetRemainHP() > 0 && 
				FindSetFromOrder(joinAtkPm, order) ==
				((lvupPm.empty()) ? nullptr : *(lvupPm.rbegin()))) {
				switch (lvupCount) {
				case 2:
					lvupPanel.ShowBitmap();
					for (int i = 0; i < 6; ++i) 
						valueUpText[i].OnShow();
					break;
				case 3:
					lvupFpanel.ShowBitmap();
					for (int i = 0; i < 6; ++i) 
						valueFinalText[i].OnShow();
					break;
				}
			}
			break;
		}

	}

	void AtkInterface::OnMove()
	{
		constexpr auto V = 20;
		if (++audioCounter == 270)
			CAudio::Instance()->Play(AUDIO_BATTLE_PROCESS, true);
		switch (state)
		{
		case heroAppear:
			battleGround[0].SetTopLeft(battleGround[0].Left() - V, battleGround[0].Top());
			battleGround[1].SetTopLeft(battleGround[1].Left() + V, battleGround[1].Top());
			battleHero.SetTopLeft(battleHero.Left() + V, battleHero.Top());
			if (trainer != nullptr)
				battleTrainer->SetTopLeft(battleTrainer->Left() - V, battleTrainer->Top());
			if (battleGround[0].Left() <= 0)
				state = heroStay;
			break;
		case heroStay:
			if (trainer == nullptr)
				outcomeText.SetText(enemy->GetName() + " is appear");
			else 
				outcomeText.SetText(trainer->GetName() + " come to challenge");
			if (myList.Left() > PMLIST_RIGHT_LEFT) {
				if(trainer != nullptr)
					trainerList.SetTopLeft(trainerList.Left() + V, trainerList.Top());
				myList.SetTopLeft(myList.Left() - V, myList.Top());
			}
				
			break;
		case heroLeave:
			battleGround[0].SetTopLeft(battleGround[0].Left(), battleGround[0].Top());
			battleGround[1].SetTopLeft(battleGround[1].Left(), battleGround[1].Top());
			battleHero.SetTopLeft(battleHero.Left() - V, battleHero.Top());
			myList.SetTopLeft(myList.Left() + V, myList.Top());
			if (trainer != nullptr) {
				battleTrainer->SetTopLeft(battleTrainer->Left() + V, battleTrainer->Top());
				trainerList.SetTopLeft(trainerList.Left() - V, trainerList.Top());
			}
			if (battleHero.Left() <= -130)
				state = pokemonAppear;
			break;
		case pokemonAppear:
			if (myPm->Left() != SELFPM_X) {
				myPm->SetTopLeft(myPm->Left() + V, SELFPM_Y);
				enemy->SetTopLeft(enemy->Left() - V, ENEMYPM_Y);
			}
			atkText.SetText(enemy->GetName() + " appeared");
			enemyBar.OnMove();
			myBar.OnMove();
			break;
		case loadStartStatu:
			SetCursorPosition(cursor, state);
			myPm->RoundStartStatuEffect();
			state = action;
			break;
		case action:
			SetCursorPosition(cursor, state);
			break;
		case chooseSkill:
			remainPPText.SetText(to_string(myPm->GetSkill(cursor)->GetRemainPP()));
			allPPText.SetText(to_string(myPm->GetSkill(cursor)->GetAllPP()));
			skTypeText.SetText(myPm->GetSkill(cursor)->GetAttributeText());
			remainPPText.SetTopLeft(REMAINPP_RIGHT - remainPPText.GetLength() * (int)remainPPText.GetFontSize(), SKILL_TOP);
			SetCursorPosition(cursor, state);
			break;
		case choosePokemon:
			if (pmMenu->IsWork())
				pmMenu->OnMove();
			else {
				Pokemon *oldPm = myPm;
				SetMyAtkPm();
				state = (oldPm == myPm) ? action : enemyLoadStartStatu;
				myBar.ReceiveData(myPm);
			}
			break;
		case chooseItem:
			if (bag->IsWork())
				bag->OnMove();
			else {
				if (bag->SelectPokeball() == 4 && trainer == nullptr) {
					if (pokeball != nullptr) {
						delete pokeball;
						pokeball = nullptr;
					}
					pokeball = itemFactory.CreateItem(4);
					dynamic_cast<ItemPokeBall*>(pokeball)->UsePokeBall(self, enemy);
					bag->DropItem(4, 1);
					state = usePokeBall;
				}
				else {
					myBar.ReceiveData(myPm);
					state = action;
				}
			}
			break;
		case usePokeBall:
			enemyStruggleCounter = 0;
			dynamic_cast<ItemPokeBall*>(pokeball)->OnMove();
			if (dynamic_cast<ItemPokeBall*>(pokeball)->animeEnd())
				state = enemyInStruggle;
			break;
		case enemyInStruggle:
			if (enemyStruggleCounter < 60)
				enemyStruggleCounter++;
			else 
				state = dynamic_cast<ItemPokeBall*>(pokeball)->IsCatch() ? endDialog : unCatch;
			break;
		case unCatch:
			outcomeText.SetText("ah! the pokemon is escape!");
			break;
		case onSkill:
			if (!myPm->IsCanMove()) {
				states.push(state);
				state = loadProgressStatu;
				break;
			}

			if (!isAnime) {
				atkText.SetText(myPm->GetName() + " use " + myPm->GetSkill(cursor)->GetName());
				atkStatuTemp = (myPm->GetSkill(cursor))->Use(myPm, enemy);
				enemyBar.ReceiveStatu(enemy->GetStatus()->GetStatu());
				atkStatuText.SetText(atkStatuTemp);
				isAnime = true;
			}

			if ((myPm->GetSkill(cursor))->AtkAnimeOnMove()) {
				isAnime = false;
				states.push(state);
				state = hpAnime;
			}
			break;
		case loadProgressStatu:
			atkStatuTemp = myPm->RoundProgressStatuEffect();
			atkStatuText.SetText(atkStatuTemp);
			state = atkStatu;
			break;
		case loadEndStatu:
			if (!isAnime) {
				myPm->RoundEndStatuEffect();
				isAnime = true;
			}
			myPm->GetStatus()->OnMove();
			if (!myPm->GetStatus()->IsAnime()) {
				isAnime = false;
				states.push(state);
				state = hpAnime;
			}
			break;
		case enemyLoadStartStatu:
			enemySkill = rand() % enemy->GetSkillNum();
			enemy->RoundStartStatuEffect();
			state = onEnemySkill;
			break;
		case onEnemySkill:
			if (!enemy->IsCanMove()) {
				states.push(state);
				state = enemyLoadProgressStatu;
				break;
			}

			if (!isAnime) {
				atkText.SetText(enemy->GetName() + " use " + enemy->GetSkill(enemySkill)->GetName());
				atkStatuTemp = (enemy->GetSkill(enemySkill))->Use(enemy, myPm);
				myBar.ReceiveStatu(myPm->GetStatus()->GetStatu());
				atkStatuText.SetText(atkStatuTemp);
				isAnime = true;
			}

			if ((enemy->GetSkill(enemySkill))->AtkAnimeOnMove()) {
				cursor = fight;
				isAnime = false;
				states.push(state);
				state = hpAnime;
			}
			break;
		case enemyLoadProgressStatu:
			atkStatuTemp = enemy->RoundProgressStatuEffect();
			atkStatuText.SetText(atkStatuTemp);
			state = atkStatu;
			break;
		case enemyLoadEndStatu:
			if (!isAnime) {
				enemy->RoundEndStatuEffect();
				isAnime = true;
			}
			enemy->GetStatus()->OnMove();
			if (!enemy->GetStatus()->IsAnime()) {
				isAnime = false;
				states.push(state);
				state = hpAnime;
			}
			break;
		case atkStatu:
			if (++delayCount == 33) {
				delayCount = 0;
				if (states.top() == onSkill)
					state = (enemy->GetRemainHP() == 0 || myPm->GetRemainHP() == 0) ? endAnime : loadEndStatu;
				else
					state = (enemy->GetRemainHP() == 0 || myPm->GetRemainHP() == 0) ? endAnime : enemyLoadEndStatu;
			}
			break;
		case hpAnime:
			myBar.OnMove();
			enemyBar.OnMove();
			if (!myBar.IsAnime() && !enemyBar.IsAnime()) {	// anime end, change state
				switch (states.top()) {
				case onSkill:
					if (atkStatuTemp == "") 
						state = (enemy->GetRemainHP() == 0 || myPm->GetRemainHP() == 0) ? endAnime : loadEndStatu;
					else 
						state = atkStatu;
					break;
				case loadEndStatu:
					state = (myPm->GetRemainHP() == 0) ? endAnime : enemyLoadStartStatu;
					break;
				case onEnemySkill:
					if (atkStatuTemp == "") 
						state = (enemy->GetRemainHP() == 0 || myPm->GetRemainHP() == 0) ? endAnime : enemyLoadEndStatu;
					else 
						state = atkStatu;
					break;
				case enemyLoadEndStatu:
					state = (enemy->GetRemainHP() == 0) ? endAnime : loadStartStatu;
					break;
				}
			}
			break;
		case endAnime:
			if (enemy->GetRemainHP() <= 0) {
				enemy->SetTopLeft(enemy->Left(), enemy->Top() + V);
				enemy->SetHeight(enemy->GetHeight() - V);
				if (enemy->Top() >= ENEMYPM_Y + 130)
					state = endDialog;
			}
			else {
				myPm->SetTopLeft(myPm->Left(), myPm->Top() + V);
				myPm->SetHeight(myPm->GetHeight() - V);
				if (myPm->Top() >= SELFPM_Y + 130)
					state = endDialog;
			}
			textCount = 0;
			break;
		case endDialog:
			isAnime = false;
			if (myPm->GetRemainHP() <= 0) {
				if (textCount == 0)
					outcomeText.SetText(myPm->GetName() + " was defeated");
				else {
					if (self->GetAliveNum() > 0) {
						if (textCount == 1) {
							outcomeText.SetText("use next pokemon?");
							if (cursor == yes) 
								atkCursor.SetTopLeft(515, 235);
							else if (cursor == no) 
								atkCursor.SetTopLeft(515, 285);
						}
						else {
							if (cursor == yes) 
								pmMenu->OnMove();
							else  End();
						}
					}
					else  End();
				}
			}
			else {
				if (trainer != nullptr) 
					trainerList.LoadPokemonData(PmType::enemy, trainer->GetPokemons());
				if (trainer != nullptr && textCount == 0 && trainerList.Left() < PMLIST_LEFT_LEFT)
					trainerList.SetTopLeft(trainerList.Left() + V, trainerList.Top());
				if (textCount == 0) 
					if (pokeball != nullptr && dynamic_cast<ItemPokeBall*>(pokeball)->IsCatch()) 
						outcomeText.SetText("capture " + enemy->GetName());
					else 
						outcomeText.SetText(enemy->GetName() + " was defeated");
				else if (textCount <= (int)joinAtkPm.size()) {
					outcomeText.SetText(FindSetFromOrder(joinAtkPm, textCount - 1)->GetName() + " get " +
						to_string(GetAddExp(enemy) / joinAtkPm.size()) + " exp");
				}
				else if (trainer != nullptr && trainer->GetAliveNum() > 0) {
					SetTrainerAtkPm();
					joinAtkPm.insert(myPm);
					outcomeText.SetText(trainer->GetName() + " use " + enemy->GetName());
				}
				if ((!isBattleEnd && trainer == nullptr) || (!isBattleEnd && trainer != nullptr && trainer->GetAliveNum() == 0)) {
					isBattleEnd = true;
					CAudio::Instance()->Stop(AUDIO_BATTLE_START);
					CAudio::Instance()->Stop(AUDIO_BATTLE_PROCESS);
					CAudio::Instance()->Play(AUDIO_BATTLE_END, true);
				}
			}
			break;
		case end:
			int order = textCount - 2;

			if (enemy->GetRemainHP() <= 0) {
				switch (lvupCount) {
				case 0:
					AddExp(order);
					if (!myBar.IsAddExp()) {
						if (FindSetFromOrder(joinAtkPm, order) !=
							((lvupPm.empty()) ? nullptr : *(lvupPm.rbegin()))) {
							if (trainer == nullptr) {
								if ((int)joinAtkPm.size() == order + 1)
									End();
								else
									state = endDialog;
							}
							else {
								if ((int)joinAtkPm.size() == order + 1 && trainer->GetAliveNum() == 0) {		// �̫�@��
									if (trainer != nullptr && trainer->GetAliveNum() > 0)
										state = loadStartStatu;
									else End();
								}
								else state = endDialog;
							}
						}
						else	
							lvupCount = 1;
					}
					break;
				case 1:	
					outcomeText.SetText(FindSetFromOrder(joinAtkPm, order)->GetName() + " level up to "
						 + to_string(FindSetFromOrder(joinAtkPm, order)->GetLevel()));
					break;
				case 2:	
					SetValue(order);
					break;
				case 4:	
					if ((int)joinAtkPm.size() == order + 1) End();
					else {
						lvupCount = 0;
						state = endDialog;
					}
					break;
				}
			}
			else End();
			break;
		}
	}

	void AtkInterface::LoadBitmap()
	{
		black.LoadBitmap(IDB_BLACK);
		myList.LoadBitmap();
		trainerList.LoadBitmap();
		battleBackground.LoadBitmap(IDB_BATTLE_BACKGROUND);
		battleGround[0].LoadBitmap(IDB_BATTLE_GROUND, RGB(255, 0, 0));
		battleGround[1].LoadBitmap(IDB_BATTLE_GROUND, RGB(255, 0, 0));
		battleHero.LoadBitmap(IDB_BATTLE_HERO, RGB(255, 0, 0));
		battleOption.LoadBitmap(IDB_BATTLE_OPTION);
		battleDialog.LoadBitmap(IDB_BATTLE_DIALOG);
		skillOption.LoadBitmap(IDB_SKILL_OPTION);
		atkCursor.LoadBitmap(IDB_CURSOR , RGB(255,0,0));
		ynPanel.LoadBitmap(BG_YESNO);
		lvupPanel.LoadBitmap(IDB_LV_UP_PANEL);
		lvupFpanel.LoadBitmap(IDB_LV_UP_FPANEL);
		myBar.LoadBitmap();
		enemyBar.LoadBitmap();
		outcomeText.LoadBitmap();
		atkText.LoadBitmap();
		atkStatuText.LoadBitmap();
		remainPPText.LoadBitmap();
		allPPText.LoadBitmap();
		skTypeText.LoadBitmap();
		for (int i = 0; i < 6; ++i) {
			valueUpText[i].LoadBitmap();
			valueFinalText[i].LoadBitmap();
		}
	}

	void AtkInterface::Init()
	{
		trainer = nullptr;
		myBar.ReceiveType(barTypeMy);
		myBar.Init();
		enemyBar.ReceiveType(barTypeEnemy);
		enemyBar.Init();
		battleBackground.SetTopLeft(0, 0);
		battleOption.SetTopLeft(0, 340);
		battleDialog.SetTopLeft(0, 340);
		skillOption.SetTopLeft(0, 340);
		ynPanel.SetTopLeft(495, 200);
		lvupPanel.SetTopLeft(LVUP_PANEL_LEFT, LVUP_PANEL_TOP);
		lvupFpanel.SetTopLeft(LVUP_PANEL_LEFT, LVUP_PANEL_TOP);
		outcomeText.SetTopLeft(45, 360);
		atkText.SetTopLeft(45, 360);
		atkStatuText.SetTopLeft(45, 360);
		allPPText.SetTopLeft(ALLPP_LEFT, SKILL_TOP);
		skTypeText.SetTopLeft(SKTYPE_LEFT, SKILL_DOWN);
		for (int i = 0; i < 6; ++i) {
			valueUpText[i].SetTopLeft(LVUP_VALUE_LEFT,
				LVUP_VALUE_TOP + i * LVUP_VALUE_INTERVAL);
		}
	}

	void AtkInterface::ReceivePmMenu(PokemonMenu *pmMenu)
	{
		this->pmMenu = pmMenu;
		this->pmMenu->ReceiveBag(this->bag);
	}

	void AtkInterface::ReceiveBag(Bag * bag)
	{
		this->bag = bag;
	}

	void AtkInterface::ReceiveEnemy(CHero *self, Pokemon *enemy)
	{
		battleGround[0].SetTopLeft(290, 290);
		battleGround[1].SetTopLeft(0, 50);
		battleHero.SetTopLeft(-90, 190);

		isAnime = false;
		state = heroAppear;
		cursor = fight;
		this->self = self;
		this->enemy = enemy;
		SetMyAtkPm();
		myPm->SetTopLeft(-130, SELFPM_Y);
		enemy->SetTopLeft(660, ENEMYPM_Y);
		myBar.ReceiveData(myPm);
		enemyBar.ReceiveData(enemy);
	}

	void AtkInterface::ReceiveTrainer(CHero *self, Trainer *trainer)
	{
		battleGround[0].SetTopLeft(290, 290);
		battleGround[1].SetTopLeft(0, 50);
		battleHero.SetTopLeft(-90, 190);

		isAnime = false;
		state = heroAppear;
		cursor = fight;
		this->self = self;
		this->trainer = trainer;
		battleTrainer = trainer->GetAtkImg();
		battleTrainer->SetTopLeft(740, 10);
		SetTrainerAtkPm();
		SetMyAtkPm();
		myPm->SetTopLeft(-130, SELFPM_Y);
		enemy->SetTopLeft(660, ENEMYPM_Y);
		myBar.ReceiveData(myPm);
		enemyBar.ReceiveData(enemy);
	}

	void AtkInterface::KeyDownListener(UINT nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
		const char KEY_Z = 0x5a;
		const char KEY_X = 0x58;

		if (pmMenu->IsWork()) 
			pmMenu->KeyDownListener(nChar);
		else if (bag->IsWork()) 
			bag->KeyDownListener(nChar);
		switch (state)
		{
		case heroStay:
			if (nChar == KEY_Z)
				state = heroLeave;
			break;
		case pokemonAppear:
			if (nChar == KEY_Z && myPm->Left() >= 110) {
				CAudio::Instance()->Play(AUDIO_SELECT);
				state = loadStartStatu;
			}
			break;
		case action:
			if(nChar == KEY_LEFT || nChar == KEY_RIGHT || nChar == KEY_UP || nChar == KEY_DOWN || nChar == KEY_Z || nChar == KEY_X)
				CAudio::Instance()->Play(AUDIO_SELECT);
			switch (nChar)
			{
			case KEY_LEFT:
				if (cursor == openbag || cursor == escape) 
					cursor -= 1;
				break;
			case KEY_RIGHT:
				if (cursor == fight || cursor == pokemon) 
					cursor += 1;
				break;
			case KEY_UP:
				if (cursor == pokemon || cursor == escape) 
					cursor -= 2;
				break;
			case KEY_DOWN:
				if (cursor == fight || cursor == openbag) 
					cursor += 2;
				break;
			case KEY_Z:
				switch (cursor) {
				case fight:
					state = chooseSkill;
					break;
				case openbag:
					UseItem();
					break;
				case pokemon:
					SltPm();
					break;
				case escape:
					if (trainer == nullptr) {
						CAudio::Instance()->Play(AUDIO_SELECT);
						CAudio::Instance()->Play(AUDIO_ESCAPE);
						End();
					}
					else  cursor = 0;
					break;
				default:
					break;
				}
				cursor = skill1;
				break;
			default:
				break;
			}
			break;
		case chooseSkill:
			if (nChar == KEY_LEFT || nChar == KEY_RIGHT || nChar == KEY_UP || nChar == KEY_DOWN || nChar == KEY_Z || nChar == KEY_X)
				CAudio::Instance()->Play(AUDIO_SELECT);
			switch (nChar)
			{
			case KEY_LEFT:
				if (cursor == skill2 || cursor == skill4) 
					cursor -= 1;
				break;
			case KEY_RIGHT:
				if (cursor == skill1 || cursor == skill3) 
					cursor = (myPm->GetSkillNum() <= (cursor + 1)) ? cursor : (cursor + 1);
				break;
			case KEY_UP:
				if (cursor == skill3 || cursor == skill4) 
					cursor -= 2;
				break;
			case KEY_DOWN:
				if (cursor == skill1 || cursor == skill2) 
					cursor = (myPm->GetSkillNum() <= (cursor + 2)) ? cursor : (cursor + 2);
				break;
			case KEY_Z:
				state = onSkill;
				break;
			case KEY_X:
				state = action;
				break;
			default:
				break;
			}
			break;
		case unCatch:
			if (nChar == KEY_Z) {
				CAudio::Instance()->Play(AUDIO_SELECT);
				state = enemyLoadStartStatu;
			}
			break;
		case endDialog:
			if (nChar == KEY_UP || nChar == KEY_DOWN || nChar == KEY_Z)
				CAudio::Instance()->Play(AUDIO_SELECT);
			switch (nChar) {
			case KEY_UP:
				if (myPm->GetRemainHP() <= 0 && textCount == 1) 
					cursor = yes;
				break;
			case KEY_DOWN:
				if (myPm->GetRemainHP() <= 0 && textCount == 1) 
					cursor = no;
				break;
			case KEY_Z:
				if (myPm->GetRemainHP() <= 0) {
					if (textCount == 0)
						textCount++;
					else if (textCount == 1 && cursor == yes)
						SltPm();
					else if (textCount == 1 && cursor == no) 
						End();
				}
				else if (trainer == nullptr) {
					if (myPm->GetRemainHP() > 0 || textCount != 1) {
						if (textCount > 0) 
							state = end;
						++textCount;
					}
				}
				else {
					if (trainer != nullptr && textCount == 0 && trainerList.Left() < PMLIST_LEFT_LEFT)
						return;
					if (trainer->GetAliveNum() > 0 && textCount > ((int)joinAtkPm.size()) && trainer->GetAliveNum() > 0) 
						state = (trainer->GetAliveNum() > 0) ? loadStartStatu : end;
					else if (trainer->GetAliveNum() > 0 && textCount >= ((int)joinAtkPm.size()) && trainer->GetAliveNum() == 0) 
						state = (trainer->GetAliveNum() > 0) ? loadStartStatu : end;
					else if (trainer->GetAliveNum() <= 0 && textCount > ((int)joinAtkPm.size())) 
						state = (trainer->GetAliveNum() > 0) ? loadStartStatu : end;
					else if ((enemy->GetRemainHP() <= 0 || textCount != 1) && textCount < (int)joinAtkPm.size()) {
						if (textCount > 0) 
							state = end;
						++textCount;
					}
					else 
						textCount++;
				}
				break;
			}
			break;
		case end:
			if (nChar == KEY_Z) {
				CAudio::Instance()->Play(AUDIO_SELECT);
				++lvupCount;
			}
			break;
		}
	}

	void AtkInterface::Start()
	{
		isWork = true;
		isBattleEnd = false;
		delayCount = audioCounter = 0;
		CAudio::Instance()->Stop(AUDIO_GOTOBATTLE);
		CAudio::Instance()->Play(AUDIO_BATTLE_START);
	}

	void AtkInterface::End()
	{
		while (!states.empty()) 
			states.pop();
		if (trainer != nullptr) {
			trainer->SetIsEvent(true);
			trainer = nullptr;
		}
		else {
			delete enemy;
			enemy = nullptr;
		}
		trainer = nullptr;
		isWork = false;
		isAnime = false;
		if (pokeball != nullptr) {
			delete pokeball;
			pokeball = nullptr;
		}
		textCount = 0;
		lvupCount = 0;
		joinAtkPm.clear();
		lvupPm.clear();
		skillText.clear();
		CAudio::Instance()->Stop(AUDIO_BATTLE_START);
		CAudio::Instance()->Stop(AUDIO_BATTLE_PROCESS);
		CAudio::Instance()->Stop(AUDIO_BATTLE_END);
		CAudio::Instance()->Stop(AUDIO_LOW_HP);
		CAudio::Instance()->Play(AUDIO_WEIBAITOWN);
	}

	void AtkInterface::SetMyAtkPm()
	{
		myPm = nullptr;
		skillText.clear();
		for (int i = 0; i < self->GetPmNum(); ++i) {
			if (self->GetPokemon(i)->GetRemainHP() > 0) {
				myPm = self->GetPokemon(i);
				SetSkillText();
				break;
			}
		}
		if (myPm == nullptr)
			End();
		myPm->SetTopLeft(110, SELFPM_Y);
		myList.LoadPokemonData(PmType::my, self->GetPokemons());
		myList.SetTopLeft(PMLIST_RIGHT_LEFT + PMLIST_LEN, PMLIST_RIGHT_TOP);
		joinAtkPm.insert(myPm);
	}

	void AtkInterface::SetTrainerAtkPm()
	{
		enemy = nullptr;
		for (int i = 0; i < trainer->GetPmNum(); ++i) {
			if (trainer->GetPokemon(i)->GetRemainHP() > 0) {
				enemy = trainer->GetPokemon(i);
				break;
			}
		}
		if (enemy == nullptr)
			End();
		enemy->SetTopLeft(ENEMYPM_X, ENEMYPM_Y);
		enemyBar.ReceiveData(enemy);
		trainerList.LoadPokemonData(PmType::enemy, trainer->GetPokemons());
		trainerList.SetTopLeft(PMLIST_LEFT_LEFT - PMLIST_LEN, PMLIST_LEFT_TOP);
		joinAtkPm.clear();
		lvupPm.clear();
	}

	void AtkInterface::SetSkillText()
	{
		for (int i = 0; i < myPm->GetSkillNum(); ++i) {
			CText tmpText;
			tmpText.SetText(myPm->GetSkill(i)->GetName());
			skillText.push_back(tmpText);
			(skillText.back()).LoadBitmap();
			(skillText.back()).SetTopLeft(
				(i == skill1 || i == skill3) ? SKILL_LEFT : SKILL_RIGHT,
				(i == skill1 || i == skill2) ? SKILL_TOP : SKILL_DOWN
			);
		}
	}

	int AtkInterface::GetAddExp(Pokemon *enemy)
	{
		return enemy->GetBasicExp() * enemy->GetLevel() / 7;
	}

	void AtkInterface::AddExp(int order)
	{
		if (!isAnime) {
			value.SetAll(FindSetFromOrder(joinAtkPm, order));
			int addExp = GetAddExp(enemy) / joinAtkPm.size();
			if (FindSetFromOrder(joinAtkPm, order)->AddExp(addExp)) 
				lvupPm.insert(FindSetFromOrder(joinAtkPm, order));
			isAnime = true;
		}
		myBar.OnMove();
	}

	void AtkInterface::SetValue(int order)
	{
		PmValue lvupValue(FindSetFromOrder(joinAtkPm, order)), difValue;
		difValue = lvupValue - value;

		valueUpText[0].SetText(to_string(difValue.hp));
		valueUpText[1].SetText(to_string(difValue.atk));
		valueUpText[2].SetText(to_string(difValue.def));
		valueUpText[3].SetText(to_string(difValue.satk));
		valueUpText[4].SetText(to_string(difValue.sdef));
		valueUpText[5].SetText(to_string(difValue.speed));

		valueFinalText[0].SetText(to_string(lvupValue.hp));
		valueFinalText[1].SetText(to_string(lvupValue.atk));
		valueFinalText[2].SetText(to_string(lvupValue.def));
		valueFinalText[3].SetText(to_string(lvupValue.satk));
		valueFinalText[4].SetText(to_string(lvupValue.sdef));
		valueFinalText[5].SetText(to_string(lvupValue.speed));

		for (int i = 0; i < 6; ++i) {
			valueFinalText[i].SetTopLeft(LVUP_VALUE_RIGHT - 
				valueFinalText[i].GetLength() * (int)valueFinalText[i].GetFontSize(), 
				LVUP_VALUE_TOP + i * LVUP_VALUE_INTERVAL);
		}
	}

	void AtkInterface::UseItem()
	{
		state = chooseItem;
		bag->Start();
		pmMenu->ReceiveData(self->GetPokemons());
		bag->RecievePokemonMenu(pmMenu);
		bag->SetBattleMode();
	}

	void AtkInterface::SltPm()
	{
		state = choosePokemon;
		pmMenu->Start();
		pmMenu->ChangeOnAtk();
		pmMenu->ReceiveData(self->GetPokemons());
	}

	void AtkInterface::SetCursorPosition(int cursor, State state)
	{
		switch (cursor) {
		case 0:
			if (state == action || state == onSkill || state == onEnemySkill || state == loadStartStatu) 
				atkCursor.SetTopLeft(380, 375);
			else 
				atkCursor.SetTopLeft(20, 375);
			break;
		case 1:
			if (state == action || state == onSkill || state == onEnemySkill || state == loadStartStatu)
				atkCursor.SetTopLeft(505, 375);
			else 
				atkCursor.SetTopLeft(190, 375);
			break;
		case 2:
			if (state == action || state == onSkill || state == onEnemySkill || state == loadStartStatu)
				atkCursor.SetTopLeft(380, 425);
			else 
				atkCursor.SetTopLeft(20, 425);
			break;
		case 3:
			if (state == action || state == onSkill || state == onEnemySkill || state == loadStartStatu)
				atkCursor.SetTopLeft(505, 425);
			else 
				atkCursor.SetTopLeft(190, 425);
			break;
		}
	}
}