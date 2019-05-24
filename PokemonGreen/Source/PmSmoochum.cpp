#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "PmSmoochum.h"
#include "SkillFactory.h"
#include "SkillImpact.h"

namespace game_framework {
	PmSmoochum::PmSmoochum()
	{
		Init("smoochum");
	}

	PmSmoochum::PmSmoochum(PmType pmtype)
	{
		this->pmtype = pmtype;
		SkillFactory skFactory;
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(impact, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(ember, pmtype)));
		Init("smoochum");
	}

	PmSmoochum::PmSmoochum(PmType pmtype, string name)
	{
		this->pmtype = pmtype;
		Init(name);
	}

	void PmSmoochum::Init(string name)
	{
		LoadBitmap();

		srand((unsigned)time(NULL));
		this->name = name;
		attribute = ice;
		level = 5;			// 需要改，此處先設定level全定為5
		speciesStrength.SetAll(45, 30, 15, 85, 65, 65);
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

	void PmSmoochum::LoadBitmap()
	{
		backImg.LoadBitmap(IDB_PM_SMOOCHUM_BACK, RGB(255, 0, 0));
		frontImg.LoadBitmap(IDB_PM_SMOOCHUM_FRONT, RGB(255, 0, 0));
		icon.LoadBitmap(IDB_ICON_PM_SMOOCHUM, RGB(255, 0, 0));
	}
}