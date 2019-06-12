#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Tianyuan_Hospital_Map.h"
#include "WeiBaiMap.h"
#include "CDialog.h"

namespace game_framework
{
	Tianyuan_Hospital_Map::Tianyuan_Hospital_Map(CEvent* gameEvent) : CMap(4) // sceneNum
	{
		mapGameEvent = gameEvent;
		InitMap();
	}

	void Tianyuan_Hospital_Map::InitMap()
	{
		CAudio::Instance()->Play(AUDIO_HOSPITAL_START);

		SetMXY(42, 37);
		SetXY(16 * SM, 18 * SM);
		SetMap("hospital");
		name = "tianyuan_hospital";
	}

	void Tianyuan_Hospital_Map::LoadBitmap()
	{
		scene[HOSPITAL_INSIDE].LoadBitmap(IDB_HOSPITAL_INSIDE);
		nurse.LoadBitmap();
		nurse.Init();
	}

	void Tianyuan_Hospital_Map::OnShow()
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
				case NURSE:
					break;
				case ENTRANCE:
					break;
				case HOSPITAL_INSIDE:
					SetTopLeft(HOSPITAL_INSIDE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
					break;
				default:
					TRACE("\nHospital error!\n");
					ASSERT(0);
					break;
				}
			}
		}

		if (nurse.IsWork()) {
			nurse.OnShow();
		}
	}

	void Tianyuan_Hospital_Map::OnMove()
	{
		if (++audioCounter == 100) {
			CAudio::Instance()->Play(AUDIO_HOSPITAL_PROCESS, true);
		}
		if (nurse.IsWork()) {
			nurse.OnMove();
		}
	}

	void Tianyuan_Hospital_Map::KeyDownListener(UINT nChar, CHero &hero)
	{
		const char KEY_Z = 0x5a;

		if (nurse.IsWork()) {
			nurse.KeyDownListener(nChar);
		}
		else {
			switch (nChar) {
			case KEY_Z:
				if (IsItemBeChecked(NURSE_X, NURSE_Y, hero)) {
					nurse.ReceiveData(hero);
					nurse.Start();
				}
				break;
			}
		}
	}

	bool Tianyuan_Hospital_Map::IsCollision(int x, int y, CHero &hero)
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

	CMap* Tianyuan_Hospital_Map::ChangeMap(int x, int y, CHero* hero)
	{
		x /= SM;
		y /= SM;
		CMap* newMap;

		if (x == 20 && y == 23 || x == 21 && y == 23)
		{
			newMap = new WeiBaiMap(mapGameEvent);
			newMap->SetXY(27 * SM, 37 * SM);
		}

		CAudio::Instance()->Stop(AUDIO_HOSPITAL_START);
		CAudio::Instance()->Stop(AUDIO_HOSPITAL_PROCESS);
		newMap->LoadBitmap();
		return newMap;
	}

	bool Tianyuan_Hospital_Map::IsItemBeChecked(int x, int y, CHero &hero)
	{
		int herox = hero.GetX1() / SM;
		int heroy = hero.GetY1() / SM;
		if (hero.GetDirection() == 0 &&
			x == herox && y == heroy - 1) {
			return true;
		}
		else if (hero.GetDirection() == 1 &&
			x == herox - 1 && y == heroy) {
			return true;
		}
		else if (hero.GetDirection() == 2 &&
			x == herox && y == heroy + 1) {
			return true;
		}
		else if (hero.GetDirection() == 3 &&
			x == herox + 1 && y == heroy) {
			return true;
		}
		else {
			return false;
		}
	}
}
