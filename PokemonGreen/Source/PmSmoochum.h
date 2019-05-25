#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Skill.h"

using namespace std;
namespace game_framework {
	class PmSmoochum : public Pokemon {
	public:
		PmSmoochum();
		PmSmoochum(PmType pmtype);
		PmSmoochum(PmType pmtype, string name);
		virtual void Init(string name);
		virtual void LoadBitmap();
	};
}