#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Pokemon.h"

namespace game_framework {
	PmValue::PmValue()
		: hp(0), speed(0), atk(0), def(0), satk(0), sdef(0)
	{
		/* empty body */
	}

	PmValue::PmValue(int hp, int sp, int atk, int def, int sa, int sd) :
		hp(hp), speed(sp), atk(atk), def(def), satk(sa), sdef(sd)
	{
		/* empty body */
	}

	PmValue::PmValue(Pokemon *pm)
	{
		this->hp = pm->GetHP();
		this->atk = pm->GetAtk();
		this->def = pm->GetDef();
		this->satk = pm->GetSatk();
		this->sdef = pm->GetSdef();
		this->speed = pm->GetSpeed();
	}

	PmValue PmValue::operator-(const PmValue& value2)
	{
		PmValue tmp(hp - value2.hp, 
			atk - value2.atk, 
			def - value2.def, 
			satk - value2.satk, 
			sdef - value2.sdef, 
			speed - value2.speed);

		return tmp;
	}

	void PmValue::SetAll(int hp, int atk, int def, int sa, int sd, int sp)
	{
		this->hp = hp;
		this->atk = atk;
		this->def = def;
		this->satk = sa;
		this->sdef = sd;
		this->speed = sp;
	}

	void PmValue::SetAll(Pokemon *pm)
	{
		this->hp = pm->GetHP();
		this->atk = pm->GetAtk();
		this->def = pm->GetDef();
		this->satk = pm->GetSatk();
		this->sdef = pm->GetSdef();
		this->speed = pm->GetSpeed();
	}
}