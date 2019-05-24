#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "ItemPokeBall.h"
namespace game_framework {
	ItemPokeBall::ItemPokeBall()
	{
		ID = 4;
		categorie = 2;
		name = "pokeball";
		description = "catch the pokemon";
		cost = 50;
		itemImage.LoadBitmap(ITEM_POKEBALL);
		LoadBitmap();
	}
	void ItemPokeBall::OnMove()
	{
		if (!isThrow)
			return;
		if (ballopen) {
			TRACE("Ballopen\n");
			ballAnime.OnMove();
		}
		SetPos();
	}
	void ItemPokeBall::OnShow()
	{
		if (isThrow)
			ballAnime.OnShow();
	}
	bool ItemPokeBall::Use(Pokemon * pm)
	{
		return false;
	}
	void ItemPokeBall::UsePokeBall(CHero* self, Pokemon* enemy)
	{
		TRACE("throw\n");
		isCatch = false;
		ballopen = false;
		isThrow = true;
		counter = 0;
		x = 0;
		y = 0;
		self->AddPokemon(enemy);
		/*
		int catchRate = enemy->GetCatchRate();
		if (rand() % 100 + 1 < catchRate) isCatch = true;
		*/
	}
	bool ItemPokeBall::IsCatch()
	{
		return isCatch;
	}
	bool ItemPokeBall::animeEnd()
	{
		return endFlag;
	}
	bool ItemPokeBall::Take(Pokemon* pm, bool replacement)
	{
		if (!replacement) {
			if (pm->GetTakeItem() == -1) {
				pm->SetTakeItem(this->ID);
				return true;
			}
			return false;
		}
		else {
			pm->SetTakeItem(this->ID);
			return true;
		}
	}
	// private

	void ItemPokeBall::LoadBitmap()
	{
		ballAnime.AddBitmap(IDB_CATCH_BALL1, RGB(255, 0, 0));
		ballAnime.AddBitmap(IDB_CATCH_BALL2, RGB(255, 0, 0));
		ballAnime.AddBitmap(IDB_CATCH_BALL3, RGB(255, 0, 0));
		ballAnime.SetDelayCount(2);
	}

	void ItemPokeBall::SetPos()
	{
		if (counter < 20) {
			endFlag = false;
			counter++;
			x = 22 * (counter - 1) + 50;
			y = (int)(pow(((1 / 15.0) * x - 17), 2) - 120);
		}
		else if (counter < 35) {
			y += 2;
			ballopen = true;
			counter++;
		}
		else {
			TRACE("end flag launch\n");
			endFlag = true;
		}
		ballAnime.SetTopLeft(x, y);
	}
}
