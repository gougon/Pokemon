#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "WeiBaiMap.h"
#include "Tianyuan_Rbhouse_Map.h"

namespace game_framework
{
	Tianyuan_Rbhouse_Map::Tianyuan_Rbhouse_Map(CEvent* gameEvent) : CMap(4) // sceneNum
	{
		mapGameEvent = gameEvent;
		InitMap();
	}

	void Tianyuan_Rbhouse_Map::InitMap()
	{
		SetMXY(38, 36);
		SetXY(13 * SM, 17 * SM);
		SetMap("tianyuantown_rbhouse");
	}

	void Tianyuan_Rbhouse_Map::LoadBitmap()
	{
		scene[TIANYUAN_RBHOUSE_INSIDE].LoadBitmap(IDB_TIANYUAN_RBHOUSE_INSIDE);
	}

	void Tianyuan_Rbhouse_Map::OnShow()
	{
		int sx = GetSX();
		int sy = GetSY();

		for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount) {
			for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount) {
				switch (map[j / SM][i / SM]) {
				case TIANYUAN_RBHOUSE_INSIDE:
					scene[TIANYUAN_RBHOUSE_INSIDE].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
					scene[TIANYUAN_RBHOUSE_INSIDE].ShowBitmap();
					break;
				default:
					break;
				}
			}
		}
	}

	bool Tianyuan_Rbhouse_Map::IsCollision(int x, int y, CHero &hero)
	{
		x /= SM;
		y /= SM;

		for (int i = 0; i < 3; ++i) {
			if (map[y][x] == hitImg[i])
				return true;
		}

		return false;
	}

	CMap* Tianyuan_Rbhouse_Map::ChangeMap(int x, int y, CHero* hero)
	{
		x /= SM;
		y /= SM;
		CMap* newMap;

		if (x == 17 && y == 22) {
			newMap = new WeiBaiMap(mapGameEvent);
			newMap->SetXY(27 * SM, 45 * SM);
		}
		else if (x == 18 && y == 22) {
			newMap = new WeiBaiMap(mapGameEvent);
			newMap->SetXY(27 * SM, 45 * SM);
		}

		newMap->LoadBitmap();
		return newMap;
	}
}