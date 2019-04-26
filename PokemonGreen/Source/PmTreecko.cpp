#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "PmTreecko.h"
#include "SkillImpact.h"

namespace game_framework
{
PmTreecko::PmTreecko()
{
    Init("treecko");
}

PmTreecko::PmTreecko(PmType pmtype)
{
    this->pmtype = pmtype;
    Init("treecko");
}

PmTreecko::PmTreecko(PmType pmtype, string name)
{
    this->pmtype = pmtype;
    Init(name);
}

void PmTreecko::Init(string name)
{
    LoadBitmap();
    srand((unsigned)time(NULL));
    this->name = name;
    attribute = grass;
    level = 5;			// 需要改，此處先設定level全定為5
    speciesStrength.SetAll(40, 45, 35, 65, 55, 70);
    individualValue.SetAll(rand() % V, rand() % V, rand() % V, rand() % V, rand() % V, rand() % V);
    effortValue.SetAll(0, 0, 0, 0, 0, 0);
    LoadValue();
    haveItem = false;
    takeItemID = -1;
    hitRate = 1;
    evasionRate = 1;
    needExp = 20;
    nowExp = 5;
    basicExp = 62;
}

void PmTreecko::LoadBitmap()
{
    backImg.LoadBitmap(IDB_PM_TREECKO_BACK, RGB(255, 0, 0));
    frontImg.LoadBitmap(IDB_PM_TREECKO_FRONT, RGB(255, 0, 0));
    icon.LoadBitmap(IDB_ICON_PM_TREECKO, RGB(255, 255, 255));
}
}