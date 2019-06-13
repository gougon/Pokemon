#pragma once

#include <string>
#include "Npc.h"
#include "AtkInterface.h"

using namespace std;
namespace game_framework {
	enum npcName {
		trainerMay, 
		trainerYoungster,
		trainerGymYoungster, 
		trainerGymYamao, 
		trainerGymMaster,
		trainerJK,
		trainerBadguy,
		citizenMom,
		citizenFatguy,
		citizenSister,
		citizenBoy,		
		citizenGirl1,
		citizenGirl2,
		citizenGirl3,	
		citizenMan1,
		citizenMan2,	
		citizenMan3,	
		citizenMan4,	
		citizenMan5,	
		citizenWoman1,
		citizenWoman2,	
		citizenWoman3,	
		citizenWoman4,	
		citizenWoman5,	
		citizenResearcher,
		citizenOdd
	};

	class NpcFactory {
	public:
		Npc *CreateNpc(npcName name, AtkInterface &atkInterface);
	};
}