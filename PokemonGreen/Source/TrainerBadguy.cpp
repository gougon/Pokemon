#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Trainer.h"
#include "CHero.h"
#include "TrainerBadguy.h"
#include "PokemonFactory.h"

namespace game_framework
{
	TrainerBadguy::TrainerBadguy(AtkInterface *atkInterface) :
		Trainer(atkInterface)
	{
		// set position
		x = 61;
		y = 50;

		// set pokemons
		PokemonFactory pmf;
		pokemons.push_back(pmf.CreateEnemy(metang, 10));
		pokemons.push_back(pmf.CreateEnemy(grovyle, 10));

		// set name and map
		name = "badguy";
		map = "weibai";
		type = walker;

		// set direction
		direction = right;

		// set dialog
		normalDialog.InitDialog('n');
		normalDialog.AddText("i am really really bad");
		normalDialog.AddText("give me your all money");
		atkDialogCounter = 1;
		normalDialog.AddText("damn it");

		eventDialog.InitDialog('n');
		eventDialog.AddText("wait me to call my brother;and you better run now");

		// set prize
		prize = 69;
	}

	void TrainerBadguy::KeyDownListener(UINT nChar, CHero &hero)
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
					hero.SetGameEvent(winBadGuy, true);
					StopTalk(hero);
				}
			}
			else {
				eventDialog.Next();

				if (eventDialog.IsEnd()) {
					StopTalk(hero);
				}
			}
		}
	}

	void TrainerBadguy::LoadBitmap()
	{
		normalImg[down].LoadBitmap(IDB_BADGUY_DOWN, RGB(255, 0, 0));
		normalImg[left].LoadBitmap(IDB_MAY_LEFT, RGB(255, 0, 0));
		normalImg[up].LoadBitmap(IDB_BADGUY_UP, RGB(255, 0, 0));
		normalImg[right].LoadBitmap(IDB_BADGUY_RIGHT, RGB(255, 0, 0));
		atkImg.LoadBitmap(IDB_BADGUY_ATK, RGB(255, 0, 0));
	}

	void TrainerBadguy::OnShow(CHero &hero)
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

	void TrainerBadguy::ReShow(CHero &hero)
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

	void TrainerBadguy::OnMove(CHero &hero)
	{
		if (!IsTalk() && !isEvent && IsDiscoverHero(hero) &&
			(hero.GetSpeed() == STEP_SIZE && hero.GetCount() == 12 ||
				hero.GetSpeed() == STEP_SIZE * 2 && hero.GetCount() == 6)) {
			Talk(hero);
		}
	}

	// private

	void TrainerBadguy::Talk(CHero &hero)
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

	void TrainerBadguy::SetTopLeft(int hx, int hy)
	{
		int dx = x * SM - hx;
		int dy = y * SM - hy;
		normalImg[direction].SetTopLeft(HERO_X + dx, HERO_Y + dy);
	}
}