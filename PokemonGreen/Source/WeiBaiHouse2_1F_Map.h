#pragma once
#ifndef WEIBAIHOUSE2_1F_MAP
#define WEIBAIHOUSE2_1F_MAP

#include "CMap.h"
#include "CHero.h"
#include "CEvent.h"

constexpr auto WEIBAITOWN_HOUSE2_1F = 2;

namespace game_framework {
	class WeiBaiHouse2_1F_Map : public CMap {
	public:
		WeiBaiHouse2_1F_Map(CEvent*);
		virtual void InitMap();
		virtual void LoadBitmap();
		virtual void OnShow();
		virtual bool IsCollision(int x, int y, CHero &hero);
		virtual CMap* ChangeMap(int x, int y, CHero* hero);
	private:
		int hitImg[2] = { 0, 2 };
	};
}

#endif#pragma once
