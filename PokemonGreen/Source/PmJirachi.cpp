#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "PmJirachi.h"
#include "SkillFactory.h"

namespace game_framework {
	PmJirachi::PmJirachi()
	{
		Init("jirachi");
	}

	PmJirachi::PmJirachi(PmType pmtype)
	{
		this->pmtype = pmtype;
		SkillFactory skFactory;
		skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(impact, pmtype)));
		skillTree.insert(pair<int, Skill*>(7, skFactory.CreateSkill(leer, pmtype)));
		Init("jirachi");
	}

	PmJirachi::PmJirachi(PmType pmtype, string name)
	{
		this->pmtype = pmtype;
		Init(name);
	}

	void PmJirachi::Init(string name)
	{
		LoadBitmap();

		srand((unsigned)time(NULL));
		this->name = name;
		attribute = psychic;
		level = 5;			// 需要改，此處先設定level全定為5
		speciesStrength.SetAll(100, 100, 100, 100, 100, 100);
		individualValue.SetAll(rand() % V, rand() % V, rand() % V, rand() % V, rand() % V, rand() % V);
		effortValue.SetAll(0, 0, 0, 0, 0, 0);
		LoadValue();
		hitRate = 1;
		evasionRate = 1;
		needExp = 20;
		nowExp = 5;
		basicExp = 215;
		LearnSkill();
	}

	void PmJirachi::LoadBitmap()
	{
		backImg.LoadBitmap(IDB_PM_JIRACHI_BACK, RGB(255, 0, 0));
		frontImg.LoadBitmap(IDB_PM_JIRACHI_FRONT, RGB(255, 0, 0));
		icon.LoadBitmap(IDB_ICON_PM_JIRACHI, RGB(255, 0, 0));
	}
}