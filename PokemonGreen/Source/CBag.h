#pragma once
#include "CText.h"
#include "CItem.h"
#include "CProp.h"
namespace game_framework
{
class CBag
{
    public:
        CBag();
        void LoadBitmap();
        void CursorMove();
        void Open();
        void AddItem(int, int);
        void KeyIn(UINT);

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