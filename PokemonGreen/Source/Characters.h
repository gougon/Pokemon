#pragma once

#include <vector>
#include "Npc.h"
#include "AtkInterface.h"
#include "Trainer.h"
#include "Citizen.h"

using namespace std;
namespace game_framework {
	class CHero;
	class Characters {
	public:
		Characters(AtkInterface *atkInterface);
		~Characters();
		void InitNpcs();
		void KeyDownListener(UINT nChar, CHero &hero, CMap &map);
		void OnShow(CHero &hero, CMap &map);
		void ReShow(CHero &hero, CMap &map);
		void OnMove(CHero &hero, CMap &map);
		bool IsCollision(int x, int y, CMap &map);
		bool IsTalk();
	private:
		void LoadBitmap();

		vector<Npc*> npcs;
		AtkInterface *atkInterface;
	};
}