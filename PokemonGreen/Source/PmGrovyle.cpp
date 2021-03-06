#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "PmGrovyle.h"
#include "SkillFactory.h"
#include "SkillImpact.h"

namespace game_framework {
	PmGrovyle::PmGrovyle()
	{
		Init("grovyle");
	}

	PmGrovyle::PmGrovyle(PmType pmtype)
	{
		this->pmtype = pmtype;
		SkillFactory skFactory;
		skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(impact, pmtype)));
		skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(leer, pmtype)));
		skillTree.insert(pair<int, Skill*>(10, skFactory.CreateSkill(leafblade, pmtype)));
		skillTree.insert(pair<int, Skill*>(40, skFactory.CreateSkill(leafstorm, pmtype)));
		Init("grovyle");
	}

	PmGrovyle::PmGrovyle(PmType pmtype, string name)
	{
		this->pmtype = pmtype;
		Init(name);
	}

	void PmGrovyle::Init(string name)
	{
		LoadBitmap();

		srand((unsigned)time(NULL));
		this->name = name;
		pmID = grovyle;
		attribute = grass;
		level = 16;			// 需要改，此處先設定level全定為5
		speciesStrength.SetAll(50, 65, 45, 85, 65, 95);
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

	void PmGrovyle::LoadBitmap()
	{
		backImg.LoadBitmap(IDB_PM_GROVYLE_BACK, RGB(255, 0, 0));
		frontImg.LoadBitmap(IDB_PM_GROVYLE_FRONT, RGB(255, 0, 0));
		icon.LoadBitmap(IDB_ICON_PM_GROVYLE, RGB(255, 0, 0));
	}
}