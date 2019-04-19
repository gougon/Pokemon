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
		: self(nullptr), enemy(nullptr), isAtk(false)
	{
		/* empty body */
	}

	void AtkInterface::Start()
	{
		isAtk = true;
	}

	void AtkInterface::OnShow()
	{
		Pokemon *mypm = self->GetPokemon(0);
		battleBackground.ShowBitmap();
		switch (state)
		{
		/*case openAnime:
			black.ShowBitmap();
			Sleep(1000);*/
		case heroAppear:
			battleGround[0].ShowBitmap();
			battleGround[1].ShowBitmap();
			battleHero.ShowBitmap();
			battleDialog.ShowBitmap();
			break;
		case heroLeave:
			battleGround[0].ShowBitmap();
			battleGround[1].ShowBitmap();
			battleHero.ShowBitmap();
			battleDialog.ShowBitmap();
			break;
		case pokemonAppear:
			battleGround[0].ShowBitmap();
			battleGround[1].ShowBitmap();
			mypm->OnShow();
			enemy->OnShow();
			battleDialog.ShowBitmap();
			// atk option appear
			break;
		case action:
			battleGround[0].ShowBitmap();
			battleGround[1].ShowBitmap();
			mypm->OnShow();
			enemy->OnShow();
			battleOption.ShowBitmap();
			atkCursor.ShowBitmap();
			myBar.OnShow();
			enemyBar.OnShow();
			break;
		case chooseSkill:
			battleGround[0].ShowBitmap();
			battleGround[1].ShowBitmap();
			mypm->OnShow();
			enemy->OnShow();
			skillOption.ShowBitmap(); 
			atkCursor.ShowBitmap();
			myBar.OnShow();
			enemyBar.OnShow();
			break;
		case onSkill:
			battleGround[0].ShowBitmap();
			battleGround[1].ShowBitmap();
			mypm->OnShow();
			enemy->OnShow();
			(mypm->GetSkill(cursor))->AtkAnimeOnShow();
			skillOption.ShowBitmap(); // 應該要跑對話
			enemyBar.OnShow();
			myBar.OnShow();
			break;
		case onEnemySkill:
			battleGround[0].ShowBitmap();
			battleGround[1].ShowBitmap();
			mypm->OnShow();
			enemy->OnShow();
			(enemy->GetSkill(enemySkill))->AtkAnimeOnShow();
			skillOption.ShowBitmap(); // 應該要跑對話
			myBar.OnShow();
			enemyBar.OnShow();
			break;
		case endAnime:
			battleGround[0].ShowBitmap();
			battleGround[1].ShowBitmap();
			mypm->OnShow("atk");
			enemy->OnShow("atk");
			battleDialog.ShowBitmap();
			myBar.OnShow();
			enemyBar.OnShow();
			break;
		case end:
			battleGround[0].ShowBitmap();
			battleGround[1].ShowBitmap();
			if (mypm->GetRemainHP() > 0) {
				mypm->OnShow();
			}
			else {
				enemy->OnShow();
			}
			battleDialog.ShowBitmap();
			myBar.OnShow();
			enemyBar.OnShow();
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	void AtkInterface::OnMove()
	{
		constexpr auto V = 10;
		Pokemon *mypm = self->GetPokemon(0);
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
			mypm->SetTopLeft(mypm->Left() + V, SELFPM_Y);
			enemy->SetTopLeft(enemy->Left() - V, ENEMYPM_Y);
			enemyBar.OnMove(enemy);
			myBar.OnMove(mypm);
			if (mypm->Left() == 110)
				state = action;
			break;
		case action:
			switch (cursor)
			{
			case fight:
				atkCursor.SetTopLeft(380, 375);
				break;
			case bag:
				atkCursor.SetTopLeft(505, 375);
				break;
			case pokemon:
				atkCursor.SetTopLeft(380, 425);
				break;
			case escape:
				atkCursor.SetTopLeft(505, 425);
				break;
			default:
				ASSERT(0);
				break;
			}
			break;
		case chooseSkill:
			TRACE("\nmy pm hp = %d, ene pm hp = %d\n", mypm->GetRemainHP(), enemy->GetRemainHP());
			switch (cursor)
			{
			case skill1:
				atkCursor.SetTopLeft(20, 375);
				break;
			case skill2:
				atkCursor.SetTopLeft(190, 375);
				break;
			case skill3:
				atkCursor.SetTopLeft(20, 425);
				break;
			case skill4:
				atkCursor.SetTopLeft(190, 425);
				break;
			default:
				TRACE("assert! AtkInterface onMove's function chooseskill");
				ASSERT(0);
				break;
			}
			break;
		case onSkill:
			if (!isAnime) {
				(mypm->GetSkill(cursor))->Use(mypm, enemy);
				isAnime = true;
			}
			// enemy->HpAnime();
			// mypm->HpAnime();
			enemyBar.OnMove(enemy);
			myBar.OnMove(mypm);
			if ((mypm->GetSkill(cursor))->AtkAnimeOnMove()) {
				state = (enemy->GetRemainHP() == 0 || mypm->GetRemainHP() == 0) ? endAnime : onEnemySkill;
				enemySkill = 0; // rand % 4
				isAnime = false;
			}
			break;
		case onEnemySkill:
			if (!isAnime) {
				(enemy->GetSkill(enemySkill))->Use(enemy, mypm);
				isAnime = true;
			}
			myBar.OnMove(mypm);
			enemyBar.OnMove(enemy);
			if ((enemy->GetSkill(enemySkill))->AtkAnimeOnMove()) {
				state = (enemy->GetRemainHP() <= 0 || mypm->GetRemainHP() <= 0) ? endAnime : action;
				cursor = fight;
				isAnime = false;
			}
			break;
		case endAnime:
			if (enemy->GetRemainHP() <= 0) {
				enemy->SetTopLeft(enemy->Left(), enemy->Top() + V);
				enemy->SetHeight(enemy->GetHeight() - V);
				if (enemy->Top() >= ENEMYPM_Y + 130) {
					state = end;
				}
			}
			else {
				mypm->SetTopLeft(mypm->Left(), mypm->Top() + V);
				mypm->SetHeight(mypm->GetHeight() - V);
				if (mypm->Top() >= SELFPM_Y + 130) {
					state = end;
				}
			}
			break;
		case end:
			if (enemy->GetRemainHP() <= 0) {
				if (!isAnime) {
					mypm->AddExp(enemy);
					isAnime = true;
				}
				myBar.OnMove(mypm);
				// end atk ...
				isAtk = myBar.IsAddExp();
			}
			else {
				// Dead(self);
				isAtk = false;
			}
			// black.ShowBitmap();
			// Sleep(1000);
			break;
		default:
			ASSERT(0);
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
		atkCursor.LoadBitmap(IDB_ATK_CURSOR);
		myBar.LoadBitmap();
		enemyBar.LoadBitmap();
	}

	void AtkInterface::Init(CHero *self, Pokemon *enemy)
	{
		isAtk = false;
		isAnime = false;
		state = heroAppear;
		cursor = fight;
		this->self = self;
		this->enemy = enemy;

		// black.SetTopLeft(0, 0);
		battleBackground.SetTopLeft(0, 0);
		battleGround[0].SetTopLeft(290, 290);
		battleGround[1].SetTopLeft(0, 50);
		battleHero.SetTopLeft(200, 190);
		battleOption.SetTopLeft(0, 340);
		battleDialog.SetTopLeft(0, 340);
		skillOption.SetTopLeft(0, 340);
		(self->GetPokemon(0))->SetTopLeft(-130, SELFPM_Y);
		enemy->SetTopLeft(660, ENEMYPM_Y);
		myBar.Init(barTypeMy);
		enemyBar.Init(barTypeEnemy);
	}

	void AtkInterface::KeyDownListener(UINT nChar)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_Z = 0x5a;

		Pokemon *mypm = self->GetPokemon(0);
		switch (state)
		{
		case action:
			switch (nChar)
			{
			case KEY_LEFT:
				switch (cursor)
				{
				case bag:
					cursor = fight;
					break;
				case escape:
					cursor = pokemon;
					break;
				default:
					break;
				}
				break;
			case KEY_RIGHT:
				switch (cursor)
				{
				case fight:
					cursor = bag;
					break;
				case pokemon:
					cursor = escape;
					break;
				default:
					break;
				}
				break;
			case KEY_UP:
				switch (cursor)
				{
				case pokemon:
					cursor = fight;
					break;
				case escape:
					cursor = bag;
					break;
				default:
					break;
				}
				break;
			case KEY_DOWN:
				switch (cursor)
				{
				case fight:
					cursor = pokemon;
					break;
				case bag:
					cursor = escape;
					break;
				default:
					break;
				}
				break;
			case KEY_Z:
				switch (cursor)
				{
				case fight:
					cursor = skill1;
					break;
				case escape:
					cursor = skill1;
					isAtk = false;
					break;
				default:
					cursor = skill1;
					break;
				}
				state = chooseSkill;
				break;
			default:
				break;
			}
			break;
		case chooseSkill:
			switch (nChar)
			{
			case KEY_LEFT:
				switch (cursor)
				{
				case skill2:
					cursor = skill1;
					break;
				case skill4:
					cursor = skill3;
					break;
				default:
					break;
				}
				break;
			case KEY_RIGHT:
				switch (cursor)
				{
				case skill1:
					cursor = (mypm->GetSkillNum() < 2) ? cursor : skill2;
					break;
				case skill3:
					cursor = (mypm->GetSkillNum() < 4) ? cursor : skill4;
					break;
				default:
					break;
				}
				break;
			case KEY_UP:
				switch (cursor)
				{
				case skill3:
					cursor = skill1;
					break;
				case skill4:
					cursor = skill2;
					break;
				default:
					break;
				}
				break;
			case KEY_DOWN:
				switch (cursor)
				{
				case skill1:
					cursor = (mypm->GetSkillNum() < 3) ? cursor : skill3;
					break;
				case skill2:
					cursor = (mypm->GetSkillNum() < 4) ? cursor : skill4;
					break;
				default:
					break;
				}
				break;
			case KEY_Z:
				state = onSkill;
				break;
			default:
				break;
			}
			break;
		}
	}

	bool AtkInterface::IsAtk()
	{
		return isAtk;
	}
}