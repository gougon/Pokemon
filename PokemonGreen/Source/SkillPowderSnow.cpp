#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillPowderSnow.h"

namespace game_framework {
	SkillPowderSnow::SkillPowderSnow(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillPowderSnow::Init()
	{
		name = "powder snow";
		description = "use cold snow cover your enemy;let him freeze";
		category = special;
		power = 40;
		allpp = 25;
		remainpp = 25;
		hitRate = 1.0f;
		freezeRate = 1.0f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW8, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW9, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW10, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW11, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW12, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW13, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW14, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW15, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW16, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW17, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW18, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW19, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW20, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_POWDERSNOW21, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW7, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW8, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW9, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW10, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW11, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW12, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW13, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW14, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW15, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW16, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW17, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW18, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW19, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW20, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW21, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_POWDERSNOW22, RGB(255, 0, 0));
		atkEnemyAnime.SetDelayCount(2);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(140, 80);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(140, 80);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillPowderSnow::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_POWDERSNOW);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				if ((int)(freezeRate * 100) > rnd) {
					enemy->SetStatus(statuFreeze);
					if (enemy->GetPmType() == PmType::my)
						enemy->GetStatus()->SetTopLeft(140, 180);
					else
						enemy->GetStatus()->SetTopLeft(250, 120);
					return enemy->GetName() + "is cover by snow";
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

	// private

	string SkillPowderSnow::EffectText(Pokemon *enemy)
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