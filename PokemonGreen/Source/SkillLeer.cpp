#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillLeer.h"

namespace game_framework {
	SkillLeer::SkillLeer(pmStyle pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillLeer::Init()
	{
		name = "leer";
		description = "frighten the enemy and;make its def fall";
		category = status;
		power = 0;
		allpp = 30;
		remainpp = 30;
		hitRate = 1.0f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_LEER1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEER2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEER3, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEER4, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_LEER5, RGB(255, 0, 0));
		atkAnime.SetDelayCount(2);

		switch (pmstyle)
		{
		case styleSelf:
			atkAnime.SetTopLeft(205, 195);
			break;
		case styleEnemy:
			atkAnime.SetTopLeft(405, 120);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillLeer::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // �ޯ��٦��Ѿl
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // �R��
				int enedeflv = enemy->GetDefLevel();
				if (enedeflv > -6) {
					enemy->SetRemainDef(enedeflv - 1);
					return enemy->GetName() + "'s def be decreased";
				}
				else {	// �]��ܻ��w�g����̧C�F
					return enemy->GetName() + "'s def cannot be decreased";
				}
			}
			else {
				return self->GetName() + "'s attack is miss";
			}
		}
		else { // �]��ܻ��w�g�Spp�F�í��s��ܧޯ�
			return self->GetName() + "have no pp";
		}
	}

	bool SkillLeer::AtkAnimeOnMove()
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

	void SkillLeer::AtkAnimeOnShow()
	{
		atkAnime.OnShow();
	}
}