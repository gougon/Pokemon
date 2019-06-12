#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CitizenGirl3.h"
namespace game_framework
{

	CitizenGirl3::CitizenGirl3() :
		Citizen()
	{
		// set position
		x = 18;
		y = 20;

		// set name
		name = "twin sister";
		map = "tianyuan_hospital";
		type = citizen;

		// set direction
		direction = up;

		// set dialog
		normalDialog.InitDialog('n');
		normalDialog.AddText("borther, i want to go outside;to adventure");
	}

	void CitizenGirl3::KeyDownListener(UINT nChar, CHero &hero)
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

	void CitizenGirl3::LoadBitmap()
	{
		normalImg[up].LoadBitmap(IDB_GIRL3_UP, RGB(255, 0, 0));
		normalImg[down].LoadBitmap(IDB_GIRL3_DOWN, RGB(255, 0, 0));
		normalImg[left].LoadBitmap(IDB_GIRL3_LEFT, RGB(255, 0, 0));
		normalImg[right].LoadBitmap(IDB_GIRL3_RIGHT, RGB(255, 0, 0));
	}

	void CitizenGirl3::OnShow(CHero &hero)
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

	void CitizenGirl3::ReShow(CHero &hero)
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

	void CitizenGirl3::OnMove(CHero &hero) // for don't move
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

	void CitizenGirl3::Talk(CHero &hero)
	{
		isTalk = true;
		hero.SetCanMove(false);
	}

	void CitizenGirl3::SetTopLeft(int hx, int hy)
	{
		int dx = x * SM - hx;
		int dy = y * SM - hy;
		normalImg[direction].SetTopLeft(HERO_X + dx, HERO_Y + dy);
	}
}
