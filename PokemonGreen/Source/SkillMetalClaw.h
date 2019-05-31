#pragma once

#include <string>
#include "Skill.h"
#include "SkillSteel.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillMetalClaw : public SkillSteel {
	public:
		SkillMetalClaw(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		string EffectText(Pokemon *enemy);
		float attachRate;
	};
}
