#pragma once

#include <string>
#include <vector>
#include "Pokemon.h"
#include "Skill.h"

using namespace std;
namespace game_framework {
	class PmPikachu : public Pokemon {
	public:
		PmPikachu();
		PmPikachu(PmType pmtype);
		PmPikachu(PmType pmtype, string name);
		virtual void Init(string name);
		virtual void LoadBitmap();
	};
}