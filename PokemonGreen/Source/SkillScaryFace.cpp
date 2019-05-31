#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillScaryFace.h"

namespace game_framework {
	SkillScaryFace::SkillScaryFace(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillScaryFace::Init()
	{
		name = "scary face";
		description = "use scary face stare your enemy;let him frighten";
		category = status;
		power = 0;
		allpp = 10;
		remainpp = 10;
		hitRate = 1.0f;
		attachRate = 0.5f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_SCARYFACE1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SCARYFACE2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SCARYFACE3, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkAnime.AddBitmap(IDB_SKILL_SCARYFACE1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SCARYFACE2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SCARYFACE3, RGB(255, 0, 0));
		atkEnemyAnime.SetDelayCount(2);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(405, 120);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(205, 195);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillScaryFace::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_LEER);
				if ((int)(attachRate * 100) > rnd)
					isSuccess = true;
					return enemy->GetName() + "is in paralysis";
				return "no effect";
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