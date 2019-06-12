#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "ItemAntidote.h"
namespace game_framework {
	ItemAntidote::ItemAntidote()
	{
		ID = 0;
		categorie = 1;
		name = "antidote";
		description = "poison recover";
		cost = 10;
		itemImage.LoadBitmap(ITEM_ANTIDOTE);
	}

	bool ItemAntidote::Use(Pokemon * pm)
	{
		if (pm->GetStatus()->GetStatu() == statuPoison) {
			pm->SetStatus(none);
			return true;
		}
		return false;
	}

	bool ItemAntidote::Take(Pokemon * pm , bool replacement)
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
}
