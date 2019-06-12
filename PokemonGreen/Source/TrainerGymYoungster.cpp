#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Trainer.h"
#include "CHero.h"
#include "TrainerGymYoungster.h"
#include "PokemonFactory.h"

namespace game_framework
{
	TrainerGymYoungster::TrainerGymYoungster(AtkInterface *atkInterface) :
		Trainer(atkInterface)
	{
		// set position
		x = 23;
		y = 29;

		// set pokemons
		PokemonFactory pmf;
		pokemons.push_back(pmf.CreateEnemy(hooh, 12));
		pokemons.push_back(pmf.CreateEnemy(pikachu, 13));

		// set name and map
		name = "gymYoungster";
		map = "tianyuangym";
		type = walker;

		// set direction
		direction = left;

		// set dialog
		normalDialog.InitDialog('n');
		normalDialog.AddText("this road does not work too");
		atkDialogCounter = 0;
		normalDialog.AddText("damn it");

		eventDialog.InitDialog('n');
		eventDialog.AddText("go to challenge gym master");

		// set prize
		prize = 69;
	}

	void TrainerGymYoungster::KeyDownListener(UINT nChar, CHero &hero)
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
				if (normalDialog.IsEnd()) {
					StopTalk(hero);
				}
			}
			else {
				eventDialog.Next();

				if (eventDialog.IsEnd()) {
					StopTalk(hero);
					hero.SetGameEvent(winYoungster, true);
				}
			}
		}
	}

	void TrainerGymYoungster::LoadBitmap()
	{
		normalImg[down].LoadBitmap(IDB_YOUNGSTER_UP, RGB(255, 0, 0));
		normalImg[left].LoadBitmap(IDB_YOUNGSTER_LEFT, RGB(255, 0, 0));
		normalImg[up].LoadBitmap(IDB_YOUNGSTER_DOWN, RGB(255, 0, 0));
		normalImg[right].LoadBitmap(IDB_YOUNGSTER_RIGHT, RGB(255, 0, 0));
		atkImg.LoadBitmap(IDB_YOUNGSTER_ATK, RGB(255, 0, 0));
	}

	void TrainerGymYoungster::OnShow(CHero &hero)
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

	void TrainerGymYoungster::ReShow(CHero &hero)
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

	void TrainerGymYoungster::OnMove(CHero &hero)
	{
		if (!IsTalk() && !isEvent && IsDiscoverHero(hero) &&
			(hero.GetSpeed() == STEP_SIZE && hero.GetCount() == 12 ||
				hero.GetSpeed() == STEP_SIZE * 2 && hero.GetCount() == 6)) {
			Talk(hero);
		}
	}

	// private

	void TrainerGymYoungster::Talk(CHero &hero)
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

	void TrainerGymYoungster::SetTopLeft(int hx, int hy)
	{
		int dx = x * SM - hx;
		int dy = y * SM - hy;
		normalImg[direction].SetTopLeft(HERO_X + dx, HERO_Y + dy);
	}
}