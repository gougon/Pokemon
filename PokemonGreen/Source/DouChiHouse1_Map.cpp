#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "DouChiHouse1_Map.h"
#include "WeiBaiMap.h"

namespace game_framework {
	DouChiHouse1_Map::DouChiHouse1_Map(CEvent*gameEvent) :
		CMap(3)
	{
		mapGameEvent = gameEvent;
		InitMap();
	}

	void DouChiHouse1_Map::InitMap()
	{
		SetMXY(39, 36);
		SetXY(12 * SM, 17 * SM);
		SetMap("douchitown_house1");
		name = "douchitown_house1";
	}

	void DouChiHouse1_Map::LoadBitmap()
	{
		scene[DOUCHIHOUSE1_INSIDE].LoadBitmap(IDB_DOUCHITOWN_HOUSE1);
	}

	void DouChiHouse1_Map::OnShow()
	{
		int sx = GetSX();
		int sy = GetSY();

		for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount) {
			for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount) {
				switch (map[j / SM][i / SM])
				{
				case NONE_HIT:
					break;
				case NONE_EMPTY:
					break;
				case ENTRANCE:
					break;
				case DOUCHIHOUSE1_INSIDE:
					SetTopLeft(DOUCHIHOUSE1_INSIDE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
					break;
				default:
					ASSERT(0);
					break;
				}
			}
		}
	}

	void DouChiHouse1_Map::OnMove()
	{
		// empty body
	}

	void DouChiHouse1_Map::KeyDownListener(UINT nChar, CHero &hero)
	{
		// empty body
	}

	bool DouChiHouse1_Map::IsCollision(int x, int y, CHero &hero)
	{
		x /= SM;
		y /= SM;

		for (int i = 0; i < 2; ++i) {
			if (map[y][x] == hitImg[i])
				return true;
		}

		return false;
	}

	CMap* DouChiHouse1_Map::ChangeMap(int x, int y, CHero* hero)
	{
		x /= SM;
		y /= SM;
		CMap* newMap;

		if (x == 17 && y == 22 || x == 18 && y == 22) {
			newMap = new WeiBaiMap(mapGameEvent);
			newMap->SetXY(102 * SM, 47 * SM);
		}

		newMap->LoadBitmap();
		return newMap;
	}
}