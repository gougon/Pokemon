#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "PmMetang.h"
#include "SkillFactory.h"
#include "SkillImpact.h"

namespace game_framework {
	PmMetang::PmMetang()
	{
		Init("metang");
	}

	PmMetang::PmMetang(PmType pmtype)
	{
		this->pmtype = pmtype;
		SkillFactory skFactory;
		skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(impact, pmtype)));
		skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(ember, pmtype)));
		Init("metang");
	}

	PmMetang::PmMetang(PmType pmtype, string name)
	{
		this->pmtype = pmtype;
		Init(name);
	}

	void PmMetang::Init(string name)
	{
		LoadBitmap();

		srand((unsigned)time(NULL));
		this->name = name;
		attribute = steel;
		level = 5;			// 需要改，此處先設定level全定為5
		speciesStrength.SetAll(60, 75, 100, 55, 80, 50);
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

	void PmMetang::LoadBitmap()
	{
		backImg.LoadBitmap(IDB_PM_METANG_BACK, RGB(255, 0, 0));
		frontImg.LoadBitmap(IDB_PM_METANG_FRONT, RGB(255, 0, 0));
		icon.LoadBitmap(IDB_ICON_PM_METANG, RGB(255, 0, 0));
	}
}