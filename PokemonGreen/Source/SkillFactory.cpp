#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "SkillFactory.h"
#include "SkillNormal.h"
#include "SkillImpact.h"
#include "SkillLeer.h"
#include "SkillEmber.h"

namespace game_framework {
	Skill* SkillFactory::CreateSkill(skillName name, int pmstyle)
	{
		//Skill *skill;
		switch (name) 
		{
		case impact:
			return new SkillImpact(pmstyle);
			break;
		case leer:
			return new SkillLeer(pmstyle);
			break;
		case ember:
			return new SkillEmber(pmstyle);
			break;
		default:
			return new SkillImpact(pmstyle);
			break;
		}
	}
}