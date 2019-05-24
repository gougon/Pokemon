#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Skill.h"

using namespace std;
namespace game_framework {
	class PmDeoxys : public Pokemon {
	public:
		PmDeoxys();
		PmDeoxys(PmType pmtype);
		PmDeoxys(PmType pmtype, string name);
		virtual void Init(string name);
		virtual void LoadBitmap();
	};
}