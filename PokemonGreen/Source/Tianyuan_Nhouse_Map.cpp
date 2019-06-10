#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "WeiBaiMap.h"
#include "Tianyuan_Nhouse_Map.h"

namespace game_framework
{
	Tianyuan_Nhouse_Map::Tianyuan_Nhouse_Map(CEvent* gameEvent) : CMap(4) // sceneNum
	{
		mapGameEvent = gameEvent;
		InitMap();
	}

	void Tianyuan_Nhouse_Map::InitMap()
	{
		SetMXY(38, 37);
		SetXY(13 * SM, 18 * SM);
		SetMap("tianyuantown_nhouse");
		name = "tianyuantown_nhouse";
	}

	void Tianyuan_Nhouse_Map::LoadBitmap()
	{
		scene[TIANYUAN_NHOUSE_INSIDE].LoadBitmap(IDB_TIANYUAN_NHOUSE_INSIDE);
		scene[TIANYUAN_NHOUSE_POTTED].LoadBitmap(IDB_POTTED, RGB(255, 0, 0));
	}

	void Tianyuan_Nhouse_Map::OnShow()
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

				case TIANYUAN_NHOUSE_INSIDE:
					scene[TIANYUAN_NHOUSE_INSIDE].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
					scene[TIANYUAN_NHOUSE_INSIDE].ShowBitmap();
					break;

				case TIANYUAN_NHOUSE_POTTED:
					scene[TIANYUAN_NHOUSE_POTTED].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM - 55);
					scene[TIANYUAN_NHOUSE_POTTED].ShowBitmap();
					break;

				default:
					ASSERT(0);
					break;
				}
			}
		}
	}

	void Tianyuan_Nhouse_Map::ReShow(CHero &hero)
	{
		int sx = GetSX();
		int sy = GetSY();
		int hy = hero.GetY1();

		for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount)
		{
			for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount)
			{
				if (HERO_Y + 20 + SM <= (ycount - EXPEND)*SM - sy % SM
					&& map[j / SM][i / SM] == TIANYUAN_NHOUSE_POTTED)
					SetTopLeft(TIANYUAN_NHOUSE_POTTED, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM - 55);
			}
		}
	}

	bool Tianyuan_Nhouse_Map::IsCollision(int x, int y, CHero &hero)
	{
		x /= SM;
		y /= SM;

		for (int i = 0; i < 3; ++i)
		{
			if (map[y][x] == hitImg[i])
				return true;
		}

		return false;
	}

	CMap* Tianyuan_Nhouse_Map::ChangeMap(int x, int y, CHero* hero)
	{
		x /= SM;
		y /= SM;
		CMap* newMap;

		if (x == 17 && y == 23)
		{
			newMap = new WeiBaiMap(mapGameEvent);
			newMap->SetXY(17 * SM, 40 * SM);
		}
		else if (x == 18 && y == 23)
		{
			newMap = new WeiBaiMap(mapGameEvent);
			newMap->SetXY(17 * SM, 40 * SM);
		}

		newMap->LoadBitmap();
		return newMap;
	}
}