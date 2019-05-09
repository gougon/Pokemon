#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillEmber.h"

namespace game_framework {
	SkillEmber::SkillEmber(pmStyle pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillEmber::Init()
	{
		name = "ember";
		description = "use fire to attack enemy;it can let enemy burn";
		category = special;
		power = 40;
		allpp = 25;
		remainpp = 25;
		hitRate = 1.0f;
		burnRate = 0.5f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_EMBER1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER8, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER9, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER10, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER11,  RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER12, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER13, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER14, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER15, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER16, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER17, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_EMBER18, RGB(255, 0, 0));
		atkAnime.SetDelayCount(1);

		switch (pmstyle)
		{
		case styleSelf:
			atkAnime.SetTopLeft(180, 140);
			break;
		case styleEnemy:
			atkAnime.SetTopLeft(405, 120);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillEmber::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // 技能還有剩餘
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // 命中
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				if ((int)(burnRate * 100) > rnd) {
					enemy->SetStatus(statuBurn);
					if(enemy->GetPmType() == PmType::my)
						enemy->GetStatus()->SetTopLeft(140, 180);
					else
						enemy->GetStatus()->SetTopLeft(250, 120);
				}
				return EffectText(enemy);
			}
			else {
				return self->GetName() + "'s attack is miss";
			}
		}
		else { // 跑對話說已經沒pp了並重新選擇技能
			return self->GetName() + "have no pp";
		}
	}

	bool SkillEmber::AtkAnimeOnMove()
	{
		atkAnime.OnMove();
		if (atkAnime.IsFinalBitmap()) {
			animeCount++;
		}
		if (animeCount == 1) {
			animeCount = 0;
			atkAnime.Reset();
			return true;
		}
		else {
			return false;
		}
	}

	void SkillEmber::AtkAnimeOnShow()
	{
		atkAnime.OnShow();
	}

	// private

	string SkillEmber::EffectText(Pokemon *enemy)
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