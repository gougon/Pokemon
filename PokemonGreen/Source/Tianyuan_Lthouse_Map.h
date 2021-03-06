#pragma once

#include "CMap.h"
#include "CHero.h"
#include "CEvent.h"

constexpr auto TIANYUAN_LTHOUSE_INSIDE = 2;
constexpr auto TIANYUAN_LTHOUSE_POTTED = 3;

namespace game_framework {
	class Tianyuan_Lthouse_Map : public CMap {
	public:
		Tianyuan_Lthouse_Map(CEvent*);
		virtual void InitMap();
		virtual void LoadBitmap();
		virtual void OnShow();
		virtual void ReShow(CHero &hero);
		virtual bool IsCollision(int x, int y, CHero &hero);
		virtual CMap* ChangeMap(int x, int y, CHero* hero);
	private:
		int hitImg[3] = { 0, 2, 3 };
	};
}