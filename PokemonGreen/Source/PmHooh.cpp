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
#include "SkillFactory.h"
#include "SkillImpact.h"

namespace game_framework {
	PmHooh::PmHooh()
	{
		Init("hooh");
	}

	PmHooh::PmHooh(PmType pmtype)
	{
		this->pmtype = pmtype;
		SkillFactory skFactory;
		skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(impact, pmtype)));
		skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(ember, pmtype)));
		skillTree.insert(pair<int, Skill*>(15, skFactory.CreateSkill(flamethrower, pmtype)));
		skillTree.insert(pair<int, Skill*>(18, skFactory.CreateSkill(phychoboost, pmtype)));
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
		level = 5;			// 需要改，此處先設定level全定為5
		speciesStrength.SetAll(106, 130, 90, 110, 154, 90);
		individualValue.SetAll(rand() % V, rand() % V, rand() % V, rand() % V, rand() % V, rand() % V);
		effortValue.SetAll(0, 0, 0, 0, 0, 0);
		haveItem = false;
		takeItemID = -1;
		LoadValue();
		hitRate = 1;
		evasionRate = 1;
		needExp = 20;
		nowExp = 5;
		basicExp = 220;
		LearnSkill();
	}

	void PmHooh::LoadBitmap()
	{
		backImg.LoadBitmap(IDB_PM_HOOH_BACK, RGB(255, 0, 0));
		frontImg.LoadBitmap(IDB_PM_HOOH_FRONT, RGB(255, 0, 0));
		icon.LoadBitmap(IDB_ICON_PM_HOOH, RGB(255, 0, 0));
	}
}