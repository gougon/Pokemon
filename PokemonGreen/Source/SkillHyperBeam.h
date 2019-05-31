#pragma once

#include <string>
#include "Skill.h"
#include "SkillNormal.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillHyperBeam : public SkillNormal{
	public:
		SkillHyperBeam(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		string EffectText(Pokemon *enemy);
		float freezeRate;
	};
}
