#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "WeiBaiHouse1_2F_Map.h"
#include "WeiBaiHouse1_1F_Map.h"

namespace game_framework {
	WeiBaiHouse1_2F_Map::WeiBaiHouse1_2F_Map(CEvent* gameEvent) : CMap(3) // sceneNum
	{
		mapGameEvent = gameEvent;
		InitMap();
	}

	void WeiBaiHouse1_2F_Map::InitMap()
	{
		SetMXY(37, 36);
		SetXY(16 * SM, 12 * SM);
		SetMap("weibaitown_house1_2f");
	}

	void WeiBaiHouse1_2F_Map::LoadBitmap()
	{
		scene[WEIBAITOWN_HOUSE1_2F].LoadBitmap(IDB_WEIBAITOWN_HOUSE1_2F);
	}

	void WeiBaiHouse1_2F_Map::OnShow()
	{
		int sx = GetSX();
		int sy = GetSY();

		for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount) {
			for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount) {
				switch (map[j / SM][i / SM]) {
				case WEIBAITOWN_HOUSE1_2F:
					scene[WEIBAITOWN_HOUSE1_2F].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
					scene[WEIBAITOWN_HOUSE1_2F].ShowBitmap();
					break;
				default:
					break;
				}
			}
		}
	}

	bool WeiBaiHouse1_2F_Map::IsCollision(int x, int y, CHero &hero)
	{
		x /= SM;
		y /= SM;

		for (int i = 0; i < 2; ++i) {
			if (map[y][x] == hitImg[i])
				return true;
		}

		return false;
	}

	CMap* WeiBaiHouse1_2F_Map::ChangeMap(int x, int y, CHero* hero)
	{
		x /= SM;
		y /= SM;
		CMap* newMap;

		if (x == 21 && y == 15) {
			newMap = new WeiBaiHouse1_1F_Map(mapGameEvent);
			newMap->SetXY(17 * SM, 13 * SM);
		}

		newMap->LoadBitmap();
		return newMap;
	}
}