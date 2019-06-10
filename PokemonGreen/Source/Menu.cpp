#include "stdafx.h"
#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Menu.h"

namespace game_framework
{
	Menu::Menu() :
		ActionObject(), isItem(false), order(0), itemCount(7)
	{
		items.push_back(new Illustration());
		items.push_back(new PokemonMenu());
		items.push_back(new Bag());
		items.push_back(new MainMenu());
		items.push_back(new Self());
		items.push_back(new Record());
	}

	Menu::~Menu()
	{
		for (auto i : items)
			delete i;
	}

	void Menu::Init()
	{
		menuTop.SetTopLeft(MENU_LEFT, MENU_TOP);
		menuBottom.SetTopLeft(MENU_LEFT, MENU_TOP + (itemCount + 1) * MENU_INTERVAL);
		cursor.SetTopLeft(CURSOR_LEFT, CURSOR_TOP);

		for (int i = 0; i < (int)items.size(); ++i)
		{
			items[i]->Init();
		}
	}

	void Menu::OnShow()
	{
		if (!isWork)
		{
			return;
		}

		if (!isItem)
		{
			menuTop.ShowBitmap();

			for (int i = 0; i < itemCount; ++i)
			{
				menuMiddle.SetTopLeft(MENU_LEFT, MENU_TOP + MENU_INTERVAL * (i + 1));
				menuMiddle.ShowBitmap();
			}

			for (int i = 0; i < 7; i++)
			{
				switch (i)
				{
					case itemIllustration:
						showingText.SetText("illu.");
						break;

					case itemPokemonMenu:
						showingText.SetText("pokemon");
						break;

					case itemBag:
						showingText.SetText("bag");
						break;

					case itemMainMenu:
						showingText.SetText("menu");
						break;

					case itemSelf:
						showingText.SetText("self");
						break;

					case itemRecord:
						showingText.SetText("record");
						break;

					case itemClose:
						showingText.SetText("close");
						break;
				}

				showingText.SetTopLeft(CURSOR_LEFT + 20, CURSOR_TOP + MENU_INTERVAL * i - 5);
				showingText.OnShow();
			}

			menuBottom.ShowBitmap();
			cursor.ShowBitmap();
		}
		else if (order != itemClose)
		{
			items[order]->OnShow();
		}
	}

	void Menu::OnMove()
	{
		if (!isItem)
		{
			menuBottom.SetTopLeft(MENU_LEFT, MENU_TOP + (itemCount + 1) * MENU_INTERVAL);
			cursor.SetTopLeft(CURSOR_LEFT, CURSOR_TOP + MENU_INTERVAL * order);
		}
		else
		{
			if (order == itemClose)
			{
				End();
			}
			else
			{
				items[order]->OnMove();

				if (!items[order]->IsWork())
				{
					isItem = false;
				}
			}
		}
	}

	void Menu::LoadBitmap()
	{
		cursor.LoadBitmap(IDB_CURSOR, RGB(255, 0, 0));
		menuTop.LoadBitmap(IDB_MENU_TOP);
		menuMiddle.LoadBitmap(IDB_MENU_MIDDLE);
		menuBottom.LoadBitmap(IDB_MENU_BOTTOM);
		showingText.LoadBitmap();
		showingText.SetFontSize(16);

		for (int i = 0; i < (int)items.size(); ++i)
		{
			items[i]->LoadBitmap();
		}
	}

	void Menu::KeyDownListener(UINT nChar)
	{
		const char KEY_UP = 0x26;
		const char KEY_DOWN = 0x28;
		const char KEY_Z = 0x5a;
		const char KEY_X = 0x58;

		if (isItem)
		{
			items[order]->KeyDownListener(nChar);
		}
		else
		{
			switch (nChar)
			{
				case KEY_UP:
					if (order > itemIllustration) { 		// 選項向上移
						CAudio::Instance()->Play(AUDIO_SELECT);
						order -= 1;
					}
					break;
				case KEY_DOWN:
					if (order < itemClose) {  		// 選項向下移
						CAudio::Instance()->Play(AUDIO_SELECT);
						order += 1;
					}
					break;
				case KEY_Z:
					CAudio::Instance()->Play(AUDIO_SELECT);
					isItem = true;
					if (order != itemClose) {
						items[order]->Start();
						if (order == itemPokemonMenu)
						{
							dynamic_cast<PokemonMenu*>(items[order])->ReceiveData(pokemons);
							dynamic_cast<Bag*>(items[itemBag])->RecievePokemonMenu(items[order]);
							dynamic_cast<PokemonMenu*>(items[order])->ReceiveBag(items[itemBag]);
						}
						if (order == itemBag) {
							dynamic_cast<PokemonMenu*>(items[itemPokemonMenu])->ReceiveData(pokemons);
							dynamic_cast<Bag*>(items[order])->RecievePokemonMenu(items[itemPokemonMenu]);
						}
						if (order == itemSelf) {
							dynamic_cast<Self*>(items[order])->RecieveData(*money, 0);
						}
						
					}
					else 
						End();
					break;

				case KEY_X:
					CAudio::Instance()->Play(AUDIO_SELECT);
					End();		// 結束選單
					break;

				default:
					break;
			}
		}
	}

	void Menu::Start()
	{
		isWork = true;
		CAudio::Instance()->Play(AUDIO_START_MENU);
	}

	void Menu::End()
	{
		order = itemIllustration;
		isWork = false;
		isItem = false;
	}

	void Menu::RecieveItem(int itemID, int amount)
	{
		dynamic_cast<Bag*>(items[itemBag])->AddItem(itemID, amount);
	}

	void Menu::SetPokemons(vector<Pokemon*>* pms)
	{    
		pokemons = pms;
		dynamic_cast<PokemonMenu*>(items[itemPokemonMenu])->ReceiveData(pokemons);
	}

	void Menu::SetMoney(int * money)
	{
		this->money = money;
	}

	PokemonMenu *Menu::GetPokemonMenu()
	{
		return dynamic_cast<PokemonMenu*>(items[itemPokemonMenu]);
	}
	Bag * Menu::GetBag()
	{
		return dynamic_cast<Bag*>(items[itemBag]);;
	}
}