#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillNightShade.h"

namespace game_framework {
	SkillNightShade::SkillNightShade(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillNightShade::Init()
	{
		name = "night shade";
		description = "give the opponent the same;level of damage as himself";
		category = special;
		power = 0;
		allpp = 15;
		remainpp = 15;
		hitRate = 1.0f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_NIGHTSHADE1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_NIGHTSHADE2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_NIGHTSHADE3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_NIGHTSHADE4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_NIGHTSHADE5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_NIGHTSHADE6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_NIGHTSHADE7, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_SKILL_NIGHTSHADE1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_NIGHTSHADE2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_NIGHTSHADE3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_NIGHTSHADE4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_NIGHTSHADE5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_NIGHTSHADE6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_NIGHTSHADE7, RGB(255, 0, 0));
		atkEnemyAnime.SetDelayCount(2);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(410, 25);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(110, 205);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillNightShade::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_NIGHTSHADE);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp -= self->GetLevel();
				enemy->SetRemainHP(enehp);
				return "";
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
}