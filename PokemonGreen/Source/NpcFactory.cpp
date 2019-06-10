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
#include "TrainerJK.h"
#include "TrainerBadguy.h"
#include "CitizenMom.h"
#include "CitizenFatguy.h"
#include "CitizenSister.h"
#include "CitizenBoy.h"
#include "CitizenGirl1.h"
#include "CitizenGirl2.h"
#include "CitizenGirl3.h"
#include "CitizenMan1.h"
#include "CitizenMan2.h"
#include "CitizenMan3.h"
#include "CitizenMan4.h"
#include "CitizenMan5.h"
#include "CitizenWoman1.h"
#include "CitizenWoman2.h"
#include "CitizenWoman3.h"
#include "CitizenWoman4.h"
#include "CitizenWoman5.h"
#include "CitizenResearcher.h"
#include "CitizenOdd.h"

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
		case trainerJK:
			return new TrainerJK(&atkInterface);
			break;
		case trainerBadguy:
			return new TrainerBadguy(&atkInterface);
			break;
		case citizenMom:
			return new CitizenMom();
			break;
		case citizenFatguy:
			return new CitizenFatguy();
			break;
		case citizenSister:
			return new CitizenSister();
			break;
		case citizenBoy:
			return new CitizenBoy();
			break;
		case citizenGirl1:
			return new CitizenGirl1();
			break;
		case citizenGirl2:
			return new CitizenGirl2();
			break;
		case citizenGirl3:
			return new CitizenGirl3();
			break;
		case citizenMan1:
			return new CitizenMan1();
			break;
		case citizenMan2:
			return new CitizenMan2();
			break;
		case citizenMan3:
			return new CitizenMan3();
			break;
		case citizenMan4:
			return new CitizenMan4();
			break;
		case citizenMan5:
			return new CitizenMan5();
			break;
		case citizenWoman1:
			return new CitizenWoman1();
			break;
		case citizenWoman2:
			return new CitizenWoman2();
			break;
		case citizenWoman3:
			return new CitizenWoman3();
			break;
		case citizenWoman4:
			return new CitizenWoman4();
			break;
		case citizenWoman5:
			return new CitizenWoman5();
			break;
		case citizenResearcher:
			return new CitizenResearcher();
			break;
		case citizenOdd:
			return new CitizenOdd();
			break;
		default:
			return new TrainerMay(&atkInterface);
		}
	}
}