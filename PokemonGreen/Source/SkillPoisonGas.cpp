#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "SkillPoisonGas.h"

namespace game_framework {
	SkillPoisonGas::SkillPoisonGas(int pmstyle)
	{
		this->pmstyle = pmstyle;
		Init();
	}

	void SkillPoisonGas::Init()
	{
		name = "poison gas";
		description = "blow the poison gas to enmey;let enemy get poison";
		category = status;
		power = 0;
		allpp = 40;
		remainpp = 40;
		hitRate = 1.0f;

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

	string SkillPoisonGas::Use(Pokemon *self, Pokemon *enemy)
	{
		if (remainpp > 0) { // �ޯ��٦��Ѿl
			--remainpp;
			float realHitRate = hitRate * self->GetHitRate() / enemy->GetEvasionRate();
			int rnd = rand() % 100 + 1;
			if ((int)(realHitRate * 100) > rnd) { // �R��
				CAudio::Instance()->Play(AUDIO_EMBER);
				isSuccess = true;
				enemy->SetStatus(statuPoison);
				if (enemy->GetPmType() == PmType::my)
					enemy->GetStatus()->SetTopLeft(140, 180);
				else
					enemy->GetStatus()->SetTopLeft(250, 120);
				return enemy->GetName() + "is in poison";
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