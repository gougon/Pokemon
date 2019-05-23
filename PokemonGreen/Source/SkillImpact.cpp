#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillImpact.h"

namespace game_framework {
	SkillImpact::SkillImpact(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillImpact::Init()
	{
		name = "impact";
		description = "use whole body to attack enemy";
		category = physical;
		power = 35;
		allpp = 35;
		remainpp = 35;
		hitRate = 0.95f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_IMPACT1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_IMPACT2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_IMPACT1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_IMPACT2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_IMPACT1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_IMPACT2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_IMPACT1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_IMPACT2, RGB(255, 0, 0));

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(410, 70);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(230, 260);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillImpact::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_IMPACT);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				return EffectText(enemy);
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

	string SkillImpact::EffectText(Pokemon *enemy)
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