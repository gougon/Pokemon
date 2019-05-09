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

	enum AttrDamage {
		superEffe, normalEffe, lowEffe, notEffe
	};

	class Skill {
	public:
		Skill();
		virtual void Init() = 0;
		virtual string Use(Pokemon *self, Pokemon *enemy) = 0;
		bool AtkAnimeOnMove();
		void AtkAnimeOnShow();
		virtual AttrDamage DamageEffect(Pokemon *enemy) = 0;
		string GetAttributeText();
		string GetName();
		string GetDescription();
		int GetRemainPP();
		int GetAllPP();
		int GetPower();
		int GetHitRate();
		//virtual void Use(Pokemon *self, Pokemon *enemy1, Pokemon *enemy2) = 0;
	protected:
		pmStyle pmstyle;
		CAnimation atkAnime;
		CSkill category;
		string name, description;
		int attribute, power, allpp, remainpp, animeCount;
		float hitRate;
		bool isSuccess;
	};
}
