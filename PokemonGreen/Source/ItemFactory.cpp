#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "ItemFactory.h"
#include "ItemAntidote.h"
#include "ItemSmallVulnerary.h"
#include "ItemBigVulnerary.h"
#include "ItemFighterGlove.h"
#include "ItemPokeBall.h"
#include "ItemBurnMedicine.h"
namespace game_framework {
	CItem * ItemFactory::CreateItem(int itemID)
	{
		switch (itemID) {
			case Item_Antidote:
				return new ItemAntidote;
				break;
			case Item_SmallVulnerary:
				return new ItemSmallVulnerary;
				break;
			case Item_BigVulnerary:
				return new ItemBigVulnerary;
				break;
			case Item_FighterGlove:
				return new ItemFighterGlove;
				break;
			case Item_PokeBall:
				return new ItemPokeBall;
				break;
			case Item_BurnMedicine:
				return new ItemBurnMedicine;
				break;
			default:
				return new ItemAntidote;
				break;
		}
	}
}
