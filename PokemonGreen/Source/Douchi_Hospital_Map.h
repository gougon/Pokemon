#pragma once
#include "CMap.h"
#include "CHero.h"
#include "Nurse.h"
#include "CObject.h"
#include "CEvent.h"

namespace game_framework
{
	class Douchi_Hospital_Map : public CMap
	{
	public:
		Douchi_Hospital_Map(CEvent*);
		virtual void InitMap();
		virtual void LoadBitmap();
		virtual void OnShow();
		virtual void OnMove();
		virtual void KeyDownListener(UINT nChar, CHero &hero);
		virtual bool IsCollision(int x, int y, CHero &hero);
		virtual CMap* ChangeMap(int x, int y, CHero* hero);
	private:
		const int NURSE_X = 21;
		const int NURSE_Y = 17;
		bool IsItemBeChecked(int x, int y, CHero &hero);
		bool inEvent;
		Nurse nurse;
		CDialog dialogBox;
		CObject book;
		vector<int> hitImg = { 0, 2, 3 };
	};
}

