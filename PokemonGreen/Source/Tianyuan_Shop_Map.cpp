#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "WeiBaiMap.h"
#include "Tianyuan_Shop_Map.h"
namespace game_framework {
	Tianyuan_Shop_Map::Tianyuan_Shop_Map(CEvent * gameEvent) : CMap(3)
	{
		mapGameEvent = gameEvent;
		InitMap();
	}
	void Tianyuan_Shop_Map::OnMove()
	{
		if (clerk.IsWork())
			clerk.OnMove();
	}

	void Tianyuan_Shop_Map::InitMap()
	{
		CAudio::Instance()->Play(AUDIO_MART);
		SetMXY(39, 36);
		SetXY(12 * SM, 18 * SM);
		SetMap("shop");
		name = "tianyuan_shop";
		inEvent = false;
	}

	void Tianyuan_Shop_Map::LoadBitmap()
	{
		scene[SHOP_MAP].LoadBitmap(IDB_SHOP_MAP);
		clerk.LoadBitmap();
		clerk.Init();
	}

	void Tianyuan_Shop_Map::OnShow()
	{
		int sx = GetSX();
		int sy = GetSY();
		for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount) {
			for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount) {
				switch (map[j / SM][i / SM]) {
				case SHOP_MAP:
					scene[SHOP_MAP].SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
					scene[SHOP_MAP].ShowBitmap();
					break;
				default:
					break;
				}
			}
		}
		if (clerk.IsWork()) clerk.OnShow();
	}

	bool Tianyuan_Shop_Map::IsCollision(int x, int y, CHero &hero)
	{
		x /= SM;
		y /= SM;

		for (int i = 0; i < 2; ++i) {
			if (map[y][x] == hitImg[i])
				return true;
		}
		return false;
	}

	CMap * Tianyuan_Shop_Map::ChangeMap(int x, int y, CHero * hero)
	{
		x /= SM;
		y /= SM;
		CMap* newMap;

		if ((x == 17 && y == 23) || (x == 18 && y == 23)) {
			newMap = new WeiBaiMap(mapGameEvent);
			newMap->SetXY(32 * SM, 33 * SM);
		}
		CAudio::Instance()->Stop(AUDIO_MART);
		newMap->LoadBitmap();
		return newMap;
	}

	int Tianyuan_Shop_Map::checkID(int, int, int)
	{
		return 0;
	}

	void Tianyuan_Shop_Map::KeyDownListener(UINT nChar, CHero& hero)
	{
		const char KEY_Z = 0x5a;
		if (clerk.IsWork())
			clerk.KeyDownListener(nChar);
		else {
			int x = hero.GetX1();
			int y = hero.GetY1();
			int direction = hero.GetDirection(); // �W���U�k
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
				if (x == 16 && y == 18) {
					clerk.ReceiveData(&hero, hero.GetBag());
					clerk.SetMoney(hero.GetMoney());
					clerk.Start();
				}
			}
		}
	}

}
