#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillLeer.h"

namespace game_framework {
	SkillLeer::SkillLeer(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillLeer::Init()
	{
		name = "leer";
		description = "frighten the enemy and;make its def fall";
		category = status;
		power = 0;
		allpp = 30;
		remainpp = 30;
		hitRate = 1.0f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_LEER1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEER2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEER3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEER4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEER5, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_SKILL_LEER1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_LEER2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_LEER3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_LEER4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_LEER5, RGB(255, 0, 0));
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

	string SkillLeer::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				isSuccess = true;
				int enedeflv = enemy->GetDefLevel();
				if (enedeflv > -6) {
					CAudio::Instance()->Play(AUDIO_LEER);
					enemy->SetRemainDef(enedeflv - 1);
					return enemy->GetName() + "'s def be decreased";
				}
				else {	// 跑對話說已經降到最低了
					CAudio::Instance()->Play(AUDIO_LEERNE);
					return enemy->GetName() + "'s def cannot be decreased";
				}
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