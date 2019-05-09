#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "WeiBaiHouse1_1F_Map.h"
#include "WeiBaiMap.h"
#include "WeiBaiHouse1_2F_Map.h"
#include "CDialog.h"

namespace game_framework
{
WeiBaiHouse1_1F_Map::WeiBaiHouse1_1F_Map(CEvent* gameEvent) : CMap(3) // sceneNum
{
    mapGameEvent = gameEvent;

    for (int i = 0; i < 10; i++)
        TRACE("Event%d : %d\n", i, mapGameEvent->CheckOccured(i));

    InitMap();
}

void WeiBaiHouse1_1F_Map::OnMove()
{
    dialogBox.OnMove();
    mom.OnMove();
}

void WeiBaiHouse1_1F_Map::InitMap()
{
    SetMXY(39, 37);
    SetXY(17 * SM, 18 * SM);
    SetMap("weibaitown_house1_1f");
    mom.Initialize();
    mom.SetXY(1320, 1060);
    book.SetXY(1020, 960);
    dialogBox.InitDialog('n');
    inEvent = false;
}

void WeiBaiHouse1_1F_Map::LoadBitmap()
{
    scene[WEIBAITOWN_HOUSE1_1F].LoadBitmap(IDB_WEIBAITOWN_HOUSE1_1F);
    mom.LoadBitmap();
}

void WeiBaiHouse1_1F_Map::OnShow()
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
                case WEIBAITOWN_HOUSE1_1F:
                    scene[WEIBAITOWN_HOUSE1_1F].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
                    scene[WEIBAITOWN_HOUSE1_1F].ShowBitmap();
                    break;
                default:
                    ASSERT(0);
                    break;
            }

            //y = j/SM
            //x = i/SM
            //TRACE("SX = %d , SY = %d\n", GetSX(), GetSY());
            mom.OnShow(GetSX(), GetSY());
        }
    }

    if (inEvent) dialogBox.OnShow();
}

bool WeiBaiHouse1_1F_Map::IsCollision(int x, int y)
{
    x /= SM;
    y /= SM;

    for (auto i : hitImg)
    {
		if (map[y][x] == i)
			return true;
    }

    if (mom.GetX() / SM == x  && mom.GetY() / SM  + 1 ==  y) return true;

    return false;
}

CMap* WeiBaiHouse1_1F_Map::ChangeMap(int x, int y, CHero* hero)
{
    x /= SM;
    y /= SM;
    CMap* newMap;

    if (x == 22 && y == 23)
    {
        newMap = new WeiBaiMap(mapGameEvent);
        newMap->SetXY(14 * SM, 57 * SM);
    }
    else if (x == 23 && y == 23)
    {
        newMap = new WeiBaiMap(mapGameEvent);
        newMap->SetXY(14 * SM, 57 * SM);
    }
    else if (x == 22 && y == 16)
    {
        newMap = new WeiBaiHouse1_2F_Map(mapGameEvent);
        newMap->SetXY(16 * SM, 12 * SM);
    }

    newMap->LoadBitmap();
    return newMap;
}
int WeiBaiHouse1_1F_Map::ReturnMapID()
{
    return 1;
}
int WeiBaiHouse1_1F_Map::CheckID(int x, int y, int herodirection)
{
    x /= SM;
    y /= SM;

    if (mom.GetX() / SM == x && mom.GetY() / SM + 1 == y) //represent mom
    {
        mapGameEvent->Occur(WeibaiHouse1_1F_Talk_To_Mom);
        mom.Talk(herodirection);
        inEvent = true;

        if (mom.GetVer() == 1)dialogBox.SetText("take this 100 dollars");
        else if (mom.GetVer() == 2)dialogBox.SetText("012345/6789");
        else if (mom.GetVer() == 3)dialogBox.SetText("manipulate your clock");

        if (mom.GetVer() == 4) inEvent = false;

        TRACE("getvar = %d\n", mom.GetVer());
        return inEvent;
    }

    if (book.GetX() / SM == x && book.GetY() / SM == y)
    {
        if (inEvent) inEvent = false;
        else
        {
            inEvent = true;
            dialogBox.SetText("nothing inside");
        }

        return inEvent;
    }

    return inEvent;
}
}