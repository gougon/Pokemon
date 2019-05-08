#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"
#include "Bag.h"
#include "CText.h"
#include "CItem.h"
#include "CDialog.h"

using namespace std;
namespace game_framework
{
class MainMenu : public ActionObject
{
    public:
        MainMenu();
        void Init();
        void OnShow();
        void OnMove();
        void LoadBitmap();
        void KeyDownListener(UINT nChar);
    private:
};
}
