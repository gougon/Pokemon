#pragma once

#include <string>
#include "Skill.h"
#include "SkillGhost.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillNightShade : public SkillGhost {
	public:
		SkillNightShade(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	};
}
