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
Menu::Menu():
    ActionObject(), isItem(false), order(0), itemCount(7)
{
    items.push_back(new Illustration());
    items.push_back(new PokemonMenu());
    items.push_back(new Bag());
    items.push_back(new MainMenu());
    items.push_back(new Self());
    items.push_back(new Record());
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
                    showingText.SetText("illus");
                    break;

                case itemPokemonMenu:
                    showingText.SetText("pm");
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
                    showingText.SetText("rc");
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
    cursor.LoadBitmap(BG_BACKPACK_ITEMCURSOR, RGB(255, 0, 0));
    menuTop.LoadBitmap(IDB_MENU_TOP);
    menuMiddle.LoadBitmap(IDB_MENU_MIDDLE);
    menuBottom.LoadBitmap(IDB_MENU_BOTTOM);
    showingText.LoadBitmap();

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
                if (order > itemIllustration)  		// 選項向上移
                {
                    order -= 1;
                }

                break;

            case KEY_DOWN:
                if (order < itemClose)  		// 選項向下移
                {
                    order += 1;
                }

                break;

            case KEY_Z:
                isItem = true;
                items[order]->Start();

                if (order == itemPokemonMenu)
                {
                    dynamic_cast<PokemonMenu*>(items[order])->ReceiveData(pokemons);
                }

                break;

            case KEY_X:
                End();		// 結束選單
                break;

            default:
                break;
        }
    }
}

void Menu::End()
{
    order = itemIllustration;
    isWork = false;
    isItem = false;
}

void Menu::RecieveData(int itemID, int amount)
{
    dynamic_cast<Bag*>(items[itemBag])->AddItem(itemID, amount);
}

void Menu::SetPokemons(vector<Pokemon*> &pms)
{
    pokemons = pms;
}
}