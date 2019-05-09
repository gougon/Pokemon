#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Skill.h"

using namespace std;
namespace game_framework {
	class PmHooh : public Pokemon {
	public:
		PmHooh();
		PmHooh(PmType pmtype);
		PmHooh(PmType pmtype, string name);
		virtual void Init(string name);
		virtual void LoadBitmap();
	};
}