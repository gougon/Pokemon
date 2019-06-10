#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Clerk.h"
namespace game_framework {
	Clerk::Clerk()
	{
		inItemAmount = false;
		shopping_list.clear();
	}
	Clerk::~Clerk()
	{
		for (auto i : shopping_list)
			delete i;
	}
	void Clerk::Init()
	{
		inBuyMode = false;
		inSellMode = false;
		inSelectMode = true;
		inShowText = false;
		inItemAmount = false;
		firsttime = false;
		selectModeOrder = 1;
		itemChooser = 0;
		itemAmount = 1;
		tradeModeSelectPanel.SetTopLeft(MODE_SELECT_LEFT, MODE_SELECT_TOP);
		moneyPanel.SetTopLeft(MONEY_PANEL_LEFT, MONEY_PANEL_TOP);
		currentMoney.SetTopLeft(CURRENTMONEY_LEFT, CURRENTMONEY_TOP);
		itemImagePanel.SetTopLeft(IMAGE_PANEL_LEFT, IMAGE_PANEL_TOP);
		itemDescriptionPanel.SetTopLeft(DESCRIPTION_PANEL_LEFT, DESCRIPTION_PANEL_TOP);
		shoppingPanel.SetTopLeft(SHOPPINGLIST_LEFT, SHOPPINGLIST_TOP);
		blankPanel1.SetTopLeft(0, 248);
		blankPanel2.SetTopLeft(350, 248);
		itemDescription.SetTopLeft(30, 300);
		stillHave.SetTopLeft(40, 268);
		itemAmountText.SetTopLeft(390, 268);
		game_bag = new Bag();
		clerkTalk.InitDialog('n');

		for (int initialitem = 0; initialitem <= 5; initialitem++)
		{
			InsertItem(initialitem);
		}
	}
	void Clerk::OnShow()
	{
		if (game_bag->IsWork()) {
			hero->IsInvisiable(true);
			game_bag->OnShow();
		}
		else
		{
			if (inBuyMode)
			{
				hero->IsInvisiable(true);
				inSelectMode = false;
				itemImagePanel.ShowBitmap();
				shoppingPanel.ShowBitmap();
				moneyPanel.ShowBitmap();
				currentMoney.OnShow();
				itemDescriptionPanel.ShowBitmap();
				item_counter = 0;

				for (vector<CItem*>::iterator item_itr = shopping_list.begin(); item_itr != shopping_list.end(); ++item_itr)
				{
					itemName.SetText((*item_itr)->GetName());
					itemName.SetTopLeft(330, 45 + 50 * item_counter);
					itemName.OnShow();
					itemCost.SetText(to_string((*item_itr)->GetCost()));
					itemCost.SetTopLeft(565, 45 + 50 * item_counter);
					itemCost.OnShow();
					item_counter++;
				}

				shopping_list[itemChooser]->GetImage()->ShowBitmap();
				itemSelecter.ShowBitmap();
				itemDescription.OnShow();

				if (inItemAmount)
				{
					clerkTalk.OnShow();
					blankPanel1.ShowBitmap();
					blankPanel2.ShowBitmap();
					//itemAmountText.OnShow();
					stillHave.OnShow();
					itemAmountText.OnShow();
				}
			}
			if (inSelectMode)
			{
				hero->IsInvisiable(false);
				tradeModeSelectPanel.ShowBitmap();
				itemSelecter.ShowBitmap();
				clerkTalk.OnShow();
			}
		}
	}
	void Clerk::OnMove()
	{
		if (game_bag->IsWork()) { 
			game_bag->OnMove(); 
		}
		else
		{
			if (inBuyMode)
			{
				itemSelecter.SetTopLeft(308, 53 + 50 * itemChooser);
				shopping_list[itemChooser]->GetImage()->SetTopLeft(17, 210);
				itemDescription.SetText(shopping_list[itemChooser]->GetDescription());

				if (inItemAmount)
				{
					itemAmountText.SetText("x" + to_string(itemAmount) + "  " + to_string(itemAmount * shopping_list[itemChooser]->GetCost()));
					clerkTalk.OnMove();
					//itemAmountText.SetText(to_string(itemAmount));
				}
			}
			if (inSelectMode)  				//mode cursor
			{
				clerkTalk.SetText("welcome");
				switch (selectModeOrder)
				{
				case 1:
					itemSelecter.SetTopLeft(MODE_SELECT_CURSOR_LEFT, MODE_SELECT_CURSOR_TOP);
					break;

				case 2:
					itemSelecter.SetTopLeft(MODE_SELECT_CURSOR_LEFT, MODE_SELECT_CURSOR_TOP + 50);
					break;

				case 3:
					itemSelecter.SetTopLeft(MODE_SELECT_CURSOR_LEFT, MODE_SELECT_CURSOR_TOP + 100);
					break;
				}
			}

		}
	}
	void Clerk::LoadBitmap()
	{
		itemSelecter.LoadBitmap(IDB_CURSOR, RGB(255, 0, 0));
		tradeModeSelectPanel.LoadBitmap(TRADEMODE_SELECT, RGB(255, 0, 0));
		moneyPanel.LoadBitmap(SHOP_MONEY_PANEL, RGB(255, 0, 0));
		shoppingPanel.LoadBitmap(SHOP_ITEMLIST_PANEL, RGB(255, 0, 0));
		itemImagePanel.LoadBitmap(SHOP_IMAGE_PANEL);
		itemDescriptionPanel.LoadBitmap(SHOP_DESCRIPTION_PANEL, RGB(255, 0, 0));
		blankPanel1.LoadBitmap(SHOP_BLANK_PANEL);
		blankPanel2.LoadBitmap(SHOP_BLANK_PANEL);
		currentMoney.LoadBitmap();
		stillHave.LoadBitmap();
		itemName.LoadBitmap();
		itemCost.LoadBitmap();
		itemDescription.LoadBitmap();
		itemAmountText.LoadBitmap();
	}
	void Clerk::KeyDownListener(UINT nChar)
	{
		const char KEY_DOWN = 0x28;; // keyboard down�b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_Z = 0x5a;
		const char KEY_X = 0x58;
		if (game_bag->IsWork())
		{
			game_bag->KeyDownListener(nChar);
		}
		else
		{
			hero->StartDialog();
			if (inSelectMode)
			{
				switch (nChar)
				{
				case KEY_UP:
					CAudio::Instance()->Play(AUDIO_SELECT);
					if (selectModeOrder != 1) selectModeOrder--;

					break;

				case KEY_DOWN:
					CAudio::Instance()->Play(AUDIO_SELECT);
					if (selectModeOrder != 3) selectModeOrder++;

					break;

				case KEY_Z:
					CAudio::Instance()->Play(AUDIO_SELECT);
					if (selectModeOrder == 1)
					{
						firsttime = false;
						inBuyMode = true;
					}

					if (selectModeOrder == 2) {
						inSellMode = true;
						game_bag->Start();
						dynamic_cast<Bag*>(game_bag)->SetSellMode(money);
					}

					if (selectModeOrder == 3) End();

					selectModeOrder = 1;
					break;

				case KEY_X:
					CAudio::Instance()->Play(AUDIO_COLLISION);
					selectModeOrder = 1;
					End();
					break;
				}
			}

			if (inBuyMode)
			{
				currentMoney.SetText(to_string(*this->money));

				if (inShowText)
				{
					if (nChar == KEY_Z)
					{
						//additem
						CAudio::Instance()->Play(AUDIO_SELECT);
						itemAmount = 1;
						inShowText = false;
						inItemAmount = false;
					}
				}
				else if (inItemAmount)
				{
					switch (nChar)
					{
					case KEY_UP:
						CAudio::Instance()->Play(AUDIO_SELECT);
						itemAmount++;
						break;

					case KEY_DOWN:
						if (itemAmount > 1) {
							CAudio::Instance()->Play(AUDIO_SELECT);
							itemAmount--;
						}

						break;

					case KEY_Z:
						if ((*money) - (shopping_list[itemChooser]->GetCost() * itemAmount) < 0) {
							CAudio::Instance()->Play(AUDIO_COLLISION);
							clerkTalk.SetText("you dont have enough money");
						}
						else
						{
							CAudio::Instance()->Play(AUDIO_SELECT);
							(*money) -= (shopping_list[itemChooser]->GetCost() * itemAmount);
							dynamic_cast<Bag*>(game_bag)->AddItem(currentID, itemAmount);
							clerkTalk.SetText("thank you very much");
							inItemAmount = false;
							inShowText = true;
						}

						inItemAmount = true;
						break;

					case KEY_X:
						CAudio::Instance()->Play(AUDIO_COLLISION);
						itemAmount = 1;
						inItemAmount = false;
						break;
					}
				}
				else
				{
					switch (nChar)
					{
					case KEY_UP:
						if (itemChooser != 0)
						{
							CAudio::Instance()->Play(AUDIO_SELECT);
							itemChooser--;
						}

						break;

					case KEY_DOWN:
						if (itemChooser != shopping_list.size() - 1)
						{
							CAudio::Instance()->Play(AUDIO_SELECT);
							itemChooser++;
						}

						break;

					case KEY_Z:
						CAudio::Instance()->Play(AUDIO_SELECT);
						if (firsttime)
						{
							currentID = shopping_list[itemChooser]->GetID();
							stillHave.SetText("still have " + to_string(dynamic_cast<Bag*>(game_bag)->GetItemAmount(currentID)));
							clerkTalk.SetText("how many you want to buy");
							inItemAmount = true;
						}

						firsttime = true;
						break;

					case KEY_X:
						CAudio::Instance()->Play(AUDIO_COLLISION);
						inBuyMode = false;
						inSelectMode = true;
						break;
					}
				}
			}
		}
	}
	void Clerk::ReceiveData(CHero* hero , ActionObject* bag)
	{
		this->hero = hero;
		this->game_bag = bag;
	}
	void Clerk::InsertItem(int itemId)
	{
		CItem* new_goods = shopItemFactory.CreateItem(itemId);
		shopping_list.push_back(new_goods);
	}
	void Clerk::SetMoney(int * money)
	{
		this->money = money;
	}
	void Clerk::Start()
	{
		isWork = true;
		hero->StartDialog();
	}
	void Clerk::End()
	{
		isWork = false;
		hero->EndDialog();
	}
}
