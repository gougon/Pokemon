#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Bag.h"

namespace game_framework
{
void Bag::Init()
{
    for (int i = 0; i < 10; i++)
    {
        item_amount[i] = 0;
    }

    categorie_flagIndex = 3;
    panel_flagIndex = 0;
    chooser = 0;
    dropAmount = 1;
    inItemamount, inYesno, inPanel, yesnoChooser = false;
    item_Prop.clear();
}

void Bag::OnShow()
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

    if (inPanel)
    {
        backpack_panel.ShowBitmap();

        switch (panel_flagIndex)
        {
            case 0:
                item_selector.SetTopLeft(360, 370);
                break;

            case 1:
                item_selector.SetTopLeft(490, 370);
                break;

            case 2:
                item_selector.SetTopLeft(360, 425);
                break;

            case 3:
                item_selector.SetTopLeft(490, 425);
                break;

            default:
                break;
        }

        item_selector.ShowBitmap();
    }

    if (inItemamount)
    {
        amountSelect_panel.ShowBitmap();
    }

    if (inYesno)
    {
        yesno_panel.ShowBitmap();

        if (yesnoChooser)
        {
            item_selector.SetTopLeft(513, 365);
        }
        else
        {
            item_selector.SetTopLeft(513, 415);
        }

        item_selector.ShowBitmap();
    }
}

void Bag::OnMove()
{
    cursor.OnMove();
}

void Bag::LoadBitmap()
{
    background_image.LoadBitmap(BG_BACKPACK);
    backpack_panel.LoadBitmap(BG_PANEL);
    amountSelect_panel.LoadBitmap(BG_ITEMAMOUNT);
    yesno_panel.LoadBitmap(BG_YESNO);
    background_image.SetTopLeft(0, 0);
    backpack_panel.SetTopLeft(345, 340);
    amountSelect_panel.SetTopLeft(495, 385);
    yesno_panel.SetTopLeft(495, 335);
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

void Bag::KeyDownListener(UINT nChar)
{
    const char KEY_LEFT = 0x25; // keyboard左箭頭
    const char KEY_UP = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN = 0x28; // keyboard下箭頭
    const char KEY_Z = 0x5a;
    const char KEY_X = 0x58;
    TRACE("panel = %d\n", panel_flagIndex);

    if (nChar == KEY_LEFT)
    {
        if (!inPanel && !inItemamount && !inYesno && categorie_flagIndex > 1)
        {
            categorie_flagIndex--;
            chooser = 0;
        }

        if (inPanel)
        {
            if (panel_flagIndex == 1) panel_flagIndex = 0;

            if (panel_flagIndex == 3) panel_flagIndex = 2;
        }
    }

    if (nChar == KEY_RIGHT)
    {
        if (!inPanel && !inItemamount && !inYesno && categorie_flagIndex < 5)
        {
            categorie_flagIndex++;
            chooser = 0;
        }

        if (inPanel)
        {
            if (panel_flagIndex == 0) panel_flagIndex = 1;

            if (panel_flagIndex == 2) panel_flagIndex = 3;
        }
    }

    if (nChar == KEY_UP)
    {
        if (!inPanel && !inItemamount && !inYesno && chooser >= 1) chooser--;

        if (inPanel)
        {
            if (panel_flagIndex == 2) panel_flagIndex = 0;

            if (panel_flagIndex == 3) panel_flagIndex = 1;
        }

        if (inItemamount)
        {
            if (categorie_flagIndex == 1 && dropAmount < item_amount[(item_Prop[chooser]->GetID())])
                dropAmount++;

            TRACE("You choose %d item to drop\n", dropAmount);
        }

        if (inYesno)
        {
            yesnoChooser = true;
        }
    }

    if (nChar == KEY_DOWN)
    {
        if (!inPanel && !inItemamount && !inYesno)
        {
            if (categorie_flagIndex == 1 && chooser < int(item_Prop.size())) chooser++;
        }

        if (inPanel)
        {
            if (panel_flagIndex == 0) panel_flagIndex = 2;

            if (panel_flagIndex == 1) panel_flagIndex = 3;
        }

        if (inItemamount && dropAmount > 1)
        {
            dropAmount--;
            TRACE("You choose %d item to drop\n", dropAmount);
        }

        if (inYesno)
        {
            yesnoChooser = false;
        }
    }

    if (nChar == KEY_X)
    {
        if (inYesno)
        {
            inYesno = false;
            inItemamount = true;
        }
        else if (inItemamount)
        {
            inItemamount = false;
            inPanel = true;
        }
        else if (inPanel) inPanel = false;
        else End();
    }

    if (nChar == KEY_Z)
    {
        TRACE("now chooser is = %d %d\n", chooser, int(item_Prop.size()));

        //Prop function
        if (!inPanel && categorie_flagIndex == 1 && chooser == int(item_Prop.size()))
        {
            End();
        }
        else if (inYesno)
        {
            inYesno = false;

            if (!yesnoChooser)
                inItemamount = true;
            else
            {
                DropItem(item_Prop[chooser]->GetID(), dropAmount);
                dropAmount = 1;
            }

            inItemamount = false;
            inPanel = false;
        }
        else if (inItemamount)
        {
            inYesno = true;
            inItemamount = false;
        }
        else if (inPanel && panel_flagIndex == 2)
        {
            inItemamount = true;
            inPanel = false;
        }
        else
        {
            inPanel = true;
        }
    }
}
void Bag::AddItem(int itemId, int amount)
{
    if (itemId == 0 && item_amount[itemId] == 0)
    {
        CProp* new_Prop = new CProp(itemId);
        item_Prop.push_back(new_Prop);
        item_amount[new_Prop->GetID()] += amount;
    }
    else item_amount[itemId] += amount;
}
void Bag::DropItem(int itemId, int amount)
{
    if (categorie_flagIndex == 1)
    {
        for (vector<CProp*>::iterator item_itr = item_Prop.begin(); item_itr != item_Prop.end(); ++item_itr)
        {
            if ((*item_itr)->GetID() == itemId)
            {
                if (item_amount[(*item_itr)->GetID()] == amount)
                {
                    item_itr = item_Prop.erase(item_itr);
                }
                else
                {
                    item_amount[(*item_itr)->GetID()] -= amount;
                    End();
                }
            }

            if (item_Prop.empty()) break;
        }
    }
}
}