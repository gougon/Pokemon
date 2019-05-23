#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "ItemBurnMedicine.h"
namespace game_framework {
	ItemBurnMedicine::ItemBurnMedicine()
	{
		ID = 5;
		categorie = 1;
		name = "burn medi.";
		description = "burn recover";
		cost = 10;
		itemImage.LoadBitmap(ITEM_BURNMEDICINE);
	}
	bool ItemBurnMedicine::Use(Pokemon * pm)
	{
		if (pm->GetStatus()->GetStatu() == statuBurn) {
			pm->SetStatus(none);
			return true;
		}
		return false;
	}
	bool ItemBurnMedicine::Take(Pokemon* pm, bool replacement)
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
