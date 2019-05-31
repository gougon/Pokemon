#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillMetalClaw.h"

namespace game_framework {
	SkillMetalClaw::SkillMetalClaw(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillMetalClaw::Init()
	{
		name = "metal claw";
		description = "use steel of claw cut your enemy;sometime increase atk";
		category = physical;
		power = 50;
		allpp = 35;
		remainpp = 35;
		hitRate = 0.95f;
		attachRate = 0.5f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_METALCLAW1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_METALCLAW2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_METALCLAW3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_METALCLAW4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_METALCLAW5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_METALCLAW6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_METALCLAW7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_METALCLAW8, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_METALCLAW9, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_METALCLAW10, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_SKILL_METALCLAW1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_METALCLAW2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_METALCLAW3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_METALCLAW4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_METALCLAW5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_METALCLAW6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_METALCLAW7, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_METALCLAW8, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_METALCLAW9, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_METALCLAW10, RGB(255, 0, 0));
		atkEnemyAnime.SetDelayCount(2);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(405, 120);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(205, 195);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillMetalClaw::Use(Pokemon *self, Pokemon *enemy)
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
				if ((int)(attachRate * 100) > rnd)
					return self->GetName() + "increase atk";
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

	string SkillMetalClaw::EffectText(Pokemon *enemy)
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