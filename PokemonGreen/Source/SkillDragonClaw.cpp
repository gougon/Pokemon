#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillDragonClaw.h"

namespace game_framework {
	SkillDragonClaw::SkillDragonClaw(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillDragonClaw::Init()
	{
		name = "dragon claw";
		description = "use your sharp giant claws;to open enemy and attack";
		category = physical;
		power = 80;
		allpp = 15;
		remainpp = 15;
		hitRate = 1.0f;

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
			atkAnime.SetTopLeft(405, 35);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(105, 215);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillDragonClaw::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // �ޯ��٦��Ѿl
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // �R��
				CAudio::Instance()->Play(AUDIO_CLAW);
				isSuccess = true;
				int enehp = enemy->GetRemainHP();
				enehp = (enehp - Damage(self, enemy) < 0) ? 0 : enehp - Damage(self, enemy);
				enemy->SetRemainHP(enehp);
				return EffectText(enemy);
			}
			else {
				isSuccess = false;
				return self->GetName() + "'s attack is miss";
			}
		}
		else { // �]��ܻ��w�g�Spp�F�í��s��ܧޯ�
			return self->GetName() + "have no pp";
		}
	}

	// private

	string SkillDragonClaw::EffectText(Pokemon *enemy)
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