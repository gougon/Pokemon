#pragma once

#include <string>
#include "Skill.h"
#include "SkillWater.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillBubbleBeam : public SkillWater {
	public:
		SkillBubbleBeam(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		string EffectText(Pokemon *enemy);
		float attachRate;
	};
}
