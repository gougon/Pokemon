#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Skill.h"

using namespace std;
namespace game_framework {
	class PmVulpix : public Pokemon {
	public:
		PmVulpix();
		PmVulpix(PmType pmtype);
		PmVulpix(PmType pmtype, string name);
		virtual void Init(string name);
		virtual void LoadBitmap();
	};
}