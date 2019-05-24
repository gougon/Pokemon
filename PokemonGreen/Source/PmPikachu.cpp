#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "PmPikachu.h"
#include "SkillFactory.h"
#include "SkillImpact.h"

namespace game_framework {
	PmPikachu::PmPikachu()
	{
		Init("pikachu");
	}

	PmPikachu::PmPikachu(PmType pmtype)
	{
		this->pmtype = pmtype;
		SkillFactory skFactory;
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(impact, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(ember, pmtype)));
		Init("pikachu");
	}

	PmPikachu::PmPikachu(PmType pmtype, string name)
	{
		this->pmtype = pmtype;
		Init(name);
	}

	void PmPikachu::Init(string name)
	{
		LoadBitmap();

		srand((unsigned)time(NULL));
		this->name = name;
		attribute = electric;
		level = 5;			// 需要改，此處先設定level全定為5
		speciesStrength.SetAll(35, 55, 40, 50, 50, 90);
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

	void PmPikachu::LoadBitmap()
	{
		backImg.LoadBitmap(IDB_PM_PIKACHU_BACK, RGB(255, 0, 0));
		frontImg.LoadBitmap(IDB_PM_PIKACHU_FRONT, RGB(255, 0, 0));
		icon.LoadBitmap(IDB_ICON_PM_PIKACHU, RGB(255, 0, 0));
	}
}