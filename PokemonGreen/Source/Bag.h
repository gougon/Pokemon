#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"
#include "CText.h"
#include "CItem.h"
#include "CProp.h"

using namespace std;
namespace game_framework
{
class Bag : public ActionObject
{
    public:
        void Init();
        void OnShow();
        void OnMove();
        void LoadBitmap();
        void KeyDownListener(UINT nChar);
        void AddItem(int, int);
    private:
        int categorie_flagIndex;
        int chooser;
        int item_amount[10];
        vector<CProp*> item_Prop;
        CText text;
        CText item_name;
        CText description;
        CAnimation cursor;
        CMovingBitmap categorie_flag;
        CMovingBitmap item_selector;
        CMovingBitmap item_image;
        CMovingBitmap background_image;
};
}
