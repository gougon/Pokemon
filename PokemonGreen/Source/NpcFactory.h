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
		citizenBoy,		//19 20
		citizenGirl1,
		citizenGirl2,
		citizenGirl3,	//18 20
		citizenMan1,
		citizenMan2,	//21 18
		citizenMan3,	//23 19
		citizenMan4,	//18 18
		citizenMan5,	//32 34
		citizenWoman1,
		citizenWoman2,	//21 19
		citizenWoman3,	//105 41
		citizenWoman4,	//21 19
		citizenWoman5,	//19 20
		citizenResearcher,
		citizenOdd
	};

	class NpcFactory {
	public:
		Npc *CreateNpc(npcName name, AtkInterface &atkInterface);
	};
}