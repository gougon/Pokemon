#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hospital_Map.h"
#include "WeiBaiMap.h"
#include "CDialog.h"

namespace game_framework
{
	Hospital_Map::Hospital_Map(CEvent* gameEvent) : CMap(4) // sceneNum
	{
		mapGameEvent = gameEvent;
		InitMap();
	}

	void Hospital_Map::InitMap()
	{
		SetMXY(42, 37);
		SetXY(16 * SM, 18 * SM);
		SetMap("hospital");
	}

	void Hospital_Map::LoadBitmap()
	{
		scene[HOSPITAL_INSIDE].LoadBitmap(IDB_HOSPITAL_INSIDE);
	}

	void Hospital_Map::OnShow()
	{
		int sx = GetSX();
		int sy = GetSY();
		TRACE("\nsx = %d, sy = %d\n", sx, sy);

		for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount)
		{
			for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount)
			{
				TRACE("\ni = %d, j = %d\n", i / SM, j / SM);
				switch (map[j / SM][i / SM])
				{
				case NONE_HIT:
					break;
				case NONE_EMPTY:
					break;
				case NURSE:
					break;
				case ENTRANCE:
					break;
				case HOSPITAL_INSIDE:
					scene[HOSPITAL_INSIDE].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
					scene[HOSPITAL_INSIDE].ShowBitmap();
					break;
				default:
					TRACE("\nHospital error!\n");
					ASSERT(0);
					break;
				}
			}
		}
	}

	bool Hospital_Map::IsCollision(int x, int y)
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

	CMap* Hospital_Map::ChangeMap(int x, int y, CHero* hero)
	{
		x /= SM;
		y /= SM;
		CMap* newMap;

		TRACE("\nX = %d, Y = %d\n", x, y);
		if (x == 20 && y == 23 || x == 21 && y == 23)
		{
			newMap = new WeiBaiMap(mapGameEvent);
			newMap->SetXY(15 * SM, 25 * SM);
		}

		newMap->LoadBitmap();
		return newMap;
	}
}
