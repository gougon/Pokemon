	#pragma once

#include <vector>
#include <string>
#include "Npc.h"

using namespace std;
namespace game_framework {
	class Citizen : public Npc {
	public:
		Citizen();
		virtual void KeyDownListener(UINT nChar, CHero &hero) = 0;
		virtual void LoadBitmap() = 0;
		virtual void OnShow(CHero &hero) = 0;
		virtual void ReShow(CHero &hero) = 0;
		virtual void OnMove() { }; // for don't move
		virtual void OnMove(CHero &hero) { }; // for need to move
		virtual string GetMap();
		void SetIsEvent(bool flag);
		bool IsTalk();
		bool IsCollision(int x, int y);
	protected:
		virtual void Talk(CHero &hero) = 0;
		void StopTalk(CHero &hero);
		bool IsBeTalked(CHero &hero);

		CDialog eventDialog, normalDialog;
		string name, map;
		int direction;
		int x, y;	// 現在所在位置，不用算sm
		bool isTalk, isEvent;
	};
}