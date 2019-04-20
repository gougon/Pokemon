#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "AtkBar.h"
#include "PokemonBar.h"

namespace game_framework {
	void PokemonBar::OnShow()
	{
		targetHp->ShowBitmap("HpBar");
		// show other...
	}

	void PokemonBar::LoadBitmap()
	{
		greenHp.LoadBitmap(IDB_HP_GREEN);
		yellowHp.LoadBitmap(IDB_HP_YELLOW);
		redHp.LoadBitmap(IDB_HP_RED);
		// pmimg.load...
	}

	void PokemonBar::LoadPosition()
	{
		if (order == 0) {
			targetHp->SetTopLeft(BLD_BAR_FIRST_LEFT, BLD_BAR_FIRST_TOP);
		}
		else {
			targetHp->SetTopLeft(BLD_BAR_LEFT, BLD_BAR_TOP + (BLD_BAR_INTERVAL * (order - 1)));
		}
		// load other font img position...
	}

	void PokemonBar::SetOrder(int order)
	{
		this->order = order;
	}

	void PokemonBar::SetAll(string name, int level, int hp, int remainHp)
	{
		this->name = name;
		this->level = level;
		this->hp = hp;
		this->remainHp = remainHp;
		LoadHpLen();
	}

	void PokemonBar::LoadHpLen()
	{
		double rate = (double)remainHp / (double)hp;
		if (rate > 0.5) {
			targetHp = &greenHp;
		}
		else if (rate > 0.2) {
			targetHp = &yellowHp;
		}
		else {
			targetHp = &redHp;
		}
		hpLen = (int)(rate * HP_LEN);
		targetHp->SetWidth(hpLen);
	}
}