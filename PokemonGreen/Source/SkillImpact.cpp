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
	SkillImpact::SkillImpact(pmStyle pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillImpact::Init()
	{
		name = "Impact";
		category = physical;
		power = 35;
		allpp = 35;
		remainpp = 35;
		hitRate = 0.95f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_IMPACT1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_IMPACT2, RGB(255, 0, 0));

		switch (pmstyle)
		{
		case styleSelf:
			atkAnime.SetTopLeft(410, 70);
			break;
		case styleEnemy:
			atkAnime.SetTopLeft(200, 260);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	void SkillImpact::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
			}
		}
		else { // 跑對話說已經沒pp了並重新選擇技能

		}
	}

	bool SkillImpact::AtkAnimeOnMove()
	{
		atkAnime.OnMove();
		if (atkAnime.GetCurrentBitmapNumber() == 1) {
			++animeCount;
		}
		if (animeCount == 20) {
			animeCount = 0;
		}
		return (animeCount == 0 && atkAnime.GetCurrentBitmapNumber() == 1);
	}

	void SkillImpact::AtkAnimeOnShow()
	{
		atkAnime.OnShow();
	}
}