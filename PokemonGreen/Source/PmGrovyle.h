#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Skill.h"

using namespace std;
namespace game_framework {
	class PmGrovyle : public Pokemon {
	public:
		PmGrovyle();
		PmGrovyle(PmType pmtype);
		PmGrovyle(PmType pmtype, string name);
		virtual void Init(string name);
		virtual void LoadBitmap();
	};
}