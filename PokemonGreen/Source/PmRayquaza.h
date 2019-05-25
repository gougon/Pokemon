#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Skill.h"

using namespace std;
namespace game_framework {
	class PmRayquaza : public Pokemon {
	public:
		PmRayquaza();
		PmRayquaza(PmType pmtype);
		PmRayquaza(PmType pmtype, string name);
		virtual void Init(string name);
		virtual void LoadBitmap();
	};
}