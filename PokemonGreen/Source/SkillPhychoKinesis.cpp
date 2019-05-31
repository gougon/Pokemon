#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillPhychoKinesis.h"

namespace game_framework {
	SkillPhychoKinesis::SkillPhychoKinesis(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillPhychoKinesis::Init()
	{
		name = "psychokinesis";
		description = "use powerful mind to attack;sometime decrease enemy sdef";
		category = special;
		power = 90;
		allpp = 10;
		remainpp = 10;
		hitRate = 1.0f;
		attachRate = 0.5f;

		animeCount = 0;
		//add anime
		atkAnime.SetDelayCount(2);
		//add enemy anime
		atkEnemyAnime.SetDelayCount(2);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(205, 195);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(405, 120);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillPhychoKinesis::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				if ((int)(attachRate * 100) > rnd) { // 命中
					isSuccess = true;
					int enesdeflv = enemy->GetSdefLevel();
					if (enesdeflv > -6) {
						enemy->SetRemainSdef(enesdeflv - 1);
						return enemy->GetName() + "'s special def be decreased";
					}
					else {	// 跑對話說已經降到最低了
						return enemy->GetName() + "'s special def cannot be decreased";
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
	string SkillPhychoKinesis::EffectText(Pokemon *enemy)
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