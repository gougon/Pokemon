#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "SkillDragon.h"

namespace game_framework {
	SkillDragon::SkillDragon()
	{
		attribute = dragon;
	}

	int SkillDragon::Damage(Pokemon *self, Pokemon *enemy)
	{
		double damage = ((2 * (double)self->GetLevel() + 10) / 250);
		switch (category)
		{
		case physical:
			damage *= ((double)self->GetRemainAtk() / (double)enemy->GetRemainDef());
			break;
		case special:
			damage *= ((double)self->GetRemainSatk() / (double)enemy->GetRemainSdef());
			break;
		case status:
			damage = (double)power;
			return power;
			break;
		default:
			ASSERT(0);
			break;
		}
		damage = damage * power + 2;
		switch (enemy->GetAttribute())
		{
		case normal:
			damage *= 1;
			break;
		case fighting:
			damage *= 1;
			break;
		case flying:
			damage *= 1;
			break;
		case poison:
			damage *= 1;
			break;
		case ground:
			damage *= 1;
			break;
		case rock:
			damage *= 1;
			break;
		case bug:
			damage *= 1;
			break;
		case ghost:
			damage *= 1;
			break;
		case steel:
			damage *= (1 / 2);
			break;
		case fire:
			damage *= 1;
			break;
		case water:
			damage *= 1;
			break;
		case grass:
			damage *= 1;
			break;
		case electric:
			damage *= 1;
			break;
		case psychic:
			damage *= 1;
			break;
		case ice:
			damage *= 1;
			break;
		case dragon:
			damage *= 2;
			break;
		case dark:
			damage *= 1;
			break;
		default:
			ASSERT(0);
			break;
		}
		TRACE("\ndamege = %d\n", (int)damage);
		return ((int)damage <= 0) ? 1 : (int)damage;
	}

	AttrDamage SkillDragon::DamageEffect(Pokemon *enemy)
	{
		if (enemy->GetAttribute() == steel
			) {
			return lowEffe;
		}
		else if (enemy->GetAttribute() == dragon
			) {
			return superEffe;
		}
		else {
			return normalEffe;
		}
	}
}