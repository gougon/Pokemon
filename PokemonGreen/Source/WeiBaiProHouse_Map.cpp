#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "WeiBaiMap.h"
#include "WeiBaiProHouse_Map.h"

namespace game_framework
{
WeiBaiProHouse_Map::WeiBaiProHouse_Map(CEvent* gameEvent) : CMap(3) // sceneNum
{
    mapGameEvent = gameEvent;
    InitMap();
}

void WeiBaiProHouse_Map::InitMap()
{
    SetMXY(41, 41);
    SetXY(15 * SM, 22 * SM);
    SetMap("weibaitown_pro_house");
	name = "weibaitown_pro_house";
}

void WeiBaiProHouse_Map::LoadBitmap()
{
    scene[WEIBAITOWN_PRO_HOUSE_INSIDE].LoadBitmap(IDB_WEIBAITOWN_PRO_HOUSE_INSIDE);
}

void WeiBaiProHouse_Map::OnShow()
{
    int sx = GetSX();
    int sy = GetSY();

    for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount)
    {
        for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount)
        {
            switch (map[j / SM][i / SM]) {
                case WEIBAITOWN_PRO_HOUSE_INSIDE:
                    scene[WEIBAITOWN_PRO_HOUSE_INSIDE].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
                    scene[WEIBAITOWN_PRO_HOUSE_INSIDE].ShowBitmap();
                    break;
                default:
                    break;
            }
        }
    }
}

bool WeiBaiProHouse_Map::IsCollision(int x, int y, CHero &hero)
{
    x /= SM;
    y /= SM;

    for (int i = 0; i < 2; ++i)
    {
		if (map[y][x] == hitImg[i])
			return true;
    }

    return false;
}

CMap* WeiBaiProHouse_Map::ChangeMap(int x, int y, CHero* hero)
{
    x /= SM;
    y /= SM;
    CMap* newMap;

    if (x == 20 && y == 27)
    {
        newMap = new WeiBaiMap(mapGameEvent);
        newMap->SetXY(94 * SM, 87 * SM);
    }
    else if (x == 21 && y == 27)
    {
        newMap = new WeiBaiMap(mapGameEvent);
        newMap->SetXY(94 * SM, 87 * SM);
    }

    newMap->LoadBitmap();
    return newMap;
}
}