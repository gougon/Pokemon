#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Skill.h"

using namespace std;
namespace game_framework {
	class PmTreecko : public Pokemon {
	public:
		PmTreecko();
		PmTreecko(PmType pmtype);
		PmTreecko(PmType pmtype, string name);
		virtual void Init(string name);
		virtual void LoadBitmap();
	};
}