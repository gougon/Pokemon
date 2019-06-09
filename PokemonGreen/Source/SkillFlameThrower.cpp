#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillFlameThrower.h"

namespace game_framework {
	SkillFlameThrower::SkillFlameThrower(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillFlameThrower::Init()
	{
		name = "flame thrower";
		description = "attack the enemy with a flame;sometimes let enemy in a burn.";
		category = special;
		power = 90;
		allpp = 15;
		remainpp = 15;
		hitRate = 1.0f;
		burnRate = 0.5f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER8, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER9, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER10, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER11, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER10, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER9, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER8, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_FLAMETHROWER7, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_FLAMETHROWER1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_FLAMETHROWER2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_FLAMETHROWER3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_FLAMETHROWER4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_FLAMETHROWER5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_FLAMETHROWER6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_FLAMETHROWER7, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_FLAMETHROWER8, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_FLAMETHROWER7, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_FLAMETHROWER8, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_FLAMETHROWER9, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_FLAMETHROWER10, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_FLAMETHROWER11, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_FLAMETHROWER10, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_FLAMETHROWER9, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_FLAMETHROWER8, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_FLAMETHROWER7, RGB(255, 0, 0));
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

	string SkillFlameThrower::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_FLAMETHROWER);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				if ((int)(burnRate * 100) > rnd) {
					enemy->SetStatus(statuBurn);
					if (enemy->GetPmType() == PmType::my)
						enemy->GetStatus()->SetTopLeft(140, 180);
					else
						enemy->GetStatus()->SetTopLeft(250, 120);
					return enemy->GetName() + "'s full body on fire";
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

	string SkillFlameThrower::EffectText(Pokemon *enemy)
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