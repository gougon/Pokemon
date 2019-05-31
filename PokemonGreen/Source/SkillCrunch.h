#pragma once

#include <string>
#include "Skill.h"
#include "SkillDragon.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillCrunch : public SkillDragon {
	public:
		SkillCrunch(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		string EffectText(Pokemon *enemy);
		float attachRate;
	};
}
