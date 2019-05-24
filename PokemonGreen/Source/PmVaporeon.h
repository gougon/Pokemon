#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Skill.h"

using namespace std;
namespace game_framework {
	class PmVaporeon : public Pokemon {
	public:
		PmVaporeon();
		PmVaporeon(PmType pmtype);
		PmVaporeon(PmType pmtype, string name);
		virtual void Init(string name);
		virtual void LoadBitmap();
	};
}