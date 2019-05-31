#pragma once

#include <string>
#include "Skill.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillSteel : public Skill {
	public:
		SkillSteel();
		int Damage(Pokemon *self, Pokemon *enemy);
		AttrDamage DamageEffect(Pokemon *enemy);
	};
}