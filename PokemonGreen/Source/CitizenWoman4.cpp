#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CitizenWoman4.h"
namespace game_framework
{

	CitizenWoman4::CitizenWoman4() :
		Citizen()
	{
		// set position
		x = 21;
		y = 19;

		// set name
		name = "cute lady";
		map = "tianyuantown_lthouse";
		type = citizen;

		// set direction
		direction = left;

		// set dialog
		normalDialog.InitDialog('n');
		normalDialog.AddText("you are cute!");
		normalDialog.AddText("can you date with me?");
	}

	void CitizenWoman4::KeyDownListener(UINT nChar, CHero &hero)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
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

	void CitizenWoman4::LoadBitmap()
	{
		normalImg[up].LoadBitmap(IDB_WOMAN4_UP, RGB(255, 0, 0));
		normalImg[down].LoadBitmap(IDB_WOMAN4_DOWN, RGB(255, 0, 0));
		normalImg[left].LoadBitmap(IDB_WOMAN4_LEFT, RGB(255, 0, 0));
		normalImg[right].LoadBitmap(IDB_WOMAN4_RIGHT, RGB(255, 0, 0));
	}

	void CitizenWoman4::OnShow(CHero &hero)
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

	void CitizenWoman4::ReShow(CHero &hero)
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

	void CitizenWoman4::OnMove(CHero &hero) // for don't move
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

	void CitizenWoman4::Talk(CHero &hero)
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

	void CitizenWoman4::SetTopLeft(int hx, int hy)
	{
		int dx = x * SM - hx;
		int dy = y * SM - hy;
		normalImg[direction].SetTopLeft(HERO_X + dx, HERO_Y + dy);
	}
}
