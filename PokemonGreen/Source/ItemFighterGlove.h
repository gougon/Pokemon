#pragma once
#include "CItem.h"
#include "Pokemon.h"
namespace game_framework {
	class ItemFighterGlove : public CItem {
	public:
		ItemFighterGlove();
		virtual bool Use(Pokemon* pm);
		virtual bool Take(Pokemon* pm, bool replacement);
	};
}