#pragma once

#include <string>
#include "Skill.h"

using namespace std;
namespace game_framework {
	enum skillName {
		impact, leer, ember
	};

	class SkillFactory {
	public:
		Skill* CreateSkill(skillName skillName, pmStyle pmstyle);
	};
}

