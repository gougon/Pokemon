#pragma once

#include <string>
#include "Skill.h"
#include "SkillPoison.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillPoisonGas : public SkillPoison {
	public:
		SkillPoisonGas(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	};
}
