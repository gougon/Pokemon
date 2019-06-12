#pragma once
#include "CItem.h"
namespace game_framework {
	class ItemFactory {
	public:
		CItem* CreateItem(int itemID);
	};
}