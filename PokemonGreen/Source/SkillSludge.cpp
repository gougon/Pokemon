#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillSludge.h"

namespace game_framework {
	SkillSludge::SkillSludge(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillSludge::Init()
	{
		name = "sludge";
		description = "throw sludge to your enemy;sometime let enemy get poison";
		category = special;
		power = 65;
		allpp = 20;
		remainpp = 20;
		hitRate = 1.0f;
		poisonRate = 0.5f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE8, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE9, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE10, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE11, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE12, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE13, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE14, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SLUDGE15, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE7, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE8, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE9, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE10, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE11, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE12, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE13, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE14, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_SLUDGE15, RGB(255, 0, 0));
		atkEnemyAnime.SetDelayCount(2);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(145, 85);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(145, 85);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillSludge::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_SLUDGE);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				if ((int)(poison * 100) > rnd) {
					enemy->SetStatus(statuPoison);
					if (enemy->GetPmType() == PmType::my)
						enemy->GetStatus()->SetTopLeft(140, 180);
					else
						enemy->GetStatus()->SetTopLeft(250, 120);
					return enemy->GetName() + " is cover by sludeg";
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

	string SkillSludge::EffectText(Pokemon *enemy)
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