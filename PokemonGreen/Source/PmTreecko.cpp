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
#include "SkillFactory.h"

namespace game_framework
{
    PmTreecko::PmTreecko()
    {
        Init("treecko");
    }

    PmTreecko::PmTreecko(PmType pmtype)
    {
        this->pmtype = pmtype;
		SkillFactory skFactory;
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(impact, pmtype)));
		//skillTree.insert(pair<int, Skill*>(7, skFactory.CreateSkill(leer, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(ember, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(confusion, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(metalclaw, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(scaryface, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(lick, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(poisongas, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(powdersnow, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(sludge, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(flamethrower, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(thundershock, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(thunderbolt, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(bubblebeam, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(watergun, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(crunch, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(dragonclaw , pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(leafblade, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(aurorabeam, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(leafstorm, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(nightshade, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(phychoboost, pmtype)));
		//skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(swift, pmtype)));
		skillTree.insert(pair<int, Skill*>(5, skFactory.CreateSkill(hyperbeam, pmtype)));
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
		LearnSkill();
    }

    void PmTreecko::LoadBitmap()
    {
        backImg.LoadBitmap(IDB_PM_TREECKO_BACK, RGB(255, 0, 0));
        frontImg.LoadBitmap(IDB_PM_TREECKO_FRONT, RGB(255, 0, 0));
        icon.LoadBitmap(IDB_ICON_PM_TREECKO, RGB(255, 255, 255));
    }
}
