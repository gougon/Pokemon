#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "PmDeoxys.h"
#include "SkillFactory.h"
#include "SkillImpact.h"

namespace game_framework {
	PmDeoxys::PmDeoxys()
	{
		Init("deoxys");
	}

	PmDeoxys::PmDeoxys(PmType pmtype)
	{
		this->pmtype = pmtype;
		SkillFactory skFactory;
		skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(impact, pmtype)));
		skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(ember, pmtype)));
		Init("deoxys");
	}

	PmDeoxys::PmDeoxys(PmType pmtype, string name)
	{
		this->pmtype = pmtype;
		Init(name);
	}

	void PmDeoxys::Init(string name)
	{
		LoadBitmap();

		srand((unsigned)time(NULL));
		this->name = name;
		attribute = psychic;
		level = 5;			// �ݭn��A���B���]�wlevel���w��5
		speciesStrength.SetAll(50, 150, 50, 150, 50, 150);
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

	void PmDeoxys::LoadBitmap()
	{
		backImg.LoadBitmap(IDB_PM_DEOXYS_BACK, RGB(255, 0, 0));
		frontImg.LoadBitmap(IDB_PM_DEOXYS_FRONT, RGB(255, 0, 0));
		icon.LoadBitmap(IDB_ICON_PM_DEOXYS, RGB(255, 0, 0));
	}
}