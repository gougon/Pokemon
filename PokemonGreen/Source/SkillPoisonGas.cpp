#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillPoisonGas.h"

namespace game_framework {
	SkillPoisonGas::SkillPoisonGas(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillPoisonGas::Init()
	{
		name = "poison gas";
		description = "blow the poison gas to enmey;let enemy get poison";
		category = status;
		power = 0;
		allpp = 40;
		remainpp = 40;
		hitRate = 1.0f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_POISONGAS1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POISONGAS2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POISONGAS3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POISONGAS4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POISONGAS5, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_SKILL_POISONGAS1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_POISONGAS2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_POISONGAS3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_POISONGAS4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_POISONGAS5, RGB(255, 0, 0));
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

	string SkillPoisonGas::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_POISONGAS);
				isSuccess = true;
				enemy->SetStatus(statuPoison);
				if (enemy->GetPmType() == PmType::my)
					enemy->GetStatus()->SetTopLeft(140, 180);
				else
					enemy->GetStatus()->SetTopLeft(145, 85);
				return enemy->GetName() + " is cover in poison gas";
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