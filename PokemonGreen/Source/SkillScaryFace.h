#pragma once

#include <string>
#include "Skill.h"
#include "SkillNormal.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class SkillScaryFace : public SkillNormal {
	public:
		SkillScaryFace(int pmstyle);
		virtual void Init();
		virtual string Use(Pokemon *self, Pokemon *enemy);
	private:
		float attachRate;
	};
}
