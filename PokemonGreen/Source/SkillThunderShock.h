#pragma once

#include <string>
#include "Skill.h"
#include "SkillElectric.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillThunderShock : public SkillElectric {
	public:
		SkillThunderShock(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		string EffectText(Pokemon *enemy);
		float attachRate;
	};
}
