#pragma once

#include <string>
#include "Skill.h"
#include "SkillIce.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillWillOwisp : public SkillIce {
	public:
		SkillWillOwisp(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	};
}
