#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "ItemSmallVulnerary.h"
namespace game_framework {
	ItemSmallVulnerary::ItemSmallVulnerary()
	{
		ID = 1;
		categorie = 1;
		name = "s.vulnerary";
		description = "recover 20 hp";
		cost = 20;
		itemImage.LoadBitmap(ITEM_VULNERARY);
	}
	bool ItemSmallVulnerary::Use(Pokemon * pm)
	{
		TRACE("IN\n");
		if (pm->GetRemainHP() < pm->GetHP())
		{
			if (pm->GetRemainHP() + 20 > pm->GetHP()) pm->SetRemainHP(pm->GetHP());
			else pm->SetRemainHP(pm->GetRemainHP() + 20);
			return true;
		}

		return false;
	}
	bool ItemSmallVulnerary::Take(Pokemon * pm , bool replacement)
	{
		if (!replacement) {
			if (pm->GetTakeItem() == -1) {
				pm->SetTakeItem(this->ID);
				return true;
			}
			return false;
		}
		else {
			TRACE("with replacement\n");
			pm->SetTakeItem(this->ID);
			return true;
		}
	}
}
