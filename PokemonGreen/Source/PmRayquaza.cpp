#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "PmRayquaza.h"
#include "SkillFactory.h"
#include "SkillImpact.h"

namespace game_framework {
	PmRayquaza::PmRayquaza()
	{
		Init("rayquaza");
	}

	PmRayquaza::PmRayquaza(PmType pmtype)
	{
		this->pmtype = pmtype;
		SkillFactory skFactory;
		skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(leer, pmtype)));
		skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(dragonclaw, pmtype)));
		skillTree.insert(pair<int, Skill*>(8, skFactory.CreateSkill(crunch, pmtype)));
		skillTree.insert(pair<int, Skill*>(20, skFactory.CreateSkill(hyperbeam, pmtype)));
		Init("rayquaza");
	}

	PmRayquaza::PmRayquaza(PmType pmtype, string name)
	{
		this->pmtype = pmtype;
		Init(name);
	}

	void PmRayquaza::Init(string name)
	{
		LoadBitmap();

		srand((unsigned)time(NULL));
		this->name = name;
		pmID = rayquaza;
		attribute = dragon;
		level = 5;			// 需要改，此處先設定level全定為5
		speciesStrength.SetAll(105, 150, 90, 150, 90, 95);
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

	void PmRayquaza::LoadBitmap()
	{
		backImg.LoadBitmap(IDB_PM_RAYQUAZA_BACK, RGB(255, 0, 0));
		frontImg.LoadBitmap(IDB_PM_RAYQUAZA_FRONT, RGB(255, 0, 0));
		icon.LoadBitmap(IDB_ICON_PM_RAYQUAZA, RGB(255, 0, 0));
	}
}