#pragma once
#include "CItem.h"
#include "Pokemon.h"
namespace game_framework {
	class ItemAntidote : public CItem {
		public:
			ItemAntidote();
			virtual bool Use(Pokemon* pm);
			virtual bool Take(Pokemon* pm , bool replacement);
	};
}
