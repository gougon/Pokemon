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
#include "SkillConfusion.h"
#include "SkillMetalclaw.h"
#include "SkillScaryFace.h"
#include "SkillLick.h"
#include "SkillPowderSnow.h"
#include "SkillPoisonGas.h"
#include "SkillSludge.h"
#include "SkillWillOwisp.h"
#include "SkillFlameThrower.h"
#include "SkillThunderShock.h"
#include "SkillThunderBolt.h"
#include "SkillBubbleBeam.h"
#include "SkillWaterGun.h"
#include "SkillAuroraBeam.h"
#include "SkillDragonClaw.h"
#include "SkillCrunch.h"
#include "SkillLeafBlade.h"
#include "SkillLeafStorm.h"
#include "SkillNightShade.h"
#include "SkillPhychoBoost.h"
#include "SkillPhychoKinesis.h"
#include "SkillSacredFire.h"
#include "SkillHyperBeam.h"
#include "SkillSwift.h"

/*
1. harden not work
2. willowisp not work
3. PhychoKinesis not work
4. scaredfire not work
*/

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
		case confusion:
			return new SkillConfusion(pmstyle);
			break;
		case metalclaw:
			return new SkillMetalClaw(pmstyle);
			break;
		case scaryface:
			return new SkillScaryFace(pmstyle);
			break;
		case lick:
			return new SkillLick(pmstyle);
			break;
		case powdersnow:
			return new SkillPowderSnow(pmstyle);
			break;
		case poisongas:
			return new SkillPoisonGas(pmstyle);
			break;
		case sludge:
			return new SkillSludge(pmstyle);
			break;
		case willowisp:
			return new SkillWillOwisp(pmstyle);
			break;
		case flamethrower:
			return new SkillFlameThrower(pmstyle);
			break;
		case thundershock:
			return new SkillThunderShock(pmstyle);
			break;
		case thunderbolt:
			return new SkillThunderBolt(pmstyle);
			break;
		case bubblebeam:
			return new SkillBubbleBeam(pmstyle);
			break;
		case watergun:
			return new SkillWaterGun(pmstyle);
			break;
		case aurorabeam:
			return new SkillAuroraBeam(pmstyle);
			break;
		case dragonclaw:
			return new SkillDragonClaw(pmstyle);
			break;
		case crunch:
			return new SkillCrunch(pmstyle);
			break;
		case leafblade:
			return new SkillLeafBlade(pmstyle);
			break;
		case leafstorm:
			return new SkillLeafStorm(pmstyle);
			break;
		case nightshade:
			return new SkillNightShade(pmstyle);
			break;
		case phychoboost:
			return new SkillPhychoBoost(pmstyle);
			break;
		case phychokinesis:
			return new SkillPhychoKinesis(pmstyle);
			break;
		case scaredfire:
			return new SkillSacredFire(pmstyle);
			break;
		case hyperbeam:
			return new SkillHyperBeam(pmstyle);
			break;
		case swift:
			return new SkillSwift(pmstyle);
			break;
		default:
			return new SkillImpact(pmstyle);
			break;
		}
	}
}