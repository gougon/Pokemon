#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CHero.h"
#include "CDialog.h"
#include "Citizen.h"

namespace game_framework {
	Citizen::Citizen() :
		type(citizen), isTalk(false), isEvent(false)
	{
		// empty body
	}

	void Citizen::SetIsEvent(bool flag)
	{
		isEvent = flag;
	}

	string Citizen::GetMap()
	{
		return map;
	}

	bool Citizen::IsTalk()
	{
		return isTalk;
	}

	bool Citizen::IsCollision(int x, int y)
	{
		x /= SM;
		y /= SM;

		return (this->x == x && this->y == y);
	}

	// protected

	void Citizen::StopTalk()
	{
		eventDialog.Reset();
		isTalk = false;
	}

	bool Citizen::IsBeTalked(CHero &hero)
	{
		int hx = hero.GetX1() / SM;
		int hy = hero.GetY1() / SM;
		if (hero.GetDirection() == up &&
			x == hx && y == hy - 1)
			return true;
		else if (hero.GetDirection() == left &&
			x == hx - 1 && y == hy)
			return true;
		else if (hero.GetDirection() == down &&
			x == hx && y == hy + 1)
			return true;
		else if (hero.GetDirection() == right &&
			x == hx + 1 && y == hy)
			return true;
		else
			return false;
	}
}