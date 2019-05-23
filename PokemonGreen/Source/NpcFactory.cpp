#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "NpcFactory.h"
#include "TrainerMay.h"
#include "CitizenMom.h"

namespace game_framework {
	Npc *NpcFactory::CreateNpc(npcName name, AtkInterface &atkInterface)
	{
		switch (name) {
		case trainerMay:
			return new TrainerMay(&atkInterface);
			break;
		case citizenMom:
			return new CitizenMom();
			break;
		default:
			return new TrainerMay(&atkInterface);
		}
	}
}