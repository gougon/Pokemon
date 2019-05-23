#pragma once
#include <string>
#include <vector>
#include "CText.h"
#include "ActionObject.h"

using namespace std;
namespace game_framework
{
class Self : public ActionObject
{
    public:
        void Init();
        void OnShow();
        void OnMove();
        void LoadBitmap();
        void KeyDownListener(UINT nChar);
		//void GetBadge();
		void RecieveData(int money, int illuAmount);
		virtual void SetTopLeft() {}
    private:
		const int TITLE_LEFT = 80;
		const int TITLE_TOP = 50;
		const int NAME_LEFT = 75;
		const int NAME_TOP = 125;
		const int MONEY_TOP = 190;
		const int ILLU_TOP = 240;
		int money;
		int illuAmount;
		CText title , name , moneyText , illuText;
        CMovingBitmap self_image;
};
}
