#pragma once

#include <string>
#include "Skill.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillGrass : public Skill {
	public:
		SkillGrass();
		int Damage(Pokemon *self, Pokemon *enemy);
		AttrDamage DamageEffect(Pokemon *enemy);
	};
}