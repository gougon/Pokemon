#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillHyperBeam.h"

namespace game_framework {
	SkillHyperBeam::SkillHyperBeam(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillHyperBeam::Init()
	{
		name = "hyper beam";
		description = "attack the opponent;with a strong light.";
		category = special;
		power = 150;
		allpp = 5;
		remainpp = 5;
		hitRate = 1.0f;
		freezeRate = 0.5f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM5, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM6, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM7, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM8, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM9, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM10, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM11, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM12, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM13, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM14, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_HYPERBEAM15, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM3, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM4, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM5, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM6, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM7, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM8, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM9, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM10, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM11, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM12, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM13, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM14, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_ENEMY_SKILL_HYPERBEAM15, RGB(255, 0, 0));
		atkEnemyAnime.SetDelayCount(2);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(155, 85);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(155, 85);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillHyperBeam::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // �ޯ��٦��Ѿl
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // �R��
				CAudio::Instance()->Play(AUDIO_HYPERBEAM);
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

	string SkillHyperBeam::EffectText(Pokemon *enemy)
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