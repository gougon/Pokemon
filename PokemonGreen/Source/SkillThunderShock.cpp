#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillThunderShock.h"

namespace game_framework {
	SkillThunderShock::SkillThunderShock(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillThunderShock::Init()
	{
		name = "thundershock";
		description = "use current sent to enemy;sometimes enemy is paralyzed";
		category = special;
		power = 40;
		allpp = 30;
		remainpp = 30;
		hitRate = 1.0f;
		attachRate = 0.5f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK8, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK7, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_THUNDERSHOCK8, RGB(255, 0, 0));
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

	string SkillThunderShock::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_PARALYSIS);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				if ((int)(attachRate * 100) > rnd) {
					enemy->SetStatus(statuParalysis);
					if (enemy->GetPmType() == PmType::my)
						enemy->GetStatus()->SetTopLeft(140, 180);
					else
						enemy->GetStatus()->SetTopLeft(250, 120);
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

	string SkillThunderShock::EffectText(Pokemon *enemy)
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