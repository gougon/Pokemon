#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CitizenFatguy.h"
namespace game_framework
{

	CitizenFatguy::CitizenFatguy():
		Citizen()
	{
		// set position
		x = 103;
		y = 86;

		// set name
		name = "fatguy";
		map = "weibai";
		type = citizen;

		// set direction
		direction = down;

		// set dialog
		normalDialog.InitDialog('n');
		normalDialog.AddText("do you have some;delicious foods?");
		normalDialog.AddText("you call me fatguy!!");
		normalDialog.AddText("get out of my way!!");
	}

	void CitizenFatguy::KeyDownListener(UINT nChar, CHero &hero)
	{
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28;
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
				normalDialog.Next();

				// assessment whether dialog is end
				if (normalDialog.IsEnd()) {
					normalDialog.Reset();
					StopTalk(hero);
				}
			}
			else {
				eventDialog.Next();

				if (eventDialog.IsEnd())
					StopTalk(hero);
			}
		}
	}

	void CitizenFatguy::LoadBitmap()
	{
		normalImg[up].LoadBitmap(FATGUY_UP, RGB(255, 0, 0));
		normalImg[down].LoadBitmap(FATGUY_DOWN, RGB(255, 0, 0));
		normalImg[left].LoadBitmap(FATGUY_LEFT, RGB(255, 0, 0));
		normalImg[right].LoadBitmap(FATGUY_RIGHT, RGB(255, 0, 0));
	}

	void CitizenFatguy::OnShow(CHero &hero)
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

	void CitizenFatguy::ReShow(CHero &hero)
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

	void CitizenFatguy::OnMove(CHero &hero) // for don't move
	{
		if (!isEvent) {
			if (hero.GetGameEvent(winMay))
				isEvent = true;
			int hx = hero.GetX1() / SM;
			int hy = hero.GetY1() / SM;
			if (hx == x && hy == y - 1 &&
				(hero.GetSpeed() == STEP_SIZE && hero.GetCount() == 12 ||
					hero.GetSpeed() == STEP_SIZE * 2 && hero.GetCount() == 6)) {
				Talk(hero);
			}
		}
	}

	// private

	void CitizenFatguy::Talk(CHero &hero)
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

	void CitizenFatguy::SetTopLeft(int hx, int hy)
	{
		int dx = x * SM - hx;
		int dy = y * SM - hy;
		normalImg[direction].SetTopLeft(HERO_X + dx, HERO_Y + dy);
	}
}
