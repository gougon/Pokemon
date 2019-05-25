#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Skill.h"

using namespace std;
namespace game_framework {
	class PmMetang : public Pokemon {
	public:
		PmMetang();
		PmMetang(PmType pmtype);
		PmMetang(PmType pmtype, string name);
		virtual void Init(string name);
		virtual void LoadBitmap();
	};
}