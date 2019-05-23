#pragma once

#include "CMap.h"
#include "CHero.h"
#include "CEvent.h"

namespace game_framework {
	const int DOUCHIHOUSE2_INSIDE = 2;

	class DouChiHouse2_Map : public CMap {
	public:
		DouChiHouse2_Map(CEvent*);
		virtual void InitMap();
		virtual void LoadBitmap();
		virtual void OnShow();
		virtual void OnMove();
		virtual void KeyDownListener(UINT nChar, CHero &hero);
		virtual bool IsCollision(int x, int y);
		virtual CMap* ChangeMap(int x, int y, CHero* hero);
	private:
		bool inEvent;
		vector<int> hitImg = { 0, 2 };
	};
}