#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "AtkInterface.h"
#include "CHero.h"
#include "CDialog.h"
#include "Pokemon.h"
#include "Trainer.h"

namespace game_framework
{
	Trainer::Trainer(AtkInterface *atkInterface) :
		type(trainer), isTalk(false), isEvent(false), atkInterface(atkInterface)
	{
		// empty body
	}

	void Trainer::SetIsEvent(bool flag)
	{
		isEvent = flag;
	}

	int Trainer::GetPmNum()
	{
		return pokemons.size();
	}

	int Trainer::GetAliveNum()
	{
		int remainPmNum = 0;
		for (auto i : pokemons) {
			if (i->GetRemainHP() > 0) 
				remainPmNum++;
		}

		return remainPmNum;
	}

	string Trainer::GetMap()
	{
		return map;
	}

	string Trainer::GetName()
	{
		return name;
	}

	CMovingBitmap *Trainer::GetAtkImg()
	{
		return &atkImg;
	}

	Pokemon *Trainer::GetPokemon(int order)
	{
		return pokemons[order];
	}

	vector<Pokemon*>* Trainer::GetPokemons()
	{
		return &pokemons;
	}

	bool Trainer::IsTalk()
	{
		return isTalk;
	}

	bool Trainer::IsCollision(int x, int y)
	{
		x /= SM;
		y /= SM;

		return (this->x == x && this->y == y);
	}

	// protected

	void Trainer::StopTalk()
	{
		eventDialog.Reset();
		isTalk = false;
	}

	void Trainer::StartAtk(CHero* self, Trainer* trainer, AtkInterface &atkInterface)
	{
		atkInterface.ReceiveTrainer(self, this);
		atkInterface.Start();
	}

	bool Trainer::IsBeTalked(CHero &hero)
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