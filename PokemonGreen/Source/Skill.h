#pragma once

#include <string>
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class Pokemon;

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
	protected:
		int pmstyle;
		CAnimation atkAnime;
		CAnimation atkEnemyAnime;
		CSkill category;
		string name, description;
		int attribute, power, allpp, remainpp, animeCount;
		float hitRate;
		bool isSuccess;
	};
}
