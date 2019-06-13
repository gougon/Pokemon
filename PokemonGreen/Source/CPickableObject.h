#pragma once
#include<string>
#include"CDialog.h"
using namespace std;
namespace game_framework {
	class CPickableObject {
	public:
		int GetX();
		int GetY();
		void OnShow(int, int);
		void LoadBitmap();
		void SetXY(unsigned int, unsigned int);
	private:
		bool inEvent;
		CMovingBitmap pickable_object;
		int ox, oy;
	};
}