#pragma once
#include <string>
#include <vector>
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class Pokemon;

	class PmValue {
	public:
		PmValue();
		PmValue(int hp, int atk, int def, int sa, int sd, int sp);
		PmValue(Pokemon *pm);
		PmValue operator-(const PmValue& value2);
		void SetAll(Pokemon *pm);
		void SetAll(int hp, int atk, int def, int sa, int sd, int sp);
		int hp;
		int speed, atk, def, satk, sdef;
	};
}