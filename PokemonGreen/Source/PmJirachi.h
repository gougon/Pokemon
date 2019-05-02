#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Skill.h"

using namespace std;
namespace game_framework {
	class PmJirachi : public Pokemon {
	public:
		PmJirachi();
		PmJirachi(PmType pmtype);
		PmJirachi(PmType pmtype, string name);
		virtual void Init(string name);
		virtual void LoadBitmap();
	};
}