#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <math.h>
#include "Pokeball.h"

namespace game_framework {
	Pokeball::Pokeball() :
		CItem(4), x(0), y(0), isThrow(false), isCatch(false)
	{
		LoadBitmap();
	}

	void Pokeball::OnMove()
	{
		if (!isThrow)
			return;
		SetPos();
	}

	void Pokeball::OnShow()
	{
		if (isThrow)
			ballAnime.OnShow();
	}

	void Pokeball::Use(CHero &hero, Pokemon &enemy)
	{
		isThrow = true;
		int catchRate = enemy.GetCatchRate();
		if (rand() % 100 + 1 < catchRate) {
			isCatch = true;
			hero.AddPokemon(&enemy);
		}
	}

	// private

	void Pokeball::LoadBitmap()
	{
		ballAnime.AddBitmap(IDB_CATCH_BALL1, RGB(255, 0, 0));
		ballAnime.AddBitmap(IDB_CATCH_BALL2, RGB(255, 0, 0));
		ballAnime.AddBitmap(IDB_CATCH_BALL3, RGB(255, 0, 0));
	}

	void Pokeball::SetPos()
	{
		if (counter < 20) {
			counter++;
			x = 20 * (counter - 1) + 50;
			y = (int)(-pow(((1 / 15.0) * x - 17), 2) + 475);
		}
		else if (counter >= 40 && counter <= 70 &&
			y < 170) {
			y -= 10;
		}
		ballAnime.SetTopLeft(x, y);
	}
}