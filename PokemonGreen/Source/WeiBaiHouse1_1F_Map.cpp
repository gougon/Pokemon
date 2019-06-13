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
		InitMap();
	}

	void WeiBaiHouse1_1F_Map::OnMove()
	{
		// empty body
	}

	void WeiBaiHouse1_1F_Map::InitMap()
	{
		SetMXY(39, 37);
		SetXY(17 * SM, 18 * SM);
		SetMap("weibaitown_house1_1f");
		name = "weibaihouse1_1";
		dialogBox.InitDialog('n');
		inEvent = false;
		dialogState = Start;
	}

	void WeiBaiHouse1_1F_Map::LoadBitmap()
	{
		scene[WEIBAITOWN_HOUSE1_1F].LoadBitmap(IDB_WEIBAITOWN_HOUSE1_1F);
	}

	void WeiBaiHouse1_1F_Map::OnShow()
	{
		int sx = GetSX();
		int sy = GetSY();

		for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount) {
			for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount) {
				switch (map[j / SM][i / SM]) {
				case WEIBAITOWN_HOUSE1_1F:
					scene[WEIBAITOWN_HOUSE1_1F].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
					scene[WEIBAITOWN_HOUSE1_1F].ShowBitmap();
					break;
				default:
					break;
				}
			}
		}

		if (inEvent)
			dialogBox.OnShow();
	}

	bool WeiBaiHouse1_1F_Map::IsCollision(int x, int y, CHero &hero)
	{
		x /= SM;
		y /= SM;

		for (int i = 0; i < 2; ++i) {
			if (map[y][x] == hitImg[i])
				return true;
		}

		return false;
	}

	CMap* WeiBaiHouse1_1F_Map::ChangeMap(int x, int y, CHero* hero)
	{
		x /= SM;
		y /= SM;
		CMap* newMap;

		if (x == 22 && y == 23) {
			newMap = new WeiBaiMap(mapGameEvent);
			newMap->SetXY(92 * SM, 79 * SM);
		}
		else if (x == 23 && y == 23) {
			newMap = new WeiBaiMap(mapGameEvent);
			newMap->SetXY(92 * SM, 79 * SM);
		}
		else if (x == 22 && y == 16) {
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

	void WeiBaiHouse1_1F_Map::KeyDownListener(UINT nChar, CHero & hero)
	{
		const char KEY_Z = 0x5a;

		int x = hero.GetX1();
		int y = hero.GetY1();
		int direction = hero.GetDirection(); // ¤W¥ª¤U¥k

		if (direction == 0) 
			y -= SM;
		else if (direction == 1) 
			y += SM;
		else if (direction == 2) 
			x -= SM;
		else if (direction == 3) 
			x += SM;
		x /= SM;
		y /= SM;
		if (nChar == KEY_Z) {
			if (inEvent && dialogState == End)
				inEvent = false;
		}
	}
}