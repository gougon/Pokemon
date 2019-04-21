#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"
#include "CText.h"
#include "CItem.h"
#include "CProp.h"
#include "CScrolls.h"
#include "CBall.h"
#include "CGoods.h"
#include "CFruit.h"
#define MAXITEMAMOUNT 100
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
        unsigned int item_amount[MAXITEMAMOUNT];
        bool inPanel, inItemamount, inYesno, yesnoChooser;
        vector<CProp*> item_Prop;
        vector<CBall*> item_Balls;
        vector<CGoods*> item_Goods;
        vector<CScrolls*> item_Scrolls;
        vector<CFruit*> item_Fruit;
        CText text;
        CText item_name;
        CText description;
        CText item_left_amount;
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
