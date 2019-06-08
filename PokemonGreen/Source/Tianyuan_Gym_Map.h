#pragma once

#include "CMap.h"
#include "CHero.h"
#include "CEvent.h"

constexpr auto TIANYUAN_GYM_INSIDE = 2;
constexpr auto TIANYUAN_GYM_WALL1 = 4;
constexpr auto TIANYUAN_GYM_WALL2 = 5;
constexpr auto TIANYUAN_GYM_WALL3 = 6;
constexpr auto TIANYUAN_GYM_WALL4 = 3;
constexpr auto TIANYUAN_GYM_STATU = 7;

namespace game_framework
{
	class Tianyuan_Gym_Map : public CMap
	{
	public:
		Tianyuan_Gym_Map(CEvent*);
		virtual void InitMap();
		virtual void LoadBitmap();
		virtual void OnShow();
		virtual void ReShow(CHero &hero);
		virtual bool IsCollision(int x, int y, CHero &hero);
		virtual CMap* ChangeMap(int x, int y, CHero* hero);
	private:
		int hitImg[7] = { 0, 2, 3, 4, 5, 6, 7 };
	};
}