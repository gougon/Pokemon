#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Trainer.h"
#include "CHero.h"
#include "TrainerGymMaster.h"
#include "PokemonFactory.h"

namespace game_framework
{
	TrainerGymMaster::TrainerGymMaster(AtkInterface *atkInterface) :
		Trainer(atkInterface)
	{
		// set position
		x = 25;
		y = 22;

		// set pokemons
		PokemonFactory pmf;
		pokemons.push_back(pmf.CreateEnemy(rayquaza, 17));
		pokemons.push_back(pmf.CreateEnemy(deoxys, 20));

		// set name and map
		name = "gymMaster";
		map = "tianyuangym";
		type = walker;

		// set direction
		direction = down;

		// set dialog
		normalDialog.InitDialog('n');
		normalDialog.AddText("my name is fanshi");
		normalDialog.AddText("i am the master of this gym");
		normalDialog.AddText("show your power to me");
		atkDialogCounter = 2;
		normalDialog.AddText("damn it");

		eventDialog.InitDialog('n');
		eventDialog.AddText("you kicked my ass");

		// set prize
		prize = 69;
	}

	void TrainerGymMaster::KeyDownListener(UINT nChar, CHero &hero)
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
					hero.SetGameEvent(winMaster, true);
				}
			}
		}
	}

	void TrainerGymMaster::LoadBitmap()
	{
		normalImg[down].LoadBitmap(IDB_MASTER_DOWN, RGB(255, 0, 0));
		normalImg[left].LoadBitmap(IDB_MASTER_LEFT, RGB(255, 0, 0));
		normalImg[up].LoadBitmap(IDB_MASTER_DOWN, RGB(255, 0, 0));
		normalImg[right].LoadBitmap(IDB_MASTER_RIGHT, RGB(255, 0, 0));
		atkImg.LoadBitmap(IDB_MASTER_ATK, RGB(255, 0, 0));
	}

	void TrainerGymMaster::OnShow(CHero &hero)
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

	void TrainerGymMaster::ReShow(CHero &hero)
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

	void TrainerGymMaster::OnMove(CHero &hero)
	{
		if (!IsTalk() && !isEvent && IsDiscoverHero(hero) &&
			(hero.GetSpeed() == STEP_SIZE && hero.GetCount() == 12 ||
				hero.GetSpeed() == STEP_SIZE * 2 && hero.GetCount() == 6)) {
			Talk(hero);
		}
	}

	// private

	void TrainerGymMaster::Talk(CHero &hero)
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

	void TrainerGymMaster::SetTopLeft(int hx, int hy)
	{
		int dx = x * SM - hx;
		int dy = y * SM - hy;
		normalImg[direction].SetTopLeft(HERO_X + dx, HERO_Y + dy);
	}
}