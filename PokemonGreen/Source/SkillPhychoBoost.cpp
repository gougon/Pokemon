#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillPhychoBoost.h"

namespace game_framework {
	SkillPhychoBoost::SkillPhychoBoost(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillPhychoBoost::Init()
	{
		name = "phycho boost";
		description = "use whole power to attack enemy;decrease self s.atk";
		category = special;
		power = 140;
		allpp = 5;
		remainpp = 5;
		hitRate = 0.9f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST8, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST9, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST10, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST11, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST12, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST13, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST14, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST15, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST16, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST17, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST18, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST19, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST20, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST21, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST22, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST23, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST24, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST25, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST26, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_PHYCHOBOOST27, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST7, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST8, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST9, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST10, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST11, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST12, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST13, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST14, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST15, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST16, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST17, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST18, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST19, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST20, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST21, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST22, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST23, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST24, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST25, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST26, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_PHYCHOBOOST27, RGB(255, 0, 0));
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

	string SkillPhychoBoost::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_PSYCHOBOOST);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				return self->GetName() + "decrease great s.atk";
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
	string SkillPhychoBoost::EffectText(Pokemon *enemy)
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