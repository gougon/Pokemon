#pragma once

#include <string>
#include "Skill.h"
#include "SkillNormal.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillImpact : public SkillNormal {
	public:
		SkillImpact(pmStyle pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
		virtual bool AtkAnimeOnMove();
		virtual void AtkAnimeOnShow();
	private:
		string EffectText(Pokemon *enemy);
	};
}
