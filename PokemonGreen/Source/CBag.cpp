#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <string>
#include "CBag.h"
using namespace std;
namespace game_framework
{
CBag::CBag()
{
    for (int i = 0; i < 10; i++)
    {
        item_amount[i] = 0;
    }

    categorie_flagIndex = 3;
    chooser = 0;
    item_Prop.clear();
}

void CBag::LoadBitmap()
{
    background_image.LoadBitmap(BG_BACKPACK);
    background_image.SetTopLeft(0, 0);
    ///////////////////////
    cursor.AddBitmap(BG_BACKPACK_CURSOR1, RGB(255, 0, 0));
    cursor.AddBitmap(BG_BACKPACK_CURSOR2, RGB(255, 0, 0));
    cursor.AddBitmap(BG_BACKPACK_CURSOR3, RGB(255, 0, 0));
    cursor.SetDelayCount(6);
    cursor.SetTopLeft(55, 27);
    categorie_flag.LoadBitmap(BG_BACKPACK_FLAG);
    item_selector.LoadBitmap(BG_BACKPACK_ITEMCURSOR, RGB(255, 0, 0));
    ///////////////////////
    text.LoadBitmap();
    item_name.LoadBitmap();
    description.LoadBitmap();
    item_image.LoadBitmap(BG_BACKPACK_BACK);
}

void CBag::CursorMove()
{
    cursor.OnMove();
}


void CBag::Open()
{
    background_image.ShowBitmap();
    cursor.OnShow();

    switch (categorie_flagIndex)
    {
        case 1:
            text.SetText("item");
            categorie_flag.SetTopLeft(113, 84);
            break;

        case 2:
            text.SetText("ball");
            categorie_flag.SetTopLeft(135, 84);
            break;

        case 3:
            text.SetText("scroll");
            categorie_flag.SetTopLeft(158, 84);
            break;

        case 4:
            text.SetText("fruit");
            categorie_flag.SetTopLeft(178, 84);
            break;

        case 5:
            text.SetText("good");
            categorie_flag.SetTopLeft(200, 84);
            break;
    }

    text.SetTopLeft(105, 27);
    text.OnShow();
    categorie_flag.ShowBitmap();
    int item_counter = 0;

    //showItem
    switch (categorie_flagIndex)
    {
        case 1:
            TRACE("item_prop_size = %d\n", item_Prop.size());

            for (vector<CProp*>::iterator item_itr = item_Prop.begin(); item_itr != item_Prop.end(); ++item_itr)
            {
                item_name.SetText((*item_itr)->GetName());
                item_name.SetTopLeft(340, 50 + 24 * item_counter);
                item_name.OnShow();
                item_counter++;
            }

            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;
    }

    item_selector.SetTopLeft(310, 62 + 24 * chooser);
    item_selector.ShowBitmap();

    if (categorie_flagIndex == 1 && chooser != int(item_Prop.size()))
    {
        description.SetText(item_Prop[chooser]->GetDescription());
        description.SetTopLeft(15, 300);
        description.OnShow();
        item_Prop[chooser]->GetImage()->SetTopLeft(13, 217);
        item_Prop[chooser]->GetImage()->ShowBitmap();
    }
    else
    {
        description.SetText("back");
        description.SetTopLeft(15, 300);
        description.OnShow();
        item_image.SetTopLeft(13, 217);
        item_image.ShowBitmap();
    }

    ///////
    item_name.SetText("exit");
    item_name.SetTopLeft(340, 50 + 24 * item_counter);
    item_name.OnShow();
}
void CBag::AddItem(int itemId, int amount)
{
    //直接增加
    if (itemId == 0)
    {
        TRACE("add antidote\n");
        CProp* new_Prop = new CProp(itemId);
        item_Prop.push_back(new_Prop);
        item_amount[new_Prop->GetID()] += amount;
    }
}
void CBag::KeyIn(UINT nChar)
{
    const char KEY_LEFT = 0x25; // keyboard左箭頭
    const char KEY_UP = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN = 0x28; // keyboard下箭頭

    if (nChar == KEY_LEFT) if (categorie_flagIndex > 1)
        {
            categorie_flagIndex--;
            chooser = 0;
        }

    if (nChar == KEY_RIGHT) if (categorie_flagIndex < 5)
        {
            categorie_flagIndex++;
            chooser = 0;
        }

    if (nChar == KEY_UP) if (chooser >= 1) chooser--;

    if (nChar == KEY_DOWN) if (categorie_flagIndex == 1 && chooser < int(item_Prop.size())) chooser++;
}
}
