#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "WeiBaiMap.h"
#include "WeiBaiHouse1_1F_Map.h"
#include "WeiBaiHouse2_1F_Map.h"
#include "WeiBaiProHouse_Map.h"
#include "AtkInterface.h"
#include "Pokemon.h"
#include "PokemonFactory.h"
#include "PmTreecko.h"
#include "Skill.h"
#include "SkillFactory.h"
#include "SkillImpact.h"

namespace game_framework
{
WeiBaiMap::WeiBaiMap(CEvent* gameEvent) : CMap(12) // sceneNum
{
    mapGameEvent = gameEvent;

    for (int i = 0; i < 10; i++)
        TRACE("Event%d : %d\n", i, mapGameEvent->CheckOccured(i));

    InitMap();
}



void WeiBaiMap::InitMap()
{
    SetMXY(48, 62);
    SetXY(18 * SM, 33 * SM);
    SetMap("area1");
    dialogBox.InitDialog('n');

    if (!mapGameEvent->CheckOccured(WeibaiTown_pick_Pokemomball)) pickable_Antidote.SetXY(1380, 1980);

    inEvent = false;
}

void WeiBaiMap::LoadBitmap()
{
    scene[GREEN_GRASS].LoadBitmap(IDB_GREEN_GRASS);
    scene[GREEN_TREE].LoadBitmap(IDB_GREEN_TREE, RGB(255, 0, 0));
    scene[GREEN_FLOWER].LoadBitmap(IDB_GREEN_FLOWER);
    scene[GRASS_LAND].LoadBitmap(IDB_GRASS_LAND);
    scene[BILLBOARD].LoadBitmap(IDB_BILLBOARD);
    scene[WEIBAITOWN_HOUSE1].LoadBitmap(IDB_WEIBAITOWN_HOUSE1);
    scene[WEIBAITOWN_HOUSE2].LoadBitmap(IDB_WEIBAITOWN_HOUSE2);
    scene[WEIBAITOWN_PRO_HOUSE].LoadBitmap(IDB_WEIBAITOWN_PRO_HOUSE);
    scene[M_GREEN_GRASS].LoadBitmap(IDB_M_GREEN_GRASS);
    scene[JUMP_LAND].LoadBitmap(IDB_JUMP_LAND);

    /////////////////////////////
    if (!mapGameEvent->CheckOccured(WeibaiTown_pick_Pokemomball))
        pickable_Antidote.LoadBitmap();
}

void WeiBaiMap::OnShow()
{
    int sx = GetSX();
    int sy = GetSY();

    for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount)
    {
        for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount)
        {
            switch (map[j / SM][i / SM])
            {
                case NONE_HIT:
                    break;

                case NONE_EMPTY:
                    break;

                case ENTRANCE:
                    break;

                case GREEN_GRASS:
                    scene[GREEN_GRASS].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
                    scene[GREEN_GRASS].ShowBitmap();
                    break;

                case GREEN_TREE:
                    scene[GREEN_TREE].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM - 15);
                    scene[GREEN_TREE].ShowBitmap();
                    break;

                case GREEN_FLOWER:
                    scene[GREEN_FLOWER].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
                    scene[GREEN_FLOWER].ShowBitmap();
                    break;

                case GRASS_LAND:
                    scene[GRASS_LAND].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
                    scene[GRASS_LAND].ShowBitmap();
                    break;

                case BILLBOARD:
                    scene[BILLBOARD].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
                    scene[BILLBOARD].ShowBitmap();
                    break;

                case WEIBAITOWN_HOUSE1:
                    scene[WEIBAITOWN_HOUSE1].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
                    scene[WEIBAITOWN_HOUSE1].ShowBitmap();
                    break;

                case WEIBAITOWN_HOUSE2:
                    scene[WEIBAITOWN_HOUSE2].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
                    scene[WEIBAITOWN_HOUSE2].ShowBitmap();
                    break;

                case WEIBAITOWN_PRO_HOUSE:
                    scene[WEIBAITOWN_PRO_HOUSE].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
                    scene[WEIBAITOWN_PRO_HOUSE].ShowBitmap();
                    break;

                case M_GREEN_GRASS:
                    scene[M_GREEN_GRASS].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
                    scene[M_GREEN_GRASS].ShowBitmap();
                    break;

                case JUMP_LAND:
                    scene[JUMP_LAND].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
                    scene[JUMP_LAND].ShowBitmap();
                    break;

                default:
                    ASSERT(0);
                    break;
            }

            if (!mapGameEvent->CheckOccured(WeibaiTown_pick_Pokemomball))
                pickable_Antidote.OnShow(sx, sy);
        }
    }

    if (inEvent) dialogBox.OnShow();
}

bool WeiBaiMap::IsCollision(int x, int y)
{
    x /= SM;
    y /= SM;

    for (auto i : hitImg)
    {
        //TRACE("hitimg[i] = %d\nmap[y][x] = %d\n", i, map[y][x]);
        if (map[y][x] == i)
            return true;
    }

    return false;
}

bool WeiBaiMap::IsWarZone(int x, int y)
{
    x /= SM;
    y /= SM;

    //TRACE("\nx = %d, y = %d\n", x, y);
    for (auto i : warZone)
    {
        if (map[y][x] == i)
            return true;
    }

    return false;
}

void WeiBaiMap::ProduceEnemy(CHero* hero, AtkInterface &atkInterface)
{
    int x = hero->GetX1() / SM;
    int y = hero->GetY1() / SM;
    // 利用atkProb判斷有沒有遇到怪
    int rnd = rand() % hero->GetAtkProb() + 1;

    //TRACE("\nprob = %d, rnd = %d\n", hero->GetAtkProb(), rnd);
    if (rnd == hero->GetAtkProb())  	// 遇到怪
    {
        PokemonFactory pmfactory;
        SkillFactory skfactory;
        Pokemon* enemy = pmfactory.CreateEnemy(treecko);
        enemy->AddSkill(skfactory.CreateSkill(impact, styleEnemy));
        StartAtk(hero, enemy, atkInterface);
    }
}

CMap* WeiBaiMap::ChangeMap(int x, int y, CHero* hero)
{
    x /= SM;
    y /= SM;
    CMap* newMap;

    if (x == 19 && y == 36)
    {
        newMap = new WeiBaiHouse1_1F_Map(mapGameEvent);
    }
    else if (x == 28 && y == 36)
    {
        newMap = new WeiBaiHouse2_1F_Map(mapGameEvent);
    }
    else if (x == 21 && y == 44)
    {
        newMap = new WeiBaiProHouse_Map(mapGameEvent);
    }

    newMap->LoadBitmap();
    return newMap;
}

void WeiBaiMap::StartAtk(CHero* self, Pokemon* enemy, AtkInterface &atkInterface)
{
    atkInterface.Init(self, enemy);
    atkInterface.Start();
}
int WeiBaiMap::CheckID(int x, int y, int herodirection)
{
    x /= SM;
    y /= SM;

    if (pickable_Antidote.GetX() / SM == x && pickable_Antidote.GetY() / SM == y)
    {
        if (inEvent)
        {
            inEvent = false;
            return 0;
        }
        else
        {
            if (!mapGameEvent->CheckOccured(WeibaiTown_pick_Pokemomball))
            {
                mapGameEvent->Occur(WeibaiTown_pick_Pokemomball);
                dialogBox.SetText("pick the smallvulnerary");
                inEvent = true;
            }
            else
            {
                return 0;
            }
        }

        return WeibaiTown_pick_Pokemomball;
    }

    return inEvent;
}
}