#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillWaterGun.h"

namespace game_framework {
	SkillWaterGun::SkillWaterGun(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillWaterGun::Init()
	{
		name = "water gun";
		description = "use cold water;spray your enemy";
		category = special;
		power = 40;
		allpp = 25;
		remainpp = 25;
		hitRate = 1.0f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_WATERGUN1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_WATERGUN2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_WATERGUN3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_WATERGUN4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_WATERGUN5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_WATERGUN6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_WATERGUN7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_WATERGUN8, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_WATERGUN9, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_WATERGUN10, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_WATERGUN10, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_WATERGUN10, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_WATERGUN1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_WATERGUN2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_WATERGUN3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_WATERGUN4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_WATERGUN5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_WATERGUN6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_WATERGUN7, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_WATERGUN8, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_WATERGUN9, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_WATERGUN10, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_WATERGUN10, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_WATERGUN10, RGB(255, 0, 0));
		atkEnemyAnime.SetDelayCount(2);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(150, 100);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(140, 100);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillWaterGun::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_WATERGUN);
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

	string SkillWaterGun::EffectText(Pokemon *enemy)
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