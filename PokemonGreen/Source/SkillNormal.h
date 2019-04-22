#pragma once

#include <string>
#include "Skill.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillNormal : public Skill {
	public:
		int Damage(Pokemon *self, Pokemon *enemy);
	};
}

