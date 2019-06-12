#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillCrunch.h"

namespace game_framework {
	SkillCrunch::SkillCrunch(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillCrunch::Init()
	{
		name = "crunch";
		description = "use your teeth to bite enemy;sometimes reduce enemy's defense.";
		category = physical;
		power = 80;
		allpp = 15;
		remainpp = 15;
		hitRate = 1.0f;
		attachRate = 0.5f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_CRUNCH1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CRUNCH2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CRUNCH3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CRUNCH4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CRUNCH5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CRUNCH6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CRUNCH6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CRUNCH7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_CRUNCH7, RGB(255, 0, 0));
		atkAnime.SetDelayCount(1);
		atkEnemyAnime.AddBitmap(IDB_SKILL_CRUNCH1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CRUNCH2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CRUNCH3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CRUNCH4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CRUNCH5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CRUNCH6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CRUNCH6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CRUNCH7, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_CRUNCH7, RGB(255, 0, 0));
		atkEnemyAnime.SetDelayCount(1);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(385, 0);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(85, 180);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillCrunch::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_CRUNCH);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				if ((int)(attachRate * 100) > rnd) {
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

	string SkillCrunch::EffectText(Pokemon *enemy)
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