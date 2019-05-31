#pragma once

#include <string>
#include "Skill.h"
#include "SkillGrass.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillLeafStorm : public SkillGrass {
	public:
		SkillLeafStorm(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		string EffectText(Pokemon *enemy);
	};
}
