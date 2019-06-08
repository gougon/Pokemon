#pragma once

#include "CMap.h"
#include "CHero.h"
#include "CEvent.h"

constexpr auto TIANYUAN_RBHOUSE_INSIDE = 2;

namespace game_framework
{
	class Tianyuan_Rbhouse_Map : public CMap
	{
	public:
		Tianyuan_Rbhouse_Map(CEvent*);
		virtual void InitMap();
		virtual void LoadBitmap();
		virtual void OnShow();
		virtual bool IsCollision(int x, int y, CHero &hero);
		virtual CMap* ChangeMap(int x, int y, CHero* hero);
	private:
		int hitImg[3] = { 0, 2, 3 };
	};
}