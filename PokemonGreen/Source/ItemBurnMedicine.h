#pragma once
#include "CItem.h"
#include "Pokemon.h"
namespace game_framework {
	class ItemBurnMedicine : public CItem {
	public:
		ItemBurnMedicine();
		virtual bool Use(Pokemon* pm);
		virtual bool Take(Pokemon* pm, bool replacement);
	};
}
