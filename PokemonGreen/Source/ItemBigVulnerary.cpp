#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "ItemBigVulnerary.h"
namespace game_framework {
	ItemBigVulnerary::ItemBigVulnerary()
	{
		ID = 2;
		categorie = 1;
		name = "l.vulnerary";
		description = "recover 50 hp";
		cost = 50;
		itemImage.LoadBitmap(ITEM_VULNERARY);
	}

	bool ItemBigVulnerary::Use(Pokemon * pm)
	{
		if (pm->GetRemainHP() < pm->GetHP()) {
			if (pm->GetRemainHP() + 50 > pm->GetHP()) pm->SetRemainHP(pm->GetHP());
			else pm->SetRemainHP(pm->GetRemainHP() + 50);
			return true;
		}
		return false;
	}

	bool ItemBigVulnerary::Take(Pokemon* pm, bool replacement)
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
