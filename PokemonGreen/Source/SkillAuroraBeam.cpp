#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillAuroraBeam.h"

namespace game_framework {
	SkillAuroraBeam::SkillAuroraBeam(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillAuroraBeam::Init()
	{
		name = "aurora beam";
		description = "iris beam is emitted to the enmey;sometimes will reduce enmey attack.";
		category = special;
		power = 65;
		allpp = 20;
		remainpp = 20;
		hitRate = 1.0f;
		attachRate = 0.5f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_AURORABEAM1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_AURORABEAM2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_AURORABEAM3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_AURORABEAM4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_AURORABEAM5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_AURORABEAM6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_AURORABEAM7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_AURORABEAM8, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_AURORABEAM9, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_SKILL_AURORABEAM3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_AURORABEAM2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_AURORABEAM1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_AURORABEAM6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_AURORABEAM5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_AURORABEAM4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_AURORABEAM9, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_AURORABEAM8, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_AURORABEAM7, RGB(255, 0, 0));
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

	string SkillAuroraBeam::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_AURORABEAM);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				if ((int)(attachRate * 100) > rnd) {
					int enedeflv = enemy->GetAtkLevel();
					if (enedeflv > -6) {
						enemy->SetRemainAtk(enedeflv - 1);
						return enemy->GetName() + "'s atk be decreased";
					}
					else {	// 跑對話說已經降到最低了
						
						return enemy->GetName() + "'s atk cannot be decreased";
					}
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

	string SkillAuroraBeam::EffectText(Pokemon *enemy)
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