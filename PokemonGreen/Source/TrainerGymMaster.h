#pragma once
#include "Trainer.h"
namespace game_framework
{
	class TrainerGymMaster : public Trainer {
	public:
		TrainerGymMaster(AtkInterface *atkInterface);
		virtual void KeyDownListener(UINT nChar, CHero &hero);
		virtual void LoadBitmap();
		virtual void OnShow(CHero &hero);
		virtual void ReShow(CHero &hero);
		virtual void OnMove(CHero &hero); // for don't move
	private:
		virtual void Talk(CHero &hero);
		void SetTopLeft(int hx, int hy);
	};
}