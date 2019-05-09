#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include <time.h>
#include "WeiBaiMap.h"
#include "WeiBaiHouse1_1F_Map.h"
#include "WeiBaiHouse2_1F_Map.h"
#include "WeiBaiProHouse_Map.h"
#include "Hospital_Map.h"
#include "Shop_map.h"
#include "AtkInterface.h"
#include "Pokemon.h"
#include "PokemonFactory.h"
#include "PmTreecko.h"
#include "Skill.h"
#include "SkillFactory.h"
#include "SkillImpact.h"

namespace game_framework
{
	WeiBaiMap::WeiBaiMap(CEvent* gameEvent) : CMap(15) // sceneNum
	{
		mapGameEvent = gameEvent;

		for (int i = 0; i < 10; i++)
			TRACE("Event%d : %d\n", i, mapGameEvent->CheckOccured(i));

		InitMap();
	}



	void WeiBaiMap::InitMap()
	{
		CAudio::Instance()->Play(AUDIO_WEIBAITOWN);

		SetMXY(48, 87);			// 設定地圖總長寬格數
		SetXY(18 * SM, 57 * SM);		// 設定初始位置
		SetMap("area1");
		fatguy.Initialize();
		fatguy.SetXY(25 * SM, 62 * SM + 40);
		dialogBox.InitDialog('n');

		if (!mapGameEvent->CheckOccured(WeibaiTown_pick_Pokemomball)) pickable_Antidote.SetXY(1380, 1980);

		inEvent = false;
		dialogState = Start;
	}

	void WeiBaiMap::LoadBitmap()
	{
		scene[GREEN_GRASS].LoadBitmap(IDB_GREEN_GRASS);
		scene[GREEN_TREE].LoadBitmap(IDB_GREEN_TREE, RGB(255, 0, 0));
		// scene[GREEN_FLOWER].LoadBitmap(IDB_GREEN_FLOWER);
		scene[GRASS_LAND].LoadBitmap(IDB_GRASS_LAND);
		scene[BILLBOARD].LoadBitmap(IDB_BILLBOARD);
		scene[WEIBAITOWN_HOUSE1].LoadBitmap(IDB_WEIBAITOWN_HOUSE1);
		scene[WEIBAITOWN_HOUSE2].LoadBitmap(IDB_WEIBAITOWN_HOUSE2);
		scene[WEIBAITOWN_PRO_HOUSE].LoadBitmap(IDB_WEIBAITOWN_PRO_HOUSE);
		scene[M_GREEN_GRASS].LoadBitmap(IDB_M_GREEN_GRASS);
		scene[JUMP_LAND].LoadBitmap(IDB_JUMP_LAND);
		scene[HOSPITAL].LoadBitmap(IDB_HOSPITAL, RGB(255, 0, 0));
		scene[STORE].LoadBitmap(IDB_STORE, RGB(255, 0, 0));
		scene[NORMAL_HOUSE1].LoadBitmap(IDB_NORMAL_HOUSE1, RGB(255, 0, 0));

		flower.AddBitmap(IDB_GREEN_FLOWER);
		flower.AddBitmap(IDB_GREEN_FLOWER2);
		flower.AddBitmap(IDB_GREEN_FLOWER3);

		fatguy.LoadBitmap();
		/////////////////////////////
		if (!mapGameEvent->CheckOccured(WeibaiTown_pick_Pokemomball))
			pickable_Antidote.LoadBitmap();
	}

	void WeiBaiMap::OnShow()
	{
		int sx = GetSX();
		int sy = GetSY();

		for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount)
		{
			for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount)
			{
				SetTopLeft(GREEN_GRASS, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
			}
		}

		for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount)
		{
			for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount)
			{
				switch (map[j / SM][i / SM])
				{
					case NONE_HIT:
						break;
					case NONE_EMPTY:
						break;
					case ENTRANCE:
						break;
					case HOSPITAL:
						SetTopLeft(HOSPITAL, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case STORE:
						SetTopLeft(STORE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case GREEN_GRASS:
						SetTopLeft(GREEN_GRASS, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case GREEN_TREE:
						SetTopLeft(GREEN_TREE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM - 15);
						break;
					case GREEN_FLOWER:
						// SetTopLeft(GREEN_FLOWER, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						flower.SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						flower.OnShow();
						break;
					case GRASS_LAND:
						SetTopLeft(GRASS_LAND, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case BILLBOARD:
						SetTopLeft(BILLBOARD, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case WEIBAITOWN_HOUSE1:
						SetTopLeft(WEIBAITOWN_HOUSE1, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case WEIBAITOWN_HOUSE2:
						SetTopLeft(WEIBAITOWN_HOUSE2, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case WEIBAITOWN_PRO_HOUSE:
						SetTopLeft(WEIBAITOWN_PRO_HOUSE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case M_GREEN_GRASS:
						SetTopLeft(M_GREEN_GRASS, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case JUMP_LAND:
						SetTopLeft(JUMP_LAND, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case NORMAL_HOUSE1:
						SetTopLeft(NORMAL_HOUSE1, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					default:
						ASSERT(0);
						break;
				}
				fatguy.OnShow(GetSX(), GetSY());
				if (!mapGameEvent->CheckOccured(WeibaiTown_pick_Pokemomball))
					pickable_Antidote.OnShow(sx, sy);
			}
		}

		if (inEvent) dialogBox.OnShow();
	}

	void WeiBaiMap::OnMove()
	{
		flower.OnMove();
		fatguy.OnMove();
	}

	bool WeiBaiMap::IsCollision(int x, int y)
	{
		x /= SM;
		y /= SM;

		for (auto i : hitImg)
		{
			if (map[y][x] == i)
				return true;
		}
		if (fatguy.GetX() / SM == x && fatguy.GetY() / SM + 1 == y) return true;
		return false;
	}

	bool WeiBaiMap::IsWarZone(int x, int y)
	{
		x /= SM;
		y /= SM;

		//TRACE("\nx = %d, y = %d\n", x, y);
		for (auto i : warZone)
		{
			if (map[y][x] == i)
				return true;
		}

		return false;
	}

	void WeiBaiMap::ProduceEnemy(CHero* hero, AtkInterface &atkInterface)
	{
		int x = hero->GetX1() / SM;
		int y = hero->GetY1() / SM;
		// 利用atkProb判斷有沒有遇到怪
		int rnd = rand() % hero->GetAtkProb() + 1;

		if (rnd == hero->GetAtkProb())  	// 遇到怪
		{
			CAudio::Instance()->Stop(AUDIO_WEIBAITOWN);
			CAudio::Instance()->Play(AUDIO_GOTOBATTLE);

			PokemonFactory pmfactory;
			SkillFactory skfactory;
			Pokemon* enemy = pmfactory.CreateEnemyRandom();
			enemy->AddSkill(skfactory.CreateSkill(impact, styleEnemy));
			StartAtk(hero, enemy, atkInterface);
		}
	}

	CMap* WeiBaiMap::ChangeMap(int x, int y, CHero* hero)
	{
		x /= SM;
		y /= SM;
		CMap* newMap;
	
		if (x == 19 && y == 60) {
			newMap = new WeiBaiHouse1_1F_Map(mapGameEvent);
		}
		else if (x == 28 && y == 60) {
			newMap = new WeiBaiHouse2_1F_Map(mapGameEvent);
		}
		else if (x == 21 && y == 68) {
			newMap = new WeiBaiProHouse_Map(mapGameEvent);
		}
		else if (x == 20 && y == 28) {
			newMap = new Hospital_Map(mapGameEvent);
		}
		else if (x == 28 && y == 18) {
			newMap = new Shop_Map(mapGameEvent);
		}

		CAudio::Instance()->Stop(AUDIO_WEIBAITOWN);
		newMap->LoadBitmap();
		return newMap;
	}

	void WeiBaiMap::StartAtk(CHero* self, Pokemon* enemy, AtkInterface &atkInterface)
	{
		atkInterface.ReceiveData(self, enemy);
		atkInterface.Start();
	}

	void WeiBaiMap::KeyDownListener(UINT nChar, CHero &hero)
	{
		const char KEY_Z = 0x5a;

		int x = hero.GetX1();
		int y = hero.GetY1();
		int direction = hero.GetDirection(); // 上左下右

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
			{
				inEvent = false;
			}
			if (pickable_Antidote.GetX() / SM == x && pickable_Antidote.GetY() / SM == y)
			{
				if (!mapGameEvent->CheckOccured(WeibaiTown_pick_Pokemomball))
				{
					mapGameEvent->Occur(WeibaiTown_pick_Pokemomball);
					dialogBox.SetText("pick the smallvulnerary;and the pokeball");
					hero.GetItem(Item_SmallVulnerary , 2);
					hero.GetItem(Item_PokeBall, 2);
					inEvent = true;
				}
			}
			else if (fatguy.GetX() / SM == x && fatguy.GetY() / SM + 1 == y)
			{
				fatguy.Talk(direction);
				inEvent = true;

				if (fatguy.GetVer() == 1) {
					dialogBox.SetText("do you have some;delicious foods");
					dialogState = Start;
				}
				if (fatguy.GetVer() == 2) {
					dialogState = Continue;
					dialogBox.SetText("you call me fatguy!!");
				}
				if (fatguy.GetVer() == 3) dialogBox.SetText("get out of my way!!");
				if (fatguy.GetVer() == 4) {
					dialogState = End;
					inEvent = false;
				}
			}
			else
			{
				//
			}
		}
	}
}