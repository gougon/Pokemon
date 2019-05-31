#pragma once

#include <string>
#include "Skill.h"
#include "SkillPsychic.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillConfusion : public SkillPsychic {
	public:
		SkillConfusion(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		string EffectText(Pokemon *enemy);
		float confusionRate;
	};
}
