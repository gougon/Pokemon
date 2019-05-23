#pragma once
#include "CItem.h"
#include "Pokemon.h"
namespace game_framework {
	class ItemSmallVulnerary : public CItem {
	public:
		ItemSmallVulnerary();
		bool Use(Pokemon* pm);
		bool Take(Pokemon* pm , bool replacement);
	};
}