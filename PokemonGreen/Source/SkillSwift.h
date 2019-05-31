#pragma once

#include <string>
#include "Skill.h"
#include "SkillNormal.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillSwift : public SkillNormal {
	public:
		SkillSwift(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		string EffectText(Pokemon *enemy);
		float freezeRate;
	};
}
