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
        void DropItem(int, int);
    private:
        int categorie_flagIndex, panel_flagIndex;
        unsigned int chooser, dropAmount;
        unsigned int item_amount[10];
        bool inPanel, inItemamount, inYesno, yesnoChooser;
        vector<CProp*> item_Prop;
        CText text;
        CText item_name;
        CText description;
        CAnimation cursor;
        CMovingBitmap backpack_panel;
        CMovingBitmap amountSelect_panel;
        CMovingBitmap yesno_panel;
        CMovingBitmap categorie_flag;
        CMovingBitmap item_selector;
        CMovingBitmap item_image;
        CMovingBitmap background_image;
};
}
