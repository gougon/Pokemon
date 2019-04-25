#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "WeiBaiHouse2_1F_Map.h"
#include "WeiBaiMap.h"
#include "WeiBaiHouse2_2F_Map.h"

namespace game_framework
{
WeiBaiHouse2_1F_Map::WeiBaiHouse2_1F_Map(CEvent* gameEvent) : CMap(3) // sceneNum
{
    mapGameEvent = gameEvent;
    InitMap();
}

void WeiBaiHouse2_1F_Map::InitMap()
{
    SetMXY(39, 37);
    SetXY(11 * SM, 18 * SM);
    SetMap("weibaitown_house2_1f");
}

void WeiBaiHouse2_1F_Map::LoadBitmap()
{
    scene[WEIBAITOWN_HOUSE2_1F].LoadBitmap(IDB_WEIBAITOWN_HOUSE2_1F);
}

void WeiBaiHouse2_1F_Map::OnShow()
{
    int sx = GetSX();
    int sy = GetSY();

    for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount)
    {
        for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount)
        {
            switch (map[j / SM][i / SM])
            {
                case NONE_HIT:
                    break;

                case NONE_EMPTY:
                    break;

                case ENTRANCE:
                    break;

                case WEIBAITOWN_HOUSE2_1F:
                    scene[WEIBAITOWN_HOUSE2_1F].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
                    scene[WEIBAITOWN_HOUSE2_1F].ShowBitmap();
                    break;

                default:
                    ASSERT(0);
                    break;
            }
        }
    }
}

bool WeiBaiHouse2_1F_Map::IsCollision(int x, int y)
{
    x /= SM;
    y /= SM;

    for (auto i : hitImg)
    {
        if (map[y][x] == i)
            return true;
    }

    return false;
}

CMap* WeiBaiHouse2_1F_Map::ChangeMap(int x, int y, CHero* hero)
{
    x /= SM;
    y /= SM;
    CMap* newMap;

    if (x == 15 && y == 23)
    {
        newMap = new WeiBaiMap(mapGameEvent);
        newMap->SetXY(23 * SM, 57 * SM);
    }
    else if (x == 16 && y == 23)
    {
        newMap = new WeiBaiMap(mapGameEvent);
        newMap->SetXY(23 * SM, 57 * SM);
    }
    else if (x == 16 && y == 16)
    {
        newMap = new WeiBaiHouse2_2F_Map(mapGameEvent);
        newMap->SetXY(10 * SM, 12 * SM);
    }

    newMap->LoadBitmap();
    return newMap;
}
}