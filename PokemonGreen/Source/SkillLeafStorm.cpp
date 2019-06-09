#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillLeafStorm.h"

namespace game_framework {
	SkillLeafStorm::SkillLeafStorm(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillLeafStorm::Init()
	{
		name = "leaf storm";
		description = "use sharp leaf storm to attack enemy;decrease self s.atk";
		category = special;
		power = 40;
		allpp = 25;
		remainpp = 25;
		hitRate = 1.0f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_LEAFSTORM1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEAFSTORM2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEAFSTORM3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEAFSTORM4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEAFSTORM5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEAFSTORM6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEAFSTORM7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEAFSTORM8, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEAFSTORM9, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEAFSTORM10, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEAFSTORM11, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_SKILL_LEAFSTORM1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_LEAFSTORM2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_LEAFSTORM3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_LEAFSTORM4, RGB(255, 0, 0));
		atkEnemyAnime.SetDelayCount(2);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(140, 80);
			break;
		case enemy:
			atkAnime.SetTopLeft(420, 240);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillLeafStorm::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_LEAFSTORM);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				return self->GetName() + "decrease great s.atk";
			}
			else {
				isSuccess = false;
				return self->GetName() + "'s attack is miss";
			}
		}
		else { // 跑對話說已經沒pp了並重新選擇技能
			return self->GetName() + "have no pp";
		}
	}

	// private

	string SkillLeafStorm::EffectText(Pokemon *enemy)
	{
		switch (DamageEffect(enemy))
		{
		case superEffe:
			return "super effective";
			break;
		case normalEffe:
			return "";
			break;
		case lowEffe:
			return "not very effective";
			break;
		case notEffe:
			return "not effective";
			break;
		default:
			return "";
		}
	}
}