#pragma once

#include <string>
#include "Skill.h"
#include "SkillPoison.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillSludge : public SkillPoison {
	public:
		SkillSludge(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		string EffectText(Pokemon *enemy);
		float poisonRate;
	};
}
