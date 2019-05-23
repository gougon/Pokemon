#pragma once

#include <string>
#include "Npc.h"
#include "AtkInterface.h"

using namespace std;
namespace game_framework {
	enum npcName {
		trainerMay, citizenMom
	};

	class NpcFactory {
	public:
		Npc *CreateNpc(npcName name, AtkInterface &atkInterface);
	};
}