#pragma once

#include <string>
#include "Skill.h"
#include "SkillWater.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillWaterGun : public SkillWater {
	public:
		SkillWaterGun(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		string EffectText(Pokemon *enemy);
	};
}
