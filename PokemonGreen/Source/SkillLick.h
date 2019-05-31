#pragma once

#include <string>
#include "Skill.h"
#include "SkillGhost.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillLick : public SkillGhost {
	public:
		SkillLick(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		string EffectText(Pokemon *enemy);
		float attachRate;
	};
}
