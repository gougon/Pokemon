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
Bag::Bag() :
    ActionObject(), inItemamount(false), inYesno(false), inPanel(false), yesnoChooser(false)
{
}
void Bag::Init()
{
    for (int i = 0; i < 10; i++)
    {
        item_amount[i] = 0;
    }

    TRACE("bag init\n");
    categorie_flagIndex = 3;
    panel_flagIndex = 0;
    chooser = 0;
    dropAmount = 1;
    inSellMode = false;
    inItemamount, inYesno, inPanel, yesnoChooser = false;
    item_Prop.clear();
    //PokemonMENU
    inPokemonMenu = false;
    pk_Menu = new PokemonMenu();
    //this->pk_Menu = inPk_Menu;
}

void Bag::OnShow()
{
    if (pk_Menu->IsWork()) pk_Menu->OnShow();
    else
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
                text.SetText("goods");
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
                    item_left_amount.SetText("x" + to_string(item_amount[(*item_itr)->GetID()]));
                    item_left_amount.SetTopLeft(560, 50 + 24 * item_counter);
                    item_left_amount.OnShow();
                    item_counter++;
                }

                break;

            case 2:
                for (vector<CBall*>::iterator item_itr = item_Balls.begin(); item_itr != item_Balls.end(); ++item_itr)
                {
                    item_name.SetText((*item_itr)->GetName());
                    item_name.SetTopLeft(340, 50 + 24 * item_counter);
                    item_name.OnShow();
                    item_left_amount.SetText("x" + to_string(item_amount[(*item_itr)->GetID()]));
                    item_left_amount.SetTopLeft(560, 50 + 24 * item_counter);
                    item_left_amount.OnShow();
                    item_counter++;
                }

                break;

            case 3:
                for (vector<CScrolls*>::iterator item_itr = item_Scrolls.begin(); item_itr != item_Scrolls.end(); ++item_itr)
                {
                    item_name.SetText((*item_itr)->GetName());
                    item_name.SetTopLeft(340, 50 + 24 * item_counter);
                    item_name.OnShow();
                    item_left_amount.SetText("x" + to_string(item_amount[(*item_itr)->GetID()]));
                    item_left_amount.SetTopLeft(560, 50 + 24 * item_counter);
                    item_left_amount.OnShow();
                    item_counter++;
                }

                break;

            case 4:
                for (vector<CFruit*>::iterator item_itr = item_Fruit.begin(); item_itr != item_Fruit.end(); ++item_itr)
                {
                    item_name.SetText((*item_itr)->GetName());
                    item_name.SetTopLeft(340, 50 + 24 * item_counter);
                    item_name.OnShow();
                    item_left_amount.SetText("x" + to_string(item_amount[(*item_itr)->GetID()]));
                    item_left_amount.SetTopLeft(560, 50 + 24 * item_counter);
                    item_left_amount.OnShow();
                    item_counter++;
                }

                break;

            case 5:
                for (vector<CGoods*>::iterator item_itr = item_Goods.begin(); item_itr != item_Goods.end(); ++item_itr)
                {
                    item_name.SetText((*item_itr)->GetName());
                    item_name.SetTopLeft(340, 50 + 24 * item_counter);
                    item_name.OnShow();
                    item_left_amount.SetText("x" + to_string(item_amount[(*item_itr)->GetID()]));
                    item_left_amount.SetTopLeft(560, 50 + 24 * item_counter);
                    item_left_amount.OnShow();
                    item_counter++;
                }

                break;
        }

        item_selector.SetTopLeft(310, 62 + 24 * chooser);
        item_selector.ShowBitmap();

        if (categorie_flagIndex == 1 && chooser != int(item_Prop.size()))
        {
            if (!inItemamount && !inYesno)
            {
                description.SetText(item_Prop[chooser]->GetDescription());
                description.SetTopLeft(15, 300);
                description.OnShow();
            }

            item_Prop[chooser]->GetImage()->SetTopLeft(13, 217);
            item_Prop[chooser]->GetImage()->ShowBitmap();
        }
        else if (categorie_flagIndex == 2 && chooser != int(item_Balls.size()))
        {
            if (!inItemamount && !inYesno)
            {
                description.SetText(item_Balls[chooser]->GetDescription());
                description.SetTopLeft(15, 300);
                description.OnShow();
            }

            item_Balls[chooser]->GetImage()->SetTopLeft(13, 217);
            item_Balls[chooser]->GetImage()->ShowBitmap();
        }
        else if (categorie_flagIndex == 3 && chooser != int(item_Scrolls.size()))
        {
            if (!inItemamount && !inYesno)
            {
                description.SetText(item_Scrolls[chooser]->GetDescription());
                description.SetTopLeft(15, 300);
                description.OnShow();
            }

            item_Scrolls[chooser]->GetImage()->SetTopLeft(13, 217);
            item_Scrolls[chooser]->GetImage()->ShowBitmap();
        }
        else if (categorie_flagIndex == 4 && chooser != int(item_Fruit.size()))
        {
            if (!inItemamount && !inYesno)
            {
                description.SetText(item_Fruit[chooser]->GetDescription());
                description.SetTopLeft(15, 300);
                description.OnShow();
            }

            item_Fruit[chooser]->GetImage()->SetTopLeft(13, 217);
            item_Fruit[chooser]->GetImage()->ShowBitmap();
        }
        else if (categorie_flagIndex == 5 && chooser != int(item_Goods.size()))
        {
            if (!inItemamount && !inYesno)
            {
                description.SetText(item_Goods[chooser]->GetDescription());
                description.SetTopLeft(15, 300);
                description.OnShow();
            }

            item_Goods[chooser]->GetImage()->SetTopLeft(13, 217);
            item_Goods[chooser]->GetImage()->ShowBitmap();
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
            //show the amount you want to drop
            text.SetText(to_string(dropAmount));
            text.SetTopLeft(565, 410);
            text.OnShow();
            //show the desription what amount want drop
            description.SetText("choose the amount");
            description.SetTopLeft(15, 300);
            description.OnShow();
        }

        if (inYesno)
        {
            yesno_panel.ShowBitmap();
            description.SetText("you sure ?");
            description.SetTopLeft(15, 300);
            description.OnShow();

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
}

void Bag::OnMove()
{
    cursor.OnMove();

    if (pk_Menu->IsWork())  pk_Menu->OnMove();
    else
    {
        if (dynamic_cast<PokemonMenu*>(pk_Menu)->SuccessToUseItem() || dynamic_cast<PokemonMenu*>(pk_Menu)->SuccessToTakeItem())
        {
            DropItem(currentID, 1);
            End();
        }
    }
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
    item_left_amount.LoadBitmap();
    description.LoadBitmap();
    item_image.LoadBitmap(BG_BACKPACK_BACK);
    //////////////////////
    //if (pk_Menu->IsWork()) pk_Menu->LoadBitmap();
}

void Bag::KeyDownListener(UINT nChar)
{
    const char KEY_LEFT = 0x25; // keyboard���b�Y
    const char KEY_UP = 0x26; // keyboard�W�b�Y
    const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
    const char KEY_DOWN = 0x28; // keyboard�U�b�Y
    const char KEY_Z = 0x5a;
    const char KEY_X = 0x58;
    TRACE("panel = %d\n", panel_flagIndex);

    if (pk_Menu->IsWork())
    {
        pk_Menu->KeyDownListener(nChar);
    }
    else
    {
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
                if ((categorie_flagIndex == 1 && chooser < int(item_Prop.size())) ||
                        (categorie_flagIndex == 2 && chooser < int(item_Balls.size())) ||
                        (categorie_flagIndex == 3 && chooser < int(item_Scrolls.size())) ||
                        (categorie_flagIndex == 4 && chooser < int(item_Fruit.size())) ||
                        (categorie_flagIndex == 5 && chooser < int(item_Goods.size()))
                   ) chooser++;
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
            else if (inSellMode)
            {
                inSellMode = false;
                End();
            }
            else End();
        }

        if (nChar == KEY_Z)
        {
            if (inSellMode)
            {
                //
            }
            else
            {
                //Exit function
                if (!inPanel && categorie_flagIndex == 1 && chooser == int(item_Prop.size()))
                {
                    End();
                }
                else if (!inPanel && categorie_flagIndex == 2 && chooser == int(item_Balls.size()))
                {
                    End();
                }
                else if (!inPanel && categorie_flagIndex == 3 && chooser == int(item_Scrolls.size()))
                {
                    End();
                }
                else if (!inPanel && categorie_flagIndex == 4 && chooser == int(item_Fruit.size()))
                {
                    End();
                }
                else if (!inPanel && categorie_flagIndex == 5 && chooser == int(item_Goods.size()))
                {
                    End();
                }
                //yesno
                else if (inYesno)
                {
                    inYesno = false;

                    if (!yesnoChooser)
                        inItemamount = true;
                    else
                    {
                        if (categorie_flagIndex == 1) DropItem(item_Prop[chooser]->GetID(), dropAmount);

                        if (categorie_flagIndex == 2) DropItem(item_Balls[chooser]->GetID(), dropAmount);

                        if (categorie_flagIndex == 3) DropItem(item_Scrolls[chooser]->GetID(), dropAmount);

                        if (categorie_flagIndex == 4) DropItem(item_Fruit[chooser]->GetID(), dropAmount);

                        if (categorie_flagIndex == 5) DropItem(item_Goods[chooser]->GetID(), dropAmount);

                        dropAmount = 1;
                    }

                    inItemamount = false;
                    inPanel = false;
                }
                //itemamount
                else if (inItemamount)
                {
                    inYesno = true;
                    inItemamount = false;
                }
                else if (inPanel && (panel_flagIndex == 0 || panel_flagIndex == 1))
                {
                    switch (categorie_flagIndex)
                    {
                        case 1:
                            currentID = item_Prop[chooser]->GetID();
                            break;

                        case 2:
                            currentID = item_Balls[chooser]->GetID();
                            break;

                        case 3:
                            currentID = item_Scrolls[chooser]->GetID();
                            break;

                        case 4:
                            currentID = item_Fruit[chooser]->GetID();
                            break;

                        case 5:
                            currentID = item_Goods[chooser]->GetID();
                            break;
                    }

                    inPanel = false;
                    //inPokemonMenu = true;
                    pk_Menu->Start();

                    if (panel_flagIndex == 0)
                        dynamic_cast<PokemonMenu*>(pk_Menu)->ReceiveItem(1, currentID);
                    else dynamic_cast<PokemonMenu*>(pk_Menu)->ReceiveItem(2, currentID);
                }
                else if (inPanel && panel_flagIndex == 2)
                {
                    inItemamount = true;
                    inPanel = false;
                }
                else if (inPanel && panel_flagIndex == 3)
                {
                    inPanel = false;
                }
                else
                {
                    inPanel = true;
                }
            }
        }
    }
}
void Bag::RecievePokemonMenu(ActionObject* inPk_Menu)
{
    this->pk_Menu = inPk_Menu;
}
void Bag::AddItem(int itemId, int amount)
{
    if (itemId <= 2 && item_amount[itemId] == 0)
    {
        CProp* new_Prop = new CProp(itemId);
        item_Prop.push_back(new_Prop);
        item_amount[new_Prop->GetID()] += amount;
    }
    else if (itemId == Item_FighterGlove && item_amount[itemId] == 0)
    {
        CGoods* new_Goods = new CGoods(itemId);
        item_Goods.push_back(new_Goods);
        item_amount[new_Goods->GetID()] += amount;
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
                }
            }

            if (item_Prop.empty()) break;
        }
    }
    else if (categorie_flagIndex == 2)
    {
        for (vector<CBall*>::iterator item_itr = item_Balls.begin(); item_itr != item_Balls.end(); ++item_itr)
        {
            if ((*item_itr)->GetID() == itemId)
            {
                if (item_amount[(*item_itr)->GetID()] == amount)
                {
                    item_itr = item_Balls.erase(item_itr);
                }
                else
                {
                    item_amount[(*item_itr)->GetID()] -= amount;
                }
            }

            if (item_Balls.empty()) break;
        }
    }
    else if (categorie_flagIndex == 3)
    {
        for (vector<CScrolls*>::iterator item_itr = item_Scrolls.begin(); item_itr != item_Scrolls.end(); ++item_itr)
        {
            if ((*item_itr)->GetID() == itemId)
            {
                if (item_amount[(*item_itr)->GetID()] == amount)
                {
                    item_itr = item_Scrolls.erase(item_itr);
                }
                else
                {
                    item_amount[(*item_itr)->GetID()] -= amount;
                }
            }

            if (item_Scrolls.empty()) break;
        }
    }
    else if (categorie_flagIndex == 4)
    {
        for (vector<CFruit*>::iterator item_itr = item_Fruit.begin(); item_itr != item_Fruit.end(); ++item_itr)
        {
            if ((*item_itr)->GetID() == itemId)
            {
                if (item_amount[(*item_itr)->GetID()] == amount)
                {
                    item_itr = item_Fruit.erase(item_itr);
                }
                else
                {
                    item_amount[(*item_itr)->GetID()] -= amount;
                }
            }

            if (item_Fruit.empty()) break;
        }
    }
    else
    {
        for (vector<CGoods*>::iterator item_itr = item_Goods.begin(); item_itr != item_Goods.end(); ++item_itr)
        {
            if ((*item_itr)->GetID() == itemId)
            {
                if (item_amount[(*item_itr)->GetID()] == amount)
                {
                    item_itr = item_Goods.erase(item_itr);
                }
                else
                {
                    item_amount[(*item_itr)->GetID()] -= amount;
                }
            }

            if (item_Goods.empty()) break;
        }
    }
}
void Bag::SetSellMode()
{
    inSellMode = true;
}
int Bag::GetItemAmount(int itemID)
{
    return item_amount[itemID];
}
void Bag::End()
{
    isWork = false;
}
}