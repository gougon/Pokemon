#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "ItemFighterGlove.h"
namespace game_framework {
	ItemFighterGlove::ItemFighterGlove()
	{
		ID = 3;
		categorie = 5;
		name = "glove";
		description = "add 15 atk";
		cost = 100;
		itemImage.LoadBitmap(ITEM_FIGHTERGLOVE);
	}

	bool ItemFighterGlove::Use(Pokemon * pm)
	{
		return false;
	}

	bool ItemFighterGlove::Take(Pokemon* pm, bool replacement)
	{
		if (!replacement) {
			if (pm->GetTakeItem() == -1) {
				pm->SetRemainAtk(pm->GetAtk() + 15);	//temp
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
}
