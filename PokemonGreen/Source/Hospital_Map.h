#pragma once
#include "CMap.h"
#include "CHero.h"
#include "CObject.h"
#include "CEvent.h"

constexpr auto HOSPITAL_INSIDE = 2;
constexpr auto NURSE = 3;

namespace game_framework
{
	class Hospital_Map : public CMap
	{
	public:
		Hospital_Map(CEvent*);
		virtual void InitMap();
		virtual void LoadBitmap();
		virtual void OnShow();
		virtual bool IsCollision(int x, int y);
		virtual CMap* ChangeMap(int x, int y, CHero* hero);
	private:
		bool inEvent;
		CDialog dialogBox;
		CObject book;
		vector<int> hitImg = { 0, 2, 3 };
	};
}

