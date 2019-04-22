#pragma once

#include <string>
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class Pokemon;

	enum pmStyle {
		styleSelf, styleEnemy
	};

	enum CSkill {
		physical, status, special
	};

	class Skill {
	public:
		Skill();
		virtual void Init() = 0;
		virtual void Use(Pokemon *self, Pokemon *enemy) = 0;
		virtual bool AtkAnimeOnMove() = 0;
		virtual void AtkAnimeOnShow() = 0;
		string GetAttributeText();
		string GetName();
		int GetRemainPP();
		int GetAllPP();
		//virtual void Use(Pokemon *self, Pokemon *enemy1, Pokemon *enemy2) = 0;
	protected:
		pmStyle pmstyle;
		CAnimation atkAnime;
		int attribute;
		string name;
		int animeCount;
		CSkill category;
		int power;
		int allpp;
		int remainpp;
		float hitRate;
	};
}
