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
#include "Douchi_Hospital_Map.h"
#include "Douchi_Shop_Map.h"
#include "DouChiHouse1_Map.h"
#include "DouChiHouse2_Map.h"
#include "Tianyuan_Hospital_Map.h"
#include "Tianyuan_Shop_Map.h"
#include "Tianyuan_Nhouse_Map.h"
#include "Tianyuan_Lthouse_Map.h"
#include "Tianyuan_Rbhouse_Map.h"
#include "Tianyuan_Gym_Map.h"
#include "AtkInterface.h"
#include "Pokemon.h"
#include "PokemonFactory.h"
#include "PmTreecko.h"
#include "Skill.h"
#include "SkillFactory.h"
#include "SkillImpact.h"
#include "Black.h"

namespace game_framework
{
	WeiBaiMap::WeiBaiMap(CEvent* gameEvent) : CMap(36) // sceneNum
	{
		mapGameEvent = gameEvent;
		InitMap();
	}

	WeiBaiMap::~WeiBaiMap()
	{

	}

	void WeiBaiMap::InitMap()
	{
		CAudio::Instance()->Play(AUDIO_WEIBAITOWN);

		SetMXY(126, 109);			// 設定地圖總長寬格數
		SetXY(97 * SM, 80 * SM);		// 設定初始位置
		SetMap("area1");
		name = "weibai";
		dialogBox.InitDialog('n');

		if (!mapGameEvent->CheckOccured(WeibaiTown_pick_Pokemomball))
			pickable_Antidote.SetXY(6060, 3300);

		inEvent = false;
		dialogState = Start;
	}

	void WeiBaiMap::LoadBitmap()
	{
		scene[GREEN_GRASS].LoadBitmap(IDB_GREEN_GRASS);
		scene[GREEN_TREE].LoadBitmap(IDB_GREEN_TREE, RGB(255, 0, 0));
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
		scene[LAKE_102].LoadBitmap(IDB_LAKE_102);
		scene[LAND_C].LoadBitmap(IDB_LAND_C);
		scene[LAND_T].LoadBitmap(IDB_LAND_T);
		scene[LAND_R].LoadBitmap(IDB_LAND_R);
		scene[LAND_B].LoadBitmap(IDB_LAND_B);
		scene[LAND_L].LoadBitmap(IDB_LAND_L);
		scene[LAND_RT].LoadBitmap(IDB_LAND_RT);
		scene[LAND_RB].LoadBitmap(IDB_LAND_RB);
		scene[LAND_LT].LoadBitmap(IDB_LAND_LT);
		scene[LAND_LB].LoadBitmap(IDB_LAND_LB);
		scene[TIANYUAN_RTLAKE].LoadBitmap(IDB_TIANYUAN_RTLAKE);
		scene[TIANYUAN_RBHOUSE].LoadBitmap(IDB_TIANYUAN_RBHOUSE, RGB(255, 0, 0));
		scene[TIANYUAN_NHOUSE].LoadBitmap(IDB_TIANYUAN_NHOUSE);
		scene[TIANYUAN_LTHOUSE].LoadBitmap(IDB_TIANYUAN_LTHOUSE);
		scene[TIANYUAN_LLAKE1].LoadBitmap(IDB_TIANYUAN_LLAKE1);
		scene[TIANYUAN_LLAKE2].LoadBitmap(IDB_TIANYUAN_LLAKE2);
		scene[TIANYUAN_LLAKE3].LoadBitmap(IDB_TIANYUAN_LLAKE3);
		scene[TIANYUAN_LLAKE4].LoadBitmap(IDB_TIANYUAN_LLAKE4);
		scene[TIANYUAN_GYM].LoadBitmap(IDB_TIANYUAN_GYM);

		// flower.AddBitmap(IDB_GREEN_FLOWER);
		// flower.AddBitmap(IDB_GREEN_FLOWER2);
		// flower.AddBitmap(IDB_GREEN_FLOWER3);
		
		// rtsea1.AddBitmap(IDB_RTSEA1_1);
		// rtsea1.AddBitmap(IDB_RTSEA1_2);
		// rtsea1.AddBitmap(IDB_RTSEA1_3);
		// rtsea1.AddBitmap(IDB_RTSEA1_4);
		// rtsea1.AddBitmap(IDB_RTSEA1_5);
		// rtsea1.AddBitmap(IDB_RTSEA1_6);
		// 
		//rtsea2.AddBitmap(IDB_RTSEA2_1);
		//rtsea2.AddBitmap(IDB_RTSEA2_2);
		//rtsea2.AddBitmap(IDB_RTSEA2_3);
		//rtsea2.AddBitmap(IDB_RTSEA2_4);
		//rtsea2.AddBitmap(IDB_RTSEA2_5);
		//rtsea2.AddBitmap(IDB_RTSEA2_6);
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
						// flower.SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						// flower.OnShow();
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
					case RT_SEA1:
						// rtsea1.SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						// rtsea1.OnShow();
						break;
					case RT_SEA2:
						// rtsea2.SetTopLeft((xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						// rtsea2.OnShow();
						break;
					case LAKE_102:
						SetTopLeft(LAKE_102, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case LAND_C:
						SetTopLeft(LAND_C, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case LAND_T:
						SetTopLeft(LAND_T, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case LAND_R:
						SetTopLeft(LAND_R, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case LAND_B:
						SetTopLeft(LAND_B, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case LAND_L:
						SetTopLeft(LAND_L, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case LAND_RT:
						SetTopLeft(LAND_RT, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case LAND_RB:
						SetTopLeft(LAND_RB, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case LAND_LT:
						SetTopLeft(LAND_LT, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case LAND_LB:
						SetTopLeft(LAND_LB, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case TIANYUAN_RTLAKE:
						SetTopLeft(TIANYUAN_RTLAKE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case TIANYUAN_RBHOUSE:
						SetTopLeft(TIANYUAN_RBHOUSE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM - 20);
						break;
					case TIANYUAN_NHOUSE:
						SetTopLeft(TIANYUAN_NHOUSE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case TIANYUAN_LTHOUSE:
						SetTopLeft(TIANYUAN_LTHOUSE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case TIANYUAN_LLAKE1:
						SetTopLeft(TIANYUAN_LLAKE1, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case TIANYUAN_LLAKE2:
						SetTopLeft(TIANYUAN_LLAKE2, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case TIANYUAN_LLAKE3:
						SetTopLeft(TIANYUAN_LLAKE3, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case TIANYUAN_LLAKE4:
						SetTopLeft(TIANYUAN_LLAKE4, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case TIANYUAN_GYM:
						SetTopLeft(TIANYUAN_GYM, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					default:
						ASSERT(0);
						break;
				}

				if (!mapGameEvent->CheckOccured(WeibaiTown_pick_Pokemomball))
					pickable_Antidote.OnShow(sx, sy);
			}
		}

		if (inEvent) dialogBox.OnShow();
	}

	void WeiBaiMap::ReShow(CHero &hero)
	{
		int sx = GetSX();
		int sy = GetSY();
		int hy = hero.GetY1();

		for (int j = sy - EXPEND * SM, ycount = 0; j <= sy + SM * Y; j += SM, ++ycount)
		{
			for (int i = sx - EXPEND * SM, xcount = 0; i <= sx + SM * X; i += SM, ++xcount)
			{
				if (HERO_Y + 20 <= (ycount - EXPEND)*SM - sy % SM) {
					switch (map[j / SM][i / SM])
					{
					case HOSPITAL:
						SetTopLeft(HOSPITAL, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case STORE:
						SetTopLeft(STORE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
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
					case NORMAL_HOUSE1:
						SetTopLeft(NORMAL_HOUSE1, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case TIANYUAN_NHOUSE:
						SetTopLeft(TIANYUAN_NHOUSE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM);
						break;
					case TIANYUAN_RBHOUSE:
						SetTopLeft(TIANYUAN_RBHOUSE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM - 20);
						break;
					default:
						break;
					}
				}
				if (HERO_Y + 20 + SM <= (ycount - EXPEND)*SM - sy % SM
					&& map[j / SM][i / SM] == GREEN_TREE)
					SetTopLeft(GREEN_TREE, (xcount - EXPEND)*SM - sx % SM, (ycount - EXPEND)*SM - sy % SM - 15);
			}
		}
		if (inEvent) dialogBox.OnShow();
	}

	void WeiBaiMap::OnMove()
	{
		// flower.OnMove();
		// rtsea1.OnMove();
		// rtsea2.OnMove();
	}

	bool WeiBaiMap::IsCollision(int x, int y, CHero &hero)
	{
		x /= SM;
		y /= SM;
		bool flag = false;

		for (int i = 0; i < 14; ++i)
		{
			if (map[y][x] == hitImg[i])
				flag =  true;
		}
		if (map[y][x] == jumpLand) {
			if (!IsJumpLand(x * SM, y * SM, hero))
				flag = true;
		}

		return flag;
	}

	bool WeiBaiMap::IsWarZone(int x, int y)
	{
		x /= SM;
		y /= SM;

		if (map[y][x] == warZone) {
			return true;
		}

		return false;
	}

	bool WeiBaiMap::IsJumpLand(int x, int y, CHero &hero)
	{
		x /= SM;
		y /= SM;

		if (map[y][x] == jumpLand && hero.GetY1() / SM < y) {
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
			// SkillFactory skfactory;
			Pokemon* enemy = pmfactory.CreateEnemyRandom();
			// enemy->AddSkill(skfactory.CreateSkill(ember, styleEnemy));
			StartAtk(hero, enemy, atkInterface);
		}
	}

	CMap* WeiBaiMap::ChangeMap(int x, int y, CHero* hero)
	{
		x /= SM;
		y /= SM;
		CMap* newMap;
	
		if (x == 97 && y == 82) {
			newMap = new WeiBaiHouse1_1F_Map(mapGameEvent);
		}
		else if (x == 106 && y == 82) {
			newMap = new WeiBaiHouse2_1F_Map(mapGameEvent);
		}
		else if (x == 99 && y == 90) {
			newMap = new WeiBaiProHouse_Map(mapGameEvent);
		}
		else if (x == 98 && y == 50) {
			newMap = new Douchi_Hospital_Map(mapGameEvent);
		}
		else if (x == 106 && y == 40) {
			newMap = new Douchi_Shop_Map(mapGameEvent);
		}
		else if (x == 107 && y == 50) {
			newMap = new DouChiHouse1_Map(mapGameEvent);
		}
		else if (x == 97 && y == 41) {
			newMap = new DouChiHouse2_Map(mapGameEvent);
		}
		else if (x == 32 && y == 40) {
			newMap = new Tianyuan_Hospital_Map(mapGameEvent);
		}
		else if (x == 37 && y == 36) {
			newMap = new Tianyuan_Shop_Map(mapGameEvent);
		}
		else if (x == 22 && y == 43) {
			newMap = new Tianyuan_Nhouse_Map(mapGameEvent);
		}
		else if (x == 19 && y == 29) {
			newMap = new Tianyuan_Lthouse_Map(mapGameEvent);
		}
		else if (x == 32 && y == 48) {
			newMap = new Tianyuan_Rbhouse_Map(mapGameEvent);
		}
		else if (x == 27 && y == 32) {
			newMap = new Tianyuan_Gym_Map(mapGameEvent);
		}

		CAudio::Instance()->Stop(AUDIO_WEIBAITOWN);
		newMap->LoadBitmap();
		return newMap;
	}

	void WeiBaiMap::StartAtk(CHero* self, Pokemon* enemy, AtkInterface &atkInterface)
	{
		atkInterface.ReceiveEnemy(self, enemy);
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
				hero.EndDialog();
			}
			else {
				if (pickable_Antidote.GetX() / SM == x && pickable_Antidote.GetY() / SM == y)
				{
					if (!mapGameEvent->CheckOccured(WeibaiTown_pick_Pokemomball))
					{
						mapGameEvent->Occur(WeibaiTown_pick_Pokemomball);
						dialogBox.SetText("pick the smallvulnerary;and the pokeball");
						hero.GetItem(Item_SmallVulnerary, 2);
						hero.GetItem(Item_PokeBall, 2);
						dialogState = End;
						inEvent = true;
					}
				}
				else if (x == 99 && y == 82) {
					inEvent = true;
					dialogState = End;
					dialogBox.SetText("my sweet home");
				}
				else if (x == 104 && y == 82) {
					inEvent = true;
					dialogState = End;
					dialogBox.SetText("competitor home");
				}
				else if (x == 107 && y == 87) {
					inEvent = true;
					dialogState = End;
					dialogBox.SetText("the weibaitown             ;the town without anything");
				}
				else if (x == 98 && y == 91) {
					inEvent = true;
					dialogState = End;
					dialogBox.SetText("professor house");
				}
				else
				{
					//
				}
				if (inEvent) hero.StartDialog();
			}
		}
	}
}