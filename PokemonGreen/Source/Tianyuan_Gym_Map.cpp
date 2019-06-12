#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "WeiBaiMap.h"
#include "Tianyuan_Gym_Map.h"

namespace game_framework
{
	Tianyuan_Gym_Map::Tianyuan_Gym_Map(CEvent* gameEvent) : CMap(8) // sceneNum
	{
		mapGameEvent = gameEvent;
		InitMap();
	}

	void Tianyuan_Gym_Map::InitMap()
	{
		SetMXY(51, 60);
		SetXY(21 * SM, 35 * SM);
		SetMap("tianyuantown_gym");
		name = "tianyuangym";
	}

	void Tianyuan_Gym_Map::LoadBitmap()
	{
		scene[TIANYUAN_GYM_INSIDE].LoadBitmap(IDB_GYM);
		scene[TIANYUAN_GYM_WALL1].LoadBitmap(IDB_GYM_WALL1);
		scene[TIANYUAN_GYM_WALL2].LoadBitmap(IDB_GYM_WALL2);
		scene[TIANYUAN_GYM_WALL3].LoadBitmap(IDB_GYM_WALL3);
		scene[TIANYUAN_GYM_WALL4].LoadBitmap(IDB_GYM_WALL4);
		scene[TIANYUAN_GYM_STATU].LoadBitmap(IDB_GYM_STATU, RGB(255, 0, 0));
	}

	void Tianyuan_Gym_Map::OnShow()
	{
		int sx = GetSX();
		int sy = GetSY();

		for (int i = sx - (EXPEND + 6) * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount) {
			for (int j = sy - (EXPEND + 6) * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount) {
				switch (map[j / SM][i / SM]) {
				case TIANYUAN_GYM_INSIDE:
					scene[TIANYUAN_GYM_INSIDE].SetTopLeft((xcount - (EXPEND + 6))*SM - sx % SM, (ycount - (EXPEND + 6))*SM - sy % SM);
					scene[TIANYUAN_GYM_INSIDE].ShowBitmap();
					break;
				default:
					break;
				}
			}
		}
	}

	void Tianyuan_Gym_Map::ReShow(CHero &hero)
	{
		int sx = GetSX();
		int sy = GetSY();
		int hy = hero.GetY1();

		for (int j = sy - (EXPEND + 6) * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount) {
			for (int i = sx - (EXPEND + 6) * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount) {
				if (HERO_Y + 20 + SM <= (ycount - (EXPEND + 6))*SM - sy % SM) {
					if(map[j / SM][i / SM] == TIANYUAN_GYM_WALL1)
						SetTopLeft(TIANYUAN_GYM_WALL1, (xcount - (EXPEND + 6))*SM - sx % SM, (ycount - (EXPEND + 6))*SM - sy % SM - 32);
					else if (map[j / SM][i / SM] == TIANYUAN_GYM_WALL2)
						SetTopLeft(TIANYUAN_GYM_WALL2, (xcount - (EXPEND + 6))*SM - sx % SM, (ycount - (EXPEND + 6))*SM - sy % SM - 32);
					else if (map[j / SM][i / SM] == TIANYUAN_GYM_WALL3)
						SetTopLeft(TIANYUAN_GYM_WALL3, (xcount - (EXPEND + 6))*SM - sx % SM, (ycount - (EXPEND + 6))*SM - sy % SM - 32);
					else if (map[j / SM][i / SM] == TIANYUAN_GYM_WALL4)
						SetTopLeft(TIANYUAN_GYM_WALL4, (xcount - (EXPEND + 6))*SM - sx % SM, (ycount - (EXPEND + 6))*SM - sy % SM - 32);
					else if (map[j / SM][i / SM] == TIANYUAN_GYM_STATU)
						SetTopLeft(TIANYUAN_GYM_STATU, (xcount - (EXPEND + 6))*SM - sx % SM, (ycount - (EXPEND + 6))*SM - sy % SM - 60);
				}
			}
		}
	}

	bool Tianyuan_Gym_Map::IsCollision(int x, int y, CHero &hero)
	{
		x /= SM;
		y /= SM;

		for (int i = 0; i < 7; ++i) {
			if (map[y][x] == hitImg[i])
				return true;
		}

		return false;
	}

	CMap* Tianyuan_Gym_Map::ChangeMap(int x, int y, CHero* hero)
	{
		x /= SM;
		y /= SM;
		CMap* newMap;

		if (x == 25 && y == 40) {
			newMap = new WeiBaiMap(mapGameEvent);
			newMap->SetXY(22 * SM, 29 * SM);
		}
		else if (x == 26 && y == 40) {
			newMap = new WeiBaiMap(mapGameEvent);
			newMap->SetXY(22 * SM, 29 * SM);
		}

		newMap->LoadBitmap();
		return newMap;
	}
}