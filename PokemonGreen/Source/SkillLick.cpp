#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillLick.h"

namespace game_framework {
	SkillLick::SkillLick(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillLick::Init()
	{
		name = "lick";
		description = "use long tongue to lick;your enemy";
		category = physical;
		power = 30;
		allpp = 30;
		remainpp = 30;
		hitRate = 1.0f;
		attachRate = 0.5f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_LICK1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LICK2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LICK3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LICK4, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_SKILL_LICK1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_LICK2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_LICK3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_LICK4, RGB(255, 0, 0));
		atkEnemyAnime.SetDelayCount(2);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(430, 60);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(130, 240);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillLick::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_LICK);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				if ((int)(attachRate * 100) > rnd)
					enemy->SetStatus(statuParalysis);
					return enemy->GetName() + "be captived";
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

	string SkillLick::EffectText(Pokemon *enemy)
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