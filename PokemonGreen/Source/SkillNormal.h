#pragma once

#include <string>
#include "Skill.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillNormal : public Skill {
	public:
		SkillNormal();
		int Damage(Pokemon *self, Pokemon *enemy);
		AttrDamage DamageEffect(Pokemon *enemy);
	};
}

