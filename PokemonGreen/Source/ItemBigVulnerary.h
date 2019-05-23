#pragma once
#pragma once
#include "CItem.h"
#include "Pokemon.h"
namespace game_framework {
	class ItemBigVulnerary : public CItem {
	public:
		ItemBigVulnerary();
		virtual bool Use(Pokemon* pm);
		virtual bool Take(Pokemon* pm, bool replacement);
	};
}