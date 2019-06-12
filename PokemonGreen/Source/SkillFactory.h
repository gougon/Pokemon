#pragma once

#include <string>
#include "Skill.h"

using namespace std;
namespace game_framework {
	enum skillName {
		impact, leer, ember , confusion , metalclaw , scaryface , lick , powdersnow , poisongas,
		sludge, willowisp, flamethrower, thundershock, thunderbolt, bubblebeam, watergun, aurorabeam,
		dragonclaw, crunch, leafblade, leafstorm, nightshade, phychokinesis, phychoboost,
		scaredfire, hyperbeam, swift
	};

	class SkillFactory {
	public:
		Skill* CreateSkill(skillName skillName, int pmstyle);
	};
}

