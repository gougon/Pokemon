#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "PmHooh.h"
#include "SkillImpact.h"

namespace game_framework {
	PmHooh::PmHooh()
	{
		Init("hooh");
	}

	PmHooh::PmHooh(PmType pmtype)
	{
		this->pmtype = pmtype;
		Init("hooh");
	}

	PmHooh::PmHooh(PmType pmtype, string name)
	{
		this->pmtype = pmtype;
		Init(name);
	}

	void PmHooh::Init(string name)
	{
		LoadBitmap();

		srand((unsigned)time(NULL));
		this->name = name;
		attribute = fire;
		level = 5;			// �ݭn��A���B���]�wlevel���w��5
		speciesStrength.SetAll(106, 130, 90, 110, 154, 90);
		individualValue.SetAll(rand() % V, rand() % V, rand() % V, rand() % V, rand() % V, rand() % V);
		effortValue.SetAll(0, 0, 0, 0, 0, 0);
		LoadValue();
		hitRate = 1;
		evasionRate = 1;
		needExp = 20;
		nowExp = 5;
		basicExp = 220;
	}

	void PmHooh::LoadBitmap()
	{
		backImg.LoadBitmap(IDB_PM_HOOH_BACK, RGB(255, 0, 0));
		frontImg.LoadBitmap(IDB_PM_HOOH_FRONT, RGB(255, 0, 0));
		icon.LoadBitmap(IDB_ICON_PM_HOOH, RGB(255, 0, 0));
	}
}