#pragma once

#include <string>
#include "Skill.h"
#include "SkillIce.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillPowderSnow : public SkillIce {
	public:
		SkillPowderSnow(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		string EffectText(Pokemon *enemy);
		float freezeRate;
	};
}
