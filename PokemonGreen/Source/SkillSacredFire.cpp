#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillSacredFire.h"

namespace game_framework {
	SkillSacredFire::SkillSacredFire(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillSacredFire::Init()
	{
		name = "sacred fire";
		description = "burn enmey with a mysterious flame;sometimes let enmey in burn.";
		category = physical;
		power = 100;
		allpp = 5;
		remainpp = 5;
		hitRate = 1.0f;
		burnRate = 0.5f;

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

	string SkillSacredFire::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				CAudio::Instance()->Play(AUDIO_EMBER);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				if ((int)(burnRate * 100) > rnd) {
					if(enemy->GetStatus()->GetStatu() == statuFreeze)
						return enemy->GetName() + "freezing is stop";
					else {
						enemy->SetStatus(statuBurn);
						if (enemy->GetPmType() == PmType::my)
							enemy->GetStatus()->SetTopLeft(140, 180);
						else
							enemy->GetStatus()->SetTopLeft(250, 120);
						return enemy->GetName() + "is in burn";
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

	string SkillSacredFire::EffectText(Pokemon *enemy)
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