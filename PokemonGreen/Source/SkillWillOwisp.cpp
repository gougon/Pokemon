#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillWillOwisp.h"

namespace game_framework {
	SkillWillOwisp::SkillWillOwisp(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillWillOwisp::Init()
	{
		name = "will o wisp";
		description = "release a weird flame that will;put enemy in a burn";
		category = status;
		power = 0;
		allpp = 15;
		remainpp = 15;
		hitRate = 1.0f;

		animeCount = 0;
		//add anime
		atkAnime.SetDelayCount(2);
		//add enemy anime
		atkEnemyAnime.SetDelayCount(2);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(205, 195);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(405, 120);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillWillOwisp::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_EMBER);
				isSuccess = true;
				enemy->SetStatus(statuBurn);
				if (enemy->GetPmType() == PmType::my)
					enemy->GetStatus()->SetTopLeft(140, 180);
				else
					enemy->GetStatus()->SetTopLeft(250, 120);
				return enemy->GetName() + "is in burn";
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