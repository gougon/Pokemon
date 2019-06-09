#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillScaryFace.h"

namespace game_framework {
	SkillScaryFace::SkillScaryFace(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillScaryFace::Init()
	{
		name = "scary face";
		description = "use scary face stare your enemy;let him frighten";
		category = status;
		power = 0;
		allpp = 10;
		remainpp = 10;
		hitRate = 1.0f;
		attachRate = 0.5f;

		animeCount = 0;
		atkAnime.AddBitmap(IDB_SKILL_SCARYFACE1, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SCARYFACE2, RGB(255, 0, 0));
		atkAnime.AddBitmap(IDB_SKILL_SCARYFACE3, RGB(255, 0, 0));
		atkAnime.SetDelayCount(4);
		atkEnemyAnime.AddBitmap(IDB_SKILL_SCARYFACE1, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_SCARYFACE2, RGB(255, 0, 0));
		atkEnemyAnime.AddBitmap(IDB_SKILL_SCARYFACE3, RGB(255, 0, 0));
		atkEnemyAnime.SetDelayCount(4);

		switch (pmstyle)
		{
		case my:
			atkAnime.SetTopLeft(400, 10);
			break;
		case enemy:
			atkEnemyAnime.SetTopLeft(105, 180);
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	string SkillScaryFace::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // �ޯ��٦��Ѿl
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // �R��
				isSuccess = true;
				CAudio::Instance()->Play(AUDIO_SCARYFACE);
				if ((int)(attachRate * 100) > rnd) {
					enemy->SetStatus(statuParalysis);
					return enemy->GetName() + "is scared";
				}
				return "no effect";
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
}