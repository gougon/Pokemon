#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CitizenMom.h"
namespace game_framework
{

	CitizenMom::CitizenMom() :
		Citizen()
	{
		// set position
		x = 22;
		y = 18;

		// set name
		name = "mom";
		map = "weibaihouse1_1";

		// set direction
		direction = down;

		// set dialog
		normalDialog.InitDialog('n');
		normalDialog.AddText("hey boy");
		normalDialog.AddText("my name is may");
		normalDialog.AddText("lets battle");
		normalDialog.AddText("damn it");

		eventDialog.InitDialog('n');
		eventDialog.AddText("you are pretty strong");
	}

	void CitizenMom::KeyDownListener(UINT nChar, CHero &hero)
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
				normalDialog.Next();

				// assessment whether dialog is end
				if (normalDialog.IsEnd()) {
					StopTalk(hero);
					isEvent = true;
				}
			}
			else {
				eventDialog.Next();

				if (eventDialog.IsEnd())
					StopTalk(hero);
			}
		}
	}

	void CitizenMom::LoadBitmap()
	{
		normalImg[up].LoadBitmap(MOM_UP, RGB(255, 0, 0));
		normalImg[down].LoadBitmap(MOM_DOWN, RGB(255, 0, 0));
		normalImg[left].LoadBitmap(MOM_LEFT, RGB(255, 0, 0));
		normalImg[right].LoadBitmap(MOM_RIGHT, RGB(255, 0, 0));
	}

	void CitizenMom::OnShow(CHero &hero)
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

	void CitizenMom::ReShow(CHero &hero)
	{
		int hx = hero.GetX1() / SM;
		int hy = (hero.GetY1() + 20) / SM;
		if (abs(hx - x) <= 9 && abs(hy - y) <= 9 && hy <= y) {
			SetTopLeft(hero.GetX1(), hero.GetY1());
			normalImg[direction].ShowBitmap();
		}
	}

	void CitizenMom::OnMove() // for don't move
	{
		// empty body
	}

	// private

	void CitizenMom::Talk(CHero &hero)
	{
		isTalk = true;
		direction = (hero.GetDirection() % 2 == 0) ?
			hero.GetDirection() + 1 : hero.GetDirection() - 1;
	}

	void CitizenMom::SetTopLeft(int hx, int hy)
	{
		int dx = x * SM - hx;
		int dy = y * SM - hy;
		normalImg[direction].SetTopLeft(HERO_X + dx, HERO_Y + dy);
	}
}
