#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "PmList.h"

namespace game_framework {
	PmList::PmList()
	{
		// empty body
	}

	PmList::PmList(PmType type, vector<Pokemon*>* pokemons) :
		type(type), pokemons(pokemons)
	{
		LoadPokemonData(type, pokemons);
	}

	PmList::~PmList()
	{
		for (auto i : targetBall)
			delete i;
	}

	void PmList::LoadBitmap()
	{
		pmlistLeft.LoadBitmap(IDB_PMLIST_LEFT, RGB(255, 0, 0));
		pmlistRight.LoadBitmap(IDB_PMLIST_RIGHT, RGB(255, 0, 0));
	}

	void PmList::SetTopLeft(int left, int top)
	{
		this->left = left;
		this->top = top;

		switch (type) {
		case my:
			pmlistRight.SetTopLeft(left, top);
			for (int i = 0; i < 6; ++i) {
				targetBall[i]->SetTopLeft(left + PMLIST_BALL_RIGHT_LEFT + PMLIST_BALL_INTERVAL * i, top);
			}
			break;
		case enemy:
			pmlistLeft.SetTopLeft(left, top);
			for (int i = 0; i < 6; ++i) {
				targetBall[i]->SetTopLeft(left + PMLIST_BALL_LEFT_RIGHT - PMLIST_BALL_INTERVAL * i, top);
			}
			break;
		}
	}

	void PmList::OnShow()
	{
		switch (type) {
		case my:
			pmlistRight.ShowBitmap();
			break;
		case enemy:
			pmlistLeft.ShowBitmap();
			break;
		}
		for (auto ball : targetBall) {
			ball->ShowBitmap();
		}
	}

	void PmList::LoadPokemonData(PmType type, vector<Pokemon*>* pokemons)
	{
		this->type = type;

		vector<CMovingBitmap*>().swap(targetBall);

		for (int i = 0; i < 6; ++i) {
			if (i < (int)(*pokemons).size()) {
				if ((*pokemons)[i]->GetRemainHP() > 0) {
					targetBall.push_back(new CMovingBitmap);
					targetBall[i]->LoadBitmap(IDB_PMLIST_LIVEBALL, RGB(255, 0, 0));
				}
				else {
					targetBall.push_back(new CMovingBitmap);
					targetBall[i]->LoadBitmap(IDB_PMLIST_DEADBALL, RGB(255, 0, 0));
				}
			}
			else {
				targetBall.push_back(new CMovingBitmap);
				targetBall[i]->LoadBitmap(IDB_PMLIST_NONEBALL, RGB(255, 0, 0));
			}
		}
		SetTopLeft(left, top);
	}

	int PmList::Left()
	{
		return left;
	}

	int PmList::Top()
	{
		return top;
	}
}