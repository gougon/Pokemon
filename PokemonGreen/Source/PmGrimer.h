#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Skill.h"

using namespace std;
namespace game_framework {
	class PmGrimer : public Pokemon {
	public:
		PmGrimer();
		PmGrimer(PmType pmtype);
		PmGrimer(PmType pmtype, string name);
		virtual void Init(string name);
		virtual void LoadBitmap();
	};
}