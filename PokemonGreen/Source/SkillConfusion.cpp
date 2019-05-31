#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillConfusion.h"

namespace game_framework {
	SkillConfusion::SkillConfusion(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillConfusion::Init()
	{
		name = "confusion";
		description = "use physic power to make;enemy confused";
		category = special;
		power = 50;
		allpp = 25;
		remainpp = 25;
		hitRate = 1.0f;
		confusionRate = 0.5f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_CONFUSION1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CONFUSION2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CONFUSION3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CONFUSION4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CONFUSION5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CONFUSION6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CONFUSION7, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_SKILL_CONFUSION1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CONFUSION2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CONFUSION3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CONFUSION4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CONFUSION5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CONFUSION6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CONFUSION7, RGB(255, 0, 0));
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

	string SkillConfusion::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				isSuccess = true;
				CAudio::Instance()->Play(AUDIO_LEER);
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				if ((int)(confusionRate * 100) > rnd) {
					enemy->SetStatus(statuParalysis);
					if (enemy->GetPmType() == PmType::my) 
						enemy->GetStatus()->SetTopLeft(140, 180);
					else
						enemy->GetStatus()->SetTopLeft(250, 120);
					return enemy->GetName() + "is in paralysis";
				}
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
	string SkillConfusion::EffectText(Pokemon *enemy)
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