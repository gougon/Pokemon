#pragma once

#include "CMap.h"
#include "CHero.h"
#include "CEvent.h"
constexpr auto WEIBAITOWN_PRO_HOUSE_INSIDE = 2;

namespace game_framework {
	class WeiBaiProHouse_Map : public CMap {
	public:
		WeiBaiProHouse_Map(CEvent*);
		virtual void InitMap();
		virtual void LoadBitmap();
		virtual void OnShow();
		virtual bool IsCollision(int x, int y, CHero &hero);
		virtual CMap* ChangeMap(int x, int y, CHero* hero);
	private:
		int hitImg[2] = { 0, 2 };
	};
}