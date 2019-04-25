#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"
#include "PokemonMenu.h"
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
        Bag();
        virtual void Init();
        virtual void OnShow();
        virtual void OnMove();
        virtual void LoadBitmap();
        virtual void KeyDownListener(UINT nChar);
        void RecievePokemonMenu(ActionObject*);
        void AddItem(int, int);
        void DropItem(int, int);
        void SetSellMode();
        int GetItemAmount(int itemID);
        void End();
    private:
        int categorie_flagIndex, panel_flagIndex;
        unsigned int chooser, dropAmount, currentID;
        unsigned int item_amount[MAXITEMAMOUNT];
        bool inSellMode;
        bool inPokemonMenu, inPanel, inItemamount, inYesno, yesnoChooser;
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
        ActionObject* pk_Menu;
};
}
