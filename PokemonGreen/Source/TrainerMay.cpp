#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Trainer.h"
#include "CHero.h"
#include "TrainerMay.h"
#include "PokemonFactory.h"

namespace game_framework
{
	TrainerMay::TrainerMay(AtkInterface *atkInterface) :
		Trainer(atkInterface)
	{
		// set position
		x = 102;
		y = 15;

		// set pokemons
		PokemonFactory pmf;
		pokemons.push_back(pmf.CreateEnemy(treecko, 6));
		pokemons.push_back(pmf.CreateEnemy(hooh, 7));

		// set name and map
		name = "may";
		map = "weibai";
		type = walker;

		// set direction
		direction = right;

		// set dialog
		normalDialog.InitDialog('n');
		normalDialog.AddText("hey boy");
		normalDialog.AddText("my name is may");
		normalDialog.AddText("lets battle");
		atkDialogCounter = 2;
		normalDialog.AddText("damn it");

		eventDialog.InitDialog('n');
		eventDialog.AddText("you are pretty strong");

		// set prize
		prize = 69;
	}

	void TrainerMay::KeyDownListener(UINT nChar, CHero &hero)
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
			if (!isEvent) {
				// set dialog order trigger event
				if (normalDialog.GetCurrentTextNumber() < atkDialogCounter)
					normalDialog.Next();
				else if (normalDialog.GetCurrentTextNumber() == atkDialogCounter) {
					StartAtk(&hero, this, *atkInterface);
				}

				// assessment whether dialog is end
				if (normalDialog.IsEnd()){
					StopTalk(hero);
				}
			}
			else {
				eventDialog.Next();

				if (eventDialog.IsEnd()) {
					StopTalk(hero);
					hero.SetGameEvent(winMay, true);
				}
			}
		}
	}

	void TrainerMay::LoadBitmap()
	{
		normalImg[down].LoadBitmap(IDB_MAY_FRONT, RGB(255, 0, 0));
		normalImg[left].LoadBitmap(IDB_MAY_LEFT, RGB(255, 0, 0));
		normalImg[up].LoadBitmap(IDB_MAY_BACK, RGB(255, 0, 0));
		normalImg[right].LoadBitmap(IDB_MAY_RIGHT, RGB(255, 0, 0));
		atkImg.LoadBitmap(IDB_MAY_ATK, RGB(255, 0, 0));
	}

	void TrainerMay::OnShow(CHero &hero)
	{
		int hx = hero.GetX1() / SM;
		int hy = hero.GetY1() / SM;
		if (abs(hx - x) <= 9 && abs(hy - y) <= 9) {
			SetTopLeft(hero.GetX1(), hero.GetY1());
			normalImg[direction].ShowBitmap();
		}
		if (IsTalk()) {
			if (!isEvent)
				normalDialog.OnShow();
			else
				eventDialog.OnShow();
		}
	}

	void TrainerMay::ReShow(CHero &hero)
	{
		int hx = hero.GetX1() / SM;
		int hy = (hero.GetY1() + 20) / SM;
		if (abs(hx - x) <= 9 && abs(hy - y) <= 9 && hy <= y) {
			SetTopLeft(hero.GetX1(), hero.GetY1());
			normalImg[direction].ShowBitmap();
		}
		if (IsTalk()) {
			if (!isEvent)
				normalDialog.OnShow();
			else
				eventDialog.OnShow();
		}
	}

	void TrainerMay::OnMove(CHero &hero)
	{
		if (!IsTalk() && !isEvent && IsDiscoverHero(hero) &&
			(hero.GetSpeed() == STEP_SIZE && hero.GetCount() == 12 ||
			hero.GetSpeed() == STEP_SIZE * 2 && hero.GetCount() == 6)) {
			Talk(hero);
		}
	}

	// private

	void TrainerMay::Talk(CHero &hero)
	{
		isTalk = true;
		hero.SetCanMove(false);

		int hx = hero.GetX1() / SM;
		int hy = (hero.GetY1() + 20) / SM;
		if (hx != x)
			direction = (hx < x) ? left : right;
		else if (hy != y)
			direction = (hy < y) ? up : down;
	}

	void TrainerMay::SetTopLeft(int hx, int hy)
	{
		int dx = x * SM - hx;
		int dy = y * SM - hy;
		normalImg[direction].SetTopLeft(HERO_X + dx, HERO_Y + dy);
	}
}