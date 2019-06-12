#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillSwift.h"

namespace game_framework {
	SkillSwift::SkillSwift(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillSwift::Init()
	{
		name = "swift";
		description = "shoot a star of light;to attack enemy.";
		category = special;
		power = 60;
		allpp = 20;
		remainpp = 20;
		hitRate = 1.0f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_SWIFT1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SWIFT2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SWIFT3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SWIFT4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SWIFT5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SWIFT6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SWIFT7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SWIFT8, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_SKILL_SWIFT8, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_SWIFT7, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_SWIFT6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_SWIFT5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_SWIFT4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_SWIFT3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_SWIFT2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_SWIFT1, RGB(255, 0, 0));
		atkEnemyAnime.SetDelayCount(2);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(155, 85);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(155, 85);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillSwift::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_SWIFT);
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

	string SkillSwift::EffectText(Pokemon *enemy)
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