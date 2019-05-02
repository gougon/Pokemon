#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <windows.h>
#include "AtkInterface.h"

namespace game_framework {
	AtkInterface::AtkInterface()
		: self(nullptr), enemy(nullptr), isAtk(false), textCount(0), lvupCount(0)
	{
		/* empty body */
	}

	void AtkInterface::Start()
	{
		isAtk = true;
	}

	void AtkInterface::OnShow()
	{
		battleBackground.ShowBitmap();
		battleGround[0].ShowBitmap();
		battleGround[1].ShowBitmap();
		switch (state)
		{
		/*case openAnime:
			black.ShowBitmap();
			Sleep(1000);*/
		case heroAppear:
			battleHero.ShowBitmap();
			battleDialog.ShowBitmap();
			break;
		case heroLeave:
			battleHero.ShowBitmap();
			battleDialog.ShowBitmap();
			break;
		case pokemonAppear:
			myPm->OnShow();
			enemy->OnShow();
			battleDialog.ShowBitmap();
			atkText.OnShow();
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
			for (auto i : skillText) {
				i.OnShow();
			}
			break;
		case choosePokemon:
			pmMenu->OnShow();
			break;
		case chooseItem:
			// pmBag->OnShow();
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
		case onEnemySkill:
			myPm->OnShow();
			enemy->OnShow();
			(enemy->GetSkill(enemySkill))->AtkAnimeOnShow();
			myBar.OnShow();
			enemyBar.OnShow();
			battleDialog.ShowBitmap();
			atkText.OnShow();
			break;
		case atkStatu:
			myPm->OnShow();
			enemy->OnShow();
			myBar.OnShow();
			enemyBar.OnShow();
			battleDialog.ShowBitmap();
			atkStatuText.OnShow();
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
			if (pmMenu->IsWork()) {
				pmMenu->OnShow();
			}
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
			break;
		case end:
			if (myPm->GetRemainHP() > 0) {
				myPm->OnShow();
			}
			else {
				enemy->OnShow();
			}
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
					for (int i = 0; i < 6; ++i) {
						valueUpText[i].OnShow();
					}
					break;
				case 3:
					lvupFpanel.ShowBitmap();
					for (int i = 0; i < 6; ++i) {
						valueFinalText[i].OnShow();
					}
					break;
				}
			}
			// enemyBar.OnShow();
			break;
		}
	}

	void AtkInterface::OnMove()
	{
		constexpr auto V = 10;
		switch (state)
		{
		/*case openAnime:
			if (++openCount == 2)
				state = heroAppear;
			black.SetTopLeft(0, 0);
			break;*/
		case heroAppear:
			battleGround[0].SetTopLeft(battleGround[0].Left() - V, battleGround[0].Top());
			battleGround[1].SetTopLeft(battleGround[1].Left() + V, battleGround[1].Top());
			if (battleGround[0].Left() == 0) 
				state = heroLeave;
			break;
		case heroLeave:
			battleGround[0].SetTopLeft(battleGround[0].Left(), battleGround[0].Top());
			battleGround[1].SetTopLeft(battleGround[1].Left(), battleGround[1].Top());
			battleHero.SetTopLeft(battleHero.Left() - V, battleHero.Top());
			if (battleHero.Left() == -130)
				state = pokemonAppear;
			break;
		case pokemonAppear:
			if (myPm->Left() != 110) {
				myPm->SetTopLeft(myPm->Left() + V, SELFPM_Y);
				enemy->SetTopLeft(enemy->Left() - V, ENEMYPM_Y);
			}
			enemyBar.OnMove(enemy);
			myBar.OnMove(myPm);
			atkText.SetText(enemy->GetName() + " appeared");
			break;
		case action:
			enemyBar.OnMove(enemy);
			myBar.OnMove(myPm);
			SetCursorPosition(cursor, state);
			break;
		case chooseSkill:
			remainPPText.SetText(to_string(myPm->GetSkill(cursor)->GetRemainPP()));
			allPPText.SetText(to_string(myPm->GetSkill(cursor)->GetAllPP()));
			skTypeText.SetText(myPm->GetSkill(cursor)->GetAttributeText());
			remainPPText.SetTopLeft(REMAINPP_RIGHT - remainPPText.GetLength() * (int)remainPPText.GetFontSize(), 
				SKILL_TOP);
			SetCursorPosition(cursor, state);
			break;
		case choosePokemon:
			if (pmMenu->IsWork()) {
				pmMenu->OnMove();
			}
			else {
				SetAtkPm();
				myBar.ReceivePm(myPm);
				state = action;
			}
			break;
		case chooseItem:
			// pmBag->OnMove();
			break;
		case onSkill:
			atkText.SetText(myPm->GetName() + " use " + myPm->GetSkill(cursor)->GetName());
			if (!isAnime) {
				atkStatuTemp = (myPm->GetSkill(cursor))->Use(myPm, enemy);
				atkStatuText.SetText(atkStatuTemp);
				isAnime = true;
			}
			enemyBar.OnMove(enemy);
			myBar.OnMove(myPm);
			if ((myPm->GetSkill(cursor))->AtkAnimeOnMove()) {
				if (atkStatuTemp == "") {
					state = (enemy->GetRemainHP() == 0 || myPm->GetRemainHP() == 0) ? endAnime : onEnemySkill;
				}
				else {
					states.push(state);
					state = atkStatu;
				}
				enemySkill = 0; // rand % 4
				isAnime = false;
			}
			SetCursorPosition(cursor, state);
			break;
		case onEnemySkill:
			atkText.SetText(enemy->GetName() + " use " + enemy->GetSkill(enemySkill)->GetName());
			if (!isAnime) {
				atkStatuTemp = (enemy->GetSkill(enemySkill))->Use(enemy, myPm);
				atkStatuText.SetText(atkStatuTemp);
				isAnime = true;
			}
			myBar.OnMove(myPm);
			enemyBar.OnMove(enemy);
			if ((enemy->GetSkill(enemySkill))->AtkAnimeOnMove()) {
				if (atkStatuTemp == "") {
					state = (enemy->GetRemainHP() <= 0 || myPm->GetRemainHP() <= 0) ? endAnime : action;
				}
				else {
					states.push(state);
					state = atkStatu;
				}
				cursor = fight;
				isAnime = false;
			}
			SetCursorPosition(cursor, state);
			break;
		case endAnime:
			if (enemy->GetRemainHP() <= 0) {
				enemy->SetTopLeft(enemy->Left(), enemy->Top() + V);
				enemy->SetHeight(enemy->GetHeight() - V);
				if (enemy->Top() >= ENEMYPM_Y + 130) {
					state = endDialog;
				}
			}
			else {
				myPm->SetTopLeft(myPm->Left(), myPm->Top() + V);
				myPm->SetHeight(myPm->GetHeight() - V);
				if (myPm->Top() >= SELFPM_Y + 130) {
					state = endDialog;
				}
			}
			textCount = 0;
			break;
		case endDialog:
			if (myPm->GetRemainHP() <= 0) {
				if (textCount == 0) {
					outcomeText.SetText(myPm->GetName() + " was defeated");
				}
				else {
					if (self->GetAliveNum() > 0) {
						if (textCount == 1) {
							outcomeText.SetText("use next pokemon?");
							if (cursor == yes) {
								atkCursor.SetTopLeft(515, 235);
							}
							else if (cursor == no) {
								atkCursor.SetTopLeft(515, 285);
							}
						}
						else {
							if (cursor == yes) {
								pmMenu->OnMove();
							}
							else {
								End();
							}
						}
					}
					else {
						End();
					}
				}
			}
			else {
				if (textCount == 0) {
					outcomeText.SetText(enemy->GetName() + " was defeated");
				}
				else {
					outcomeText.SetText(FindSetFromOrder(joinAtkPm, textCount - 1)->GetName() + " get " +
						to_string(GetAddExp(enemy) / joinAtkPm.size()) + " exp");
				}
			}
			break;
		case end:
			int order = textCount - 2;

			if (enemy->GetRemainHP() <= 0) {
				switch (lvupCount) {
				case 0:
					AddExp(order);
					if (!myBar.IsAddExp()) {		// 經驗值動畫結束
						if (FindSetFromOrder(joinAtkPm, order) !=			// 不需要升等
							((lvupPm.empty()) ? nullptr : *(lvupPm.rbegin()))) {
							if ((int)joinAtkPm.size() == order + 1) {		// 最後一隻
								End();
							}
							else {
								state = endDialog;
							}
						}
						else {		// 需要升等
							lvupCount = 1;
						}
					}
					break;
				case 1:			// 已確定要升等，顯示升等文字
					outcomeText.SetText(FindSetFromOrder(joinAtkPm, order)->GetName() + ";" +
						"level up to " + to_string(FindSetFromOrder(joinAtkPm, order)->GetLevel()));
					break;
				case 2:			// 設定升等屬性提升面板
					SetValue(order);
					break;
				case 4:			// 升等面板結束
					if ((int)joinAtkPm.size() == order + 1) {		// 最後一隻
						End();
					}
					else {			// 不是最後一隻要回dialog
						state = endDialog;
					}
					break;
				}
			}
			else {
				// Dead(self);
				End();
			}
			break;
		}
	}

	void AtkInterface::LoadBitmap()
	{
		black.LoadBitmap(IDB_BLACK);
		battleBackground.LoadBitmap(IDB_BATTLE_BACKGROUND);
		battleGround[0].LoadBitmap(IDB_BATTLE_GROUND, RGB(255, 0, 0));
		battleGround[1].LoadBitmap(IDB_BATTLE_GROUND, RGB(255, 0, 0));
		battleHero.LoadBitmap(IDB_BATTLE_HERO, RGB(255, 0, 0));
		battleOption.LoadBitmap(IDB_BATTLE_OPTION);
		battleDialog.LoadBitmap(IDB_BATTLE_DIALOG);
		skillOption.LoadBitmap(IDB_SKILL_OPTION);
		atkCursor.LoadBitmap(BG_BACKPACK_ITEMCURSOR);
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

	void AtkInterface::Init(PokemonMenu *pmMenu)
	{
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

		this->pmMenu = pmMenu;
	}

	void AtkInterface::ReceiveData(CHero *self, Pokemon *enemy)
	{
		battleGround[0].SetTopLeft(290, 290);
		battleGround[1].SetTopLeft(0, 50);
		battleHero.SetTopLeft(200, 190);

		isAnime = false;
		state = heroAppear;
		cursor = fight;
		this->self = self;
		this->enemy = enemy;
		SetAtkPm();
		myPm->SetTopLeft(-130, SELFPM_Y);
		enemy->SetTopLeft(660, ENEMYPM_Y);
		myBar.Init(barTypeMy);
		enemyBar.Init(barTypeEnemy);
		myBar.ReceivePm(myPm);
		enemyBar.ReceivePm(enemy);
	}

	void AtkInterface::KeyDownListener(UINT nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_Z = 0x5a;
		const char KEY_X = 0x58;

		if (pmMenu->IsWork()) {
			pmMenu->KeyDownListener(nChar);
		}
		switch (state)
		{
		case pokemonAppear:
			if (myPm->Left() == 110 && nChar == KEY_Z) {
				state = action;
			}
			break;
		case action:
			switch (nChar)
			{
			case KEY_LEFT:
				if (cursor == bag || cursor == escape) {
					cursor -= 1;
				}
				break;
			case KEY_RIGHT:
				if (cursor == fight || cursor == pokemon) {
					cursor += 1;
				}
				break;
			case KEY_UP:
				if (cursor == pokemon || cursor == escape) {
					cursor -= 2;
				}
				break;
			case KEY_DOWN:
				if (cursor == fight || cursor == bag) {
					cursor += 2;
				}
				break;
			case KEY_Z:
				switch (cursor) {
				case fight:
					state = chooseSkill;
					break;
				case bag:
					state = chooseItem;
					// pmBag->UseOnAtk();
					break;
				case pokemon:
					SltPm();
					break;
				case escape:
					End();
					break;
				default:
					ASSERT(0);
					break;
				}
				cursor = skill1;
				break;
			default:
				break;
			}
			break;
		case chooseSkill:
			switch (nChar)
			{
			case KEY_LEFT:
				if (cursor == skill2 || cursor == skill4) {
					cursor -= 1;
				}
				break;
			case KEY_RIGHT:
				if (cursor == skill1 || cursor == skill3) {
					// TRACE("\nskillnum = %d\n", myPm->GetSkillNum());
					cursor = (myPm->GetSkillNum() <= (cursor + 1)) ? cursor : (cursor + 1);
				}
				break;
			case KEY_UP:
				if (cursor == skill3 || cursor == skill4) {
					cursor -= 2;
				}
				break;
			case KEY_DOWN:
				if (cursor == skill1 || cursor == skill2) {
					cursor = (myPm->GetSkillNum() <= (cursor + 2)) ? cursor : (cursor + 2);
				}
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
		case atkStatu:
			switch (nChar) {
			case KEY_Z:
				if (states.top() == onSkill) {
					state = (enemy->GetRemainHP() == 0 || myPm->GetRemainHP() == 0) ? endAnime : onEnemySkill;
				}
				else {
					state = (enemy->GetRemainHP() <= 0 || myPm->GetRemainHP() <= 0) ? endAnime : action;
				}
				break;
			}
			break;
		case endDialog:
			switch (nChar) {
			case KEY_UP:
				if (myPm->GetRemainHP() <= 0 && textCount == 1) {
					cursor = yes;
				}
				break;
			case KEY_DOWN:
				if (myPm->GetRemainHP() <= 0 && textCount == 1) {
					cursor = no;
				}
				break;
			case KEY_Z:
				if (myPm->GetRemainHP() <= 0) {
					if (textCount == 1 && cursor == yes) {
						SltPm();
					}
					else if (textCount == 1 && cursor == no) {
						End();
					}
				}
				if (myPm->GetRemainHP() > 0 || textCount != 1) {
					if (textCount > 0) {
						state = end;
					}
					++textCount;
				}
				break;
			}
			break;
		case end:
			switch (nChar) {
			case KEY_Z:
				++lvupCount;
				if (lvupCount == 3 && textCount < (int)joinAtkPm.size()) {
					lvupCount = 0;
					state = endDialog;
				}
				break;
			}
			break;
		}
	}

	void AtkInterface::End()
	{
		while (!states.empty()) {
			states.pop();
		}
		isAtk = false;
		isAnime = false;
		textCount = 0;
		lvupCount = 0;
		joinAtkPm.clear();
		lvupPm.clear();
		skillText.clear();
	}

	bool AtkInterface::IsAtk()
	{
		return isAtk;
	}

	void AtkInterface::SetAtkPm()
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
		if (myPm == nullptr) {
			End();
		}
		myPm->SetTopLeft(110, SELFPM_Y);
		joinAtkPm.insert(myPm);
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
			if (FindSetFromOrder(joinAtkPm, order)->AddExp(addExp)) {
				lvupPm.insert(FindSetFromOrder(joinAtkPm, order));
			}
			isAnime = true;
		}
		myBar.OnMove(myPm);
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
			if (state == action || state == onSkill || state == onEnemySkill) {
				atkCursor.SetTopLeft(380, 375);
			}
			else {
				atkCursor.SetTopLeft(20, 375);
			}
			break;
		case 1:
			if (state == action || state == onSkill || state == onEnemySkill) {
				atkCursor.SetTopLeft(505, 375);
			}
			else {
				atkCursor.SetTopLeft(190, 375);
			}
			break;
		case 2:
			if (state == action || state == onSkill || state == onEnemySkill) {
				atkCursor.SetTopLeft(380, 425);
			}
			else {
				atkCursor.SetTopLeft(20, 425);
			}
			break;
		case 3:
			if (state == action || state == onSkill || state == onEnemySkill) {
				atkCursor.SetTopLeft(505, 425);
			}
			else {
				atkCursor.SetTopLeft(190, 425);
			}
			break;
		}
	}

	Pokemon *AtkInterface::FindSetFromOrder(set<Pokemon*>& lhs, int order)
	{
		int i = 0;
		for (auto it : lhs) {
			if (i == order) {
				return it;
			}
			++i;
		}
		return NULL;
	}
}