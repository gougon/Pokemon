#pragma once

#include <string>
#include "Skill.h"
#include "SkillFire.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillSacredFire : public SkillFire {
	public:
		SkillSacredFire(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		string EffectText(Pokemon *enemy);
		float burnRate;
	};
}
