#pragma once

#include <string>
#include "Skill.h"
#include "SkillFire.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillEmber : public SkillFire {
	public:
		SkillEmber(pmStyle pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
		virtual bool AtkAnimeOnMove();
		virtual void AtkAnimeOnShow();
	private:
		string EffectText(Pokemon *enemy);
		float burnRate;
	};
}
