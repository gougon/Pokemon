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

namespace game_framework {
	Skill* SkillFactory::CreateSkill(skillName name, pmStyle pmstyle)
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
		default:
			return new SkillImpact(pmstyle);
			break;
		}
	}
}