#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillBubbleBeam.h"

namespace game_framework {
	SkillBubbleBeam::SkillBubbleBeam(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillBubbleBeam::Init()
	{
		name = "bubble beam";
		description = "spray the bubble to enemy;sometimes reduce the speed of enemy.";
		category = special;
		power = 65;
		allpp = 20;
		remainpp = 20;
		hitRate = 1.0f;
		attachRate = 0.5f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_BUBBLEBEAM1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_BUBBLEBEAM2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_BUBBLEBEAM3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_BUBBLEBEAM4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_BUBBLEBEAM5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_BUBBLEBEAM6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_BUBBLEBEAM7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_BUBBLEBEAM8, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_BUBBLEBEAM9, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_BUBBLEBEAM10, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_BUBBLEBEAM1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_BUBBLEBEAM2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_BUBBLEBEAM3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_BUBBLEBEAM4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_BUBBLEBEAM5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_BUBBLEBEAM6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_BUBBLEBEAM7, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_BUBBLEBEAM8, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_BUBBLEBEAM9, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_BUBBLEBEAM10, RGB(255, 0, 0));
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

	string SkillBubbleBeam::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_BUBBLEBEAM);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				if ((int)(attachRate * 100) > rnd) {
					int enedeflv = enemy->GetSpeedLevel();
					if (enedeflv > -6) {
						CAudio::Instance()->Play(AUDIO_LEER);
						enemy->SetRemainSpeed(enedeflv - 1);
						return enemy->GetName() + "'s speed be decreased";
					}
					else {	// 跑對話說已經降到最低了
						CAudio::Instance()->Play(AUDIO_LEERNE);
						return enemy->GetName() + "'s speed cannot be decreased";
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

	string SkillBubbleBeam::EffectText(Pokemon *enemy)
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