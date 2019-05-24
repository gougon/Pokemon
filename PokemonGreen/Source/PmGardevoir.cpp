#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "PmGardevoir.h"
#include "SkillFactory.h"
#include "SkillImpact.h"

namespace game_framework {
	PmGardevoir::PmGardevoir()
	{
		Init("gardevoir");
	}

	PmGardevoir::PmGardevoir(PmType pmtype)
	{
		this->pmtype = pmtype;
		SkillFactory skFactory;
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(impact, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(ember, pmtype)));
		Init("gardevoir");
	}

	PmGardevoir::PmGardevoir(PmType pmtype, string name)
	{
		this->pmtype = pmtype;
		Init(name);
	}

	void PmGardevoir::Init(string name)
	{
		LoadBitmap();

		srand((unsigned)time(NULL));
		this->name = name;
		attribute = psychic;
		level = 5;			// 需要改，此處先設定level全定為5
		speciesStrength.SetAll(68, 65, 65, 125, 115, 80);
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

	void PmGardevoir::LoadBitmap()
	{
		backImg.LoadBitmap(IDB_PM_GARDEVOIR_BACK, RGB(255, 0, 0));
		frontImg.LoadBitmap(IDB_PM_GARDEVOIR_FRONT, RGB(255, 0, 0));
		icon.LoadBitmap(IDB_ICON_PM_GARDEVOIR, RGB(255, 0, 0));
	}
}