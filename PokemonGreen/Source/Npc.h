#pragma once

#include "CHero.h"

using namespace std;
namespace game_framework {
	class CHero;
	enum direction {
		up, down, left, right
	};

	enum NpcType {
		citizen, trainer
	};

	class Npc {
	public:
		Npc(NpcType type) { this->type = type; }
		virtual void KeyDownListener(UINT nChar, CHero &hero) = 0;
		virtual void LoadBitmap() = 0;
		virtual void OnShow(CHero &hero) = 0;
		virtual void ReShow(CHero &hero) = 0;
		virtual void OnMove() { }; // for don't move
		virtual void OnMove(CHero &hero) { }; // for need to move
		virtual void SetIsEvent(bool flag) = 0;
		virtual bool IsTalk() = 0;
		virtual bool IsCollision(int x, int y) = 0;
		virtual string GetMap() = 0;
	protected:
		NpcType type;
		CMovingBitmap normalImg[4], atkImg;
	};
}