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
    for (int i = 0; i < 100; i++)
    {
        item_amount[i] = 0;
    }

    TRACE("bag init\n");
    categorie_flagIndex = 3;
    panel_flagIndex = 0;
    chooser = 0;
    dropAmount = 1;
	inShowText = false;
	inSellMode , inShowText ,inItemamount, inYesno, inPanel, yesnoChooser = false;
    items.clear();
	//POSITON SET
	background_image.SetTopLeft(0, 0);
	categorie_text.SetTopLeft(CAT_LOC_LEFT, CAT_LOC_TOP);
	backpack_panel.SetTopLeft(CONSOLE_PANEL_LEFT, CONSOLE_PANEL_TOP);
	amountSelect_panel.SetTopLeft(ITEMAMOUNT_PANEL_LEFT, ITEMAMOUNT_PANEL_TOP);
	yesno_panel.SetTopLeft(YESNO_PANEL_LEFT, YESNO_PANEL_TOP);
	drop_amount.SetTopLeft(DROPAMOUNT_LEFT, DROPAMOUNT_TOP);
	item_image.SetTopLeft(ITEM_IMAGE_LEFT, ITEM_IMAGE_TOP);
	description.SetTopLeft(ITEM_DESCRIPTION_LEFT, ITEM_DESCRIPTION_TOP);
	money_panel.SetTopLeft(MONEY_PANEL_LEFT, MONEY_PANEL_TOP);
	currentMoney.SetTopLeft(CURRENTMONEY_LEFT, CURRENTMONEY_TOP);
    //PokemonMENU
    pk_Menu = new PokemonMenu();
}

void Bag::OnShow()
{
    if (pk_Menu->IsWork()) pk_Menu->OnShow();
	else
	{
		background_image.ShowBitmap();
		cursor.OnShow();
		categorie_text.OnShow();
		categorie_flag.ShowBitmap();
		item_selector.ShowBitmap();
		int itemscounter = 0;
		//showItem
		for (vector<CItem*>::iterator item_itr = items.begin(); item_itr != items.end(); ++item_itr)
		{
			if ((*item_itr)->GetCategorie() == categorie_flagIndex) {
				item_name.SetText((*item_itr)->GetName());
				item_name.SetTopLeft(ITEM_NAME_LEFT, ITEM_TOP + 24 * itemscounter);
				item_name.OnShow();
				item_left_amount.SetText("x" + to_string(item_amount[(*item_itr)->GetID()]));
				item_left_amount.SetTopLeft(ITEM_LEFTAMOUNT_LEFT, ITEM_TOP + 24 * itemscounter);
				item_left_amount.OnShow();
				itemscounter++;
			}
		}
		//showBackItem
		item_name.SetText("exit");
		item_name.SetTopLeft(ITEM_NAME_LEFT, ITEM_TOP + 24 * itemscounter);
		item_name.OnShow();
		//
		if (chooser < Get_CurrentCategorie_Size()) {
			
			SelectItem()->GetImage()->SetTopLeft(ITEM_IMAGE_LEFT, ITEM_IMAGE_TOP);
			SelectItem()->GetImage()->ShowBitmap();
			description.SetText(SelectItem()->GetDescription());
			description.OnShow();
		}
		else {
			item_image.ShowBitmap();
			description.SetText("back");
			description.OnShow();
		}
		if (!inSellMode) {
			if (inYesno) {
				yesno_panel.ShowBitmap();
				panel_selector.ShowBitmap();
			}
			if (inItemamount) {
				amountSelect_panel.ShowBitmap();
				drop_amount.OnShow();
			}
			if (inPanel) {
				backpack_panel.ShowBitmap();
				panel_selector.ShowBitmap();
			}
		}
		else {
			if (inShowText || inYesno || inItemamount) {
				clerkDialog.OnShow();
				money_panel.ShowBitmap();
				currentMoney.OnShow();
			}
			if (inYesno) {
				yesno_panel.ShowBitmap();
				panel_selector.ShowBitmap();
			}
			if (inItemamount) {
				amountSelect_panel.ShowBitmap();
				drop_amount.OnShow();	
			}
		}
	}
}

void Bag::OnMove()
{
    if (pk_Menu->IsWork())  pk_Menu->OnMove();
    else
    {
		cursor.OnMove();
		if (inSellMode) {
			clerkDialog.OnMove();
			currentMoney.SetText(to_string(*(money)));
			if (inShowText) {
				if(yesnoChooser) clerkDialog.SetText("thank you very much.");
				else clerkDialog.SetText("dont let me see you.");
			}
			if (inYesno) {
				if (yesnoChooser) panel_selector.SetTopLeft(YESNOCHOOSER_LEFT, YESNOCHOOSER_TOP1);
				else panel_selector.SetTopLeft(YESNOCHOOSER_LEFT, YESNOCHOOSER_TOP2);
				clerkDialog.SetText("you sure about this?");
			}
			if (inItemamount) {
				drop_amount.SetTopLeft(DROPAMOUNT_LEFT, DROPAMOUNT_TOP - 150);
				amountSelect_panel.SetTopLeft(ITEMAMOUNT_PANEL_LEFT, ITEMAMOUNT_PANEL_TOP - 150);
				drop_amount.SetText(to_string(dropAmount));
				clerkDialog.SetText("i give you " + to_string(int(SelectItem()->GetCost()*dropAmount*0.5)) + " to buy this stuff");
			}
		}
		else {
			if (inYesno) {
				if (yesnoChooser) panel_selector.SetTopLeft(YESNOCHOOSER_LEFT , YESNOCHOOSER_TOP1);
				else panel_selector.SetTopLeft(YESNOCHOOSER_LEFT , YESNOCHOOSER_TOP2);
			}
			else if(inItemamount) drop_amount.SetText(to_string(dropAmount));
			else if (inPanel) {
				switch (panel_flagIndex)
				{
				case 0:
					panel_selector.SetTopLeft(360, 370);
					break;

				case 1:
					panel_selector.SetTopLeft(490, 370);
					break;

				case 2:
					panel_selector.SetTopLeft(360, 425);
					break;

				case 3:
					panel_selector.SetTopLeft(490, 425);
					break;
				}
			}
			if (dynamic_cast<PokemonMenu*>(pk_Menu)->SuccessToUseItem() || dynamic_cast<PokemonMenu*>(pk_Menu)->SuccessToTakeItem())
			{
				TRACE("drop : %d\n", currentID);
				DropItem(SelectItem()->GetID(), 1);
				End();
			}
		}
		///// show everytime
		switch (categorie_flagIndex)
		{
		case 1:
			categorie_text.SetText("item");
			categorie_flag.SetTopLeft(CAT_FLAG_LEFT1, CAT_FLAG_TOP);
			break;

		case 2:
			categorie_text.SetText("ball");
			categorie_flag.SetTopLeft(CAT_FLAG_LEFT2, CAT_FLAG_TOP);
			break;

		case 3:
			categorie_text.SetText("scroll");
			categorie_flag.SetTopLeft(CAT_FLAG_LEFT3, CAT_FLAG_TOP);
			break;

		case 4:
			categorie_text.SetText("fruit");
			categorie_flag.SetTopLeft(CAT_FLAG_LEFT4, CAT_FLAG_TOP);
			break;

		case 5:
			categorie_text.SetText("goods");
			categorie_flag.SetTopLeft(CAT_FLAG_LEFT5, CAT_FLAG_TOP);
			break;
		}
		item_selector.SetTopLeft(ITEM_CHOOSER_LEFT, ITEM_CHOOSER_TOP + 24 * chooser);
    }
}

void Bag::LoadBitmap()
{
    background_image.LoadBitmap(BG_BACKPACK);
    backpack_panel.LoadBitmap(BG_PANEL);
    amountSelect_panel.LoadBitmap(BG_ITEMAMOUNT);
    yesno_panel.LoadBitmap(BG_YESNO);
    ///////////////////////
    cursor.AddBitmap(BG_BACKPACK_CURSOR1, RGB(255, 0, 0));
    cursor.AddBitmap(BG_BACKPACK_CURSOR2, RGB(255, 0, 0));
    cursor.AddBitmap(BG_BACKPACK_CURSOR3, RGB(255, 0, 0));
    cursor.SetDelayCount(6);
    cursor.SetTopLeft(55, 27);
    categorie_flag.LoadBitmap(BG_BACKPACK_FLAG);
    item_selector.LoadBitmap(IDB_CURSOR, RGB(255, 0, 0));
	panel_selector.LoadBitmap(IDB_CURSOR, RGB(255, 0, 0));
    ///////////////////////
    item_name.LoadBitmap();
	item_cost.LoadBitmap();
    item_left_amount.LoadBitmap();
    description.LoadBitmap();
    item_image.LoadBitmap(BG_BACKPACK_BACK);
	drop_amount.LoadBitmap();
	categorie_text.LoadBitmap();
	clerkDialog.InitDialog('n');
	money_panel.LoadBitmap(SHOP_MONEY_PANEL);
	currentMoney.LoadBitmap();
    //////////////////////
}

void Bag::KeyDownListener(UINT nChar)
{
    const char KEY_LEFT = 0x25; 
    const char KEY_UP = 0x26; 
    const char KEY_RIGHT = 0x27; 
    const char KEY_DOWN = 0x28;
    const char KEY_Z = 0x5a;
    const char KEY_X = 0x58;

    if (pk_Menu->IsWork())
    {
        pk_Menu->KeyDownListener(nChar);
    }
    else
    {
		if (inSellMode) {
			if (inShowText) {
				if (nChar == KEY_Z) {
					inShowText = false;
					inSellMode = false;
					End();
				}
			}
			else if (inYesno) {
				switch (nChar) {
					case KEY_UP: yesnoChooser = true; break;
					case KEY_DOWN: yesnoChooser = false; break;
					case KEY_Z:
						if (yesnoChooser) {
							(*money) += int(SelectItem()->GetCost() * dropAmount * 0.5);
							DropItem(SelectItem()->GetID(), dropAmount);
						}
						dropAmount = 1;
						inYesno = false;
						inShowText = true;
						break;
					case KEY_X:
						inItemamount = true;
						inYesno = false;
						break;
				}
			}
			else if (inItemamount) {
				switch (nChar) {
				case KEY_UP:
					if (dropAmount < item_amount[SelectItem()->GetID()]) dropAmount++;
					break;
				case KEY_DOWN:
					if (dropAmount > 1) dropAmount--;
					break;
				case KEY_Z:
					inYesno = true;
					inItemamount = false;
					break;
				case KEY_X:
					dropAmount = 1;
					inItemamount = false;
					break;
				}
			}
			else {
				switch (nChar) {
				case KEY_UP:
					if (chooser > 0) chooser--;
					break;
				case KEY_DOWN:
					if (chooser < Get_CurrentCategorie_Size()) chooser++;
					break;
				case KEY_LEFT:
					if (categorie_flagIndex > 1) {
						chooser = 0;
						categorie_flagIndex--;
					}
					break;
				case KEY_RIGHT:
					if (categorie_flagIndex < 5) {
						chooser = 0;
						categorie_flagIndex++;
					}
					break;
				case KEY_Z:
					if (chooser == Get_CurrentCategorie_Size()) End();
					else inItemamount = true;
					break;
				case KEY_X: 
					inSellMode = false;
					End();
					break;
				
				}
			}
		}
		else {
			if (inYesno) {
				switch (nChar) {
					case KEY_UP: yesnoChooser = true; break;
					case KEY_DOWN: yesnoChooser = false; break;
					case KEY_Z: 
						if(yesnoChooser) DropItem(SelectItem()->GetID(), dropAmount);
						dropAmount = 1;
						inYesno = false;
						break;
					case KEY_X: 
						inItemamount = true;
						inYesno = false;
						break;
				}
			}
			else if (inItemamount) {
				switch (nChar) {
					case KEY_UP: 
						if (dropAmount < item_amount[SelectItem()->GetID()]) dropAmount++;
						break;
					case KEY_DOWN: 
						if (dropAmount > 1) dropAmount--; 
						break;
					case KEY_Z: 
						inYesno = true;
						inItemamount = false;
						break;
					case KEY_X: 
						dropAmount = 1;
						inPanel = true;
						inItemamount = false;
						break;
				}
			}
			else if (inPanel) {
				switch (nChar) {
					case KEY_UP: 
						if (panel_flagIndex == 2) panel_flagIndex = 0;
						if (panel_flagIndex == 3) panel_flagIndex = 1;
						break;
					case KEY_DOWN: 
						if (panel_flagIndex == 0) panel_flagIndex = 2;
						if (panel_flagIndex == 1) panel_flagIndex = 3;
						break;
					case KEY_LEFT: 
						if (panel_flagIndex == 1) panel_flagIndex = 0;
						if (panel_flagIndex == 3) panel_flagIndex = 2;
						break;
					case KEY_RIGHT: 
						if (panel_flagIndex == 0) panel_flagIndex = 1;
						if (panel_flagIndex == 2) panel_flagIndex = 3;
						break;
					case KEY_Z: 
						switch (panel_flagIndex)
						{
							case 0:
								dynamic_cast<PokemonMenu*>(pk_Menu)->GetCurrentItemCommend(1, SelectItem()->GetID());
								pk_Menu->Start();
								break;
							case 1:
								dynamic_cast<PokemonMenu*>(pk_Menu)->GetCurrentItemCommend(2, SelectItem()->GetID());
								pk_Menu->Start();
								break;
							case 2:
								inItemamount = true;
								break;
						}
						inPanel = false;
						break;
					case KEY_X: 
						inPanel = false; 
						panel_flagIndex = 0;
						break;
				}
			}
			else {
				switch (nChar) {
					case KEY_UP: 
						if (chooser > 0) chooser--;
						break;
					case KEY_DOWN: 
						if (chooser < Get_CurrentCategorie_Size()) chooser++;
						break;
					case KEY_LEFT: 
						if (categorie_flagIndex > 1) {
							chooser = 0;
							categorie_flagIndex--;
						}
						break;
					case KEY_RIGHT:
						if (categorie_flagIndex < 5) {
							chooser = 0;
							categorie_flagIndex++;
						}
						break;
					case KEY_Z:
						if (chooser == Get_CurrentCategorie_Size()) End();
						else inPanel = true; 
						break;
					case KEY_X: End(); break;
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
	if (item_amount[itemId] == 0) {
		TRACE("INSEFT ITEM: %d\n", itemId);
		CItem* new_Item = new CItem(itemId);
		items.push_back(new_Item);
		item_amount[itemId] += amount;
	}
    else item_amount[itemId] += amount;
}
void Bag::DropItem(int itemId, int amount)
{
	for (vector<CItem*>::iterator item_itr = items.begin(); item_itr != items.end(); ++item_itr)
	{
		if ((*item_itr)->GetID() == itemId)
		{
			if (item_amount[(*item_itr)->GetID()] == amount)
			{
				item_amount[(*item_itr)->GetID()] = 0;
				item_itr = items.erase(item_itr);
			}
			else
			{
				item_amount[(*item_itr)->GetID()] -= amount;
			}
		}

		if (items.empty()) break;
	}
}
void Bag::SetSellMode(int* money)
{
	this->money = money;
    inSellMode = true;
}
int Bag::GetItemAmount(int itemID)
{
    return item_amount[itemID];
}
void Bag::End()
{
	chooser = 0;
    isWork = false;
}
unsigned int Bag::Get_CurrentCategorie_Size()
{
	int itemscounter = 0;
	
	for (vector<CItem*>::iterator item_itr = items.begin(); item_itr != items.end(); ++item_itr) {
		if (categorie_flagIndex == (*item_itr)->GetCategorie()) itemscounter++;
	}
	return itemscounter;
}
CItem* Bag::SelectItem()
{
	//chooser
	int counter = 0;
	for (vector<CItem*>::iterator item_itr = items.begin(); item_itr != items.end(); ++item_itr) {
		if (counter == chooser) return (*item_itr);
		if (categorie_flagIndex == (*item_itr)->GetCategorie()) counter++;
	}
	return nullptr;
}
}