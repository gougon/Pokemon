#pragma once

#include <string>
#include "Skill.h"
#include "SkillNormal.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillLeer : public SkillNormal {
	public:
		SkillLeer(pmStyle pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	};
}
