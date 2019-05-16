#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Trainer.h"
#include "CHero.h"
#include "CharMay.h"
#include "PokemonFactory.h"

namespace game_framework
{
	CharMay::CharMay(AtkInterface *atkInterface) :
		Trainer(atkInterface)
	{
		// set position
		x = 27;
		y = 65;

		// set pokemons
		PokemonFactory pmf;
		pokemons.push_back(pmf.CreateEnemy(treecko, 6));
		pokemons.push_back(pmf.CreateEnemy(hooh, 7));

		// set name
		name = "may";

		// set direction
		direction = up;

		// set dialog
		unLoseDialog.InitDialog('n');
		unLoseDialog.AddText("hey boy");
		unLoseDialog.AddText("my name is may");
		unLoseDialog.AddText("lets battle");
		atkDialogCounter = 2;
		unLoseDialog.AddText("damn it");

		loseDialog.InitDialog('n');
		loseDialog.AddText("you are pretty strong");

		// set prize
		prize = 69;
	}

	void CharMay::KeyDownListener(UINT nChar, CHero &hero)
	{
		const char KEY_Z = 0x5a;

		if (!IsTalk() && nChar == KEY_Z && IsBeTalked(hero)) {
			Talk(hero);
			return;
		}
		else if (!IsTalk())
			return;

		switch (nChar) {
		case KEY_Z:
			if (!isLose) {
				// set dialog order trigger event
				if (unLoseDialog.GetCurrentTextNumber() < atkDialogCounter)
					unLoseDialog.Next();
				else if (unLoseDialog.GetCurrentTextNumber() == atkDialogCounter)
					StartAtk(&hero, this, *atkInterface);
				else
					unLoseDialog.Next();

				// assessment whether dialog is end
				if (unLoseDialog.IsEnd())
					StopTalk();
			}
			else {
				loseDialog.Next();

				if (loseDialog.IsEnd())
					StopTalk();
			}
		}
	}

	void CharMay::LoadBitmap()
	{
		normalImg[down].LoadBitmap(IDB_MAY_FRONT, RGB(255, 0, 0));
		normalImg[left].LoadBitmap(IDB_MAY_LEFT, RGB(255, 0, 0));
		normalImg[up].LoadBitmap(IDB_MAY_BACK, RGB(255, 0, 0));
		normalImg[right].LoadBitmap(IDB_MAY_RIGHT, RGB(255, 0, 0));
		atkImg.LoadBitmap(IDB_MAY_ATK, RGB(255, 0, 0));
	}

	void CharMay::OnShow(CHero &hero)
	{
		int hx = hero.GetX1() / SM;
		int hy = hero.GetY1() / SM;
		if (abs(hx - x) <= 9 && abs(hy - y) <= 9) {
			SetTopLeft(hero.GetX1(), hero.GetY1());
			normalImg[direction].ShowBitmap();
		}
		if (IsTalk()) {
			if (!isLose)
				unLoseDialog.OnShow();
			else
				loseDialog.OnShow();
		}
	}

	void CharMay::OnMove()
	{
		// empty body
	}

	// private

	void CharMay::Talk(CHero &hero)
	{
		isTalk = true;
		direction = (hero.GetDirection() % 2 == 0) ? 
			hero.GetDirection() + 1 : hero.GetDirection() - 1;
		
		// atkinterface receive data
	}

	void CharMay::SetTopLeft(int hx, int hy)
	{
		int dx = x * SM - hx;
		int dy = y * SM - hy;
		normalImg[direction].SetTopLeft(HERO_X + dx, HERO_Y + dy);
	}
}