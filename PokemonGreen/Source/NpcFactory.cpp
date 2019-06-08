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
#include "TrainerYoungster.h"
#include "TrainerGymYoungster.h"
#include "TrainerGymYamao.h"
#include "TrainerGymMaster.h"
#include "CitizenMom.h"
#include "CitizenSister.h"

namespace game_framework {
	Npc *NpcFactory::CreateNpc(npcName name, AtkInterface &atkInterface)
	{
		switch (name) {
		case trainerMay:
			return new TrainerMay(&atkInterface);
			break;
		case trainerYoungster:
			return new TrainerYoungster(&atkInterface);
			break;
		case trainerGymYoungster:
			return new TrainerGymYoungster(&atkInterface);
			break;
		case trainerGymYamao:
			return new TrainerGymYamao(&atkInterface);
			break;
		case trainerGymMaster:
			return new TrainerGymMaster(&atkInterface);
			break;
		case citizenMom:
			return new CitizenMom();
			break;
		case citizenSister:
			return new CitizenSister();
			break;
		default:
			return new TrainerMay(&atkInterface);
		}
	}
}