#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "DouChiHouse2_Map.h"
#include "WeiBaiMap.h"

namespace game_framework {
	DouChiHouse2_Map::DouChiHouse2_Map(CEvent*gameEvent) :
		CMap(3)
	{
		mapGameEvent = gameEvent;
		InitMap();
	}

	void DouChiHouse2_Map::InitMap()
	{
		SetMXY(38, 37);
		SetXY(12 * SM, 18 * SM);
		SetMap("douchitown_house2");
		name = "douchitown_house2";
	}

	void DouChiHouse2_Map::LoadBitmap()
	{
		scene[DOUCHIHOUSE2_INSIDE].LoadBitmap(IDB_DOUCHITOWN_HOUSE2);
	}

	void DouChiHouse2_Map::OnShow()
	{
		int sx = GetSX();
		int sy = GetSY();

		for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount) {
			for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount) {
				switch (map[j / SM][i / SM])
				{
				case DOUCHIHOUSE2_INSIDE:
					SetTopLeft(DOUCHIHOUSE2_INSIDE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
					break;
				default:
					break;
				}
			}
		}
	}

	void DouChiHouse2_Map::OnMove()
	{
		// empty body
	}

	void DouChiHouse2_Map::KeyDownListener(UINT nChar, CHero &hero)
	{
		// empty body
	}

	bool DouChiHouse2_Map::IsCollision(int x, int y, CHero &hero)
	{
		x /= SM;
		y /= SM;

		for (int i = 0; i < 3; ++i) {
			if (map[y][x] == hitImg[i])
				return true;
		}

		return false;
	}

	CMap* DouChiHouse2_Map::ChangeMap(int x, int y, CHero* hero)
	{
		x /= SM;
		y /= SM;
		CMap* newMap;

		if (x == 17 && y == 23 || x == 18 && y == 23) {
			newMap = new WeiBaiMap(mapGameEvent);
			newMap->SetXY(92 * SM, 38 * SM);
		}

		newMap->LoadBitmap();
		return newMap;
	}
}