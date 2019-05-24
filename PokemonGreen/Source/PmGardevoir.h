#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Skill.h"

using namespace std;
namespace game_framework {
	class PmGardevoir : public Pokemon {
	public:
		PmGardevoir();
		PmGardevoir(PmType pmtype);
		PmGardevoir(PmType pmtype, string name);
		virtual void Init(string name);
		virtual void LoadBitmap();
	};
}