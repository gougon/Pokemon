#pragma once

#include <string>
#include "Skill.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillWater : public Skill {
	public:
		SkillWater();
		int Damage(Pokemon *self, Pokemon *enemy);
		AttrDamage DamageEffect(Pokemon *enemy);
	};
}