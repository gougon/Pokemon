#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "PokemonMenu.h"
#include "AtkBar.h"

namespace game_framework
{
PokemonMenu::PokemonMenu() :
    ActionObject(), order(0), sltPm(0), swapPm(0), isOprtPanel(false), isOprtSlt(false), isItem(false), inShowText(false)
{
    // empty body
}

PokemonMenu::~PokemonMenu()
{
    for (auto i : *pokemons)
    {
        delete i;
    }

    delete[] pokemonBar;
}

void PokemonMenu::Init()
{
    order = 0;
    sltPm = 0;
    swapPm = 0;
    selectPanel.SetTopLeft(0, 0);
    operationPanel.SetTopLeft(PANEL_LEFT, PANEL_TOP);
    cursor.SetTopLeft(CURSOR_LEFT, CURSOR_TOP);
    useItemPanel.SetTopLeft(DESCRIPTIONPANEL_LEFT, DESCRIPTIONPANEL_TOP);
    giveItemPanel.SetTopLeft(DESCRIPTIONPANEL_LEFT, DESCRIPTIONPANEL_TOP);
    blankPanel.SetTopLeft(DESCRIPTIONPANEL_LEFT, DESCRIPTIONPANEL_TOP);
    panel_description.SetTopLeft(DESCRIPTIONPANEL_LEFT + 20, DESCRIPTIONPANEL_TOP + 20);
    pmOprtView.Init();
    itemTransferCommend = 0;
    successTakeItem = false;
    successUseItem = false;
}

void PokemonMenu::OnShow()
{
    selectPanel.ShowBitmap();		// 顯示背景

    for (int i = 0; i < (int)pokemons->size(); ++i)  		// 顯示血條
    {
        pokemonBar[i].OnShow();
    }

    if (isOprtPanel)
    {
        if (!isOprtSlt)
        {
            operationPanel.ShowBitmap();
            cursor.ShowBitmap();
        }
        else
        {
            if (order == pmOprtPanelSltView)
            {
                pmOprtView.OnShow();
            }
        }
    }

    if (itemTransferCommend != 0)
    {
        if (itemTransferCommend == 1)
        {
            useItemPanel.ShowBitmap();
        }

        if (itemTransferCommend == 2)
        {
            giveItemPanel.ShowBitmap();
        }
    }

    if (inShowText)
    {
        blankPanel.ShowBitmap();
        panel_description.OnShow();
    }
}

void PokemonMenu::OnMove()
{
    for (int i = 0; i < (int)pokemons->size(); ++i)
    {
        if (isItem && order == pmOprtPanelSltChange)
        {
            if (i == swapPm)
            {
                pokemonBar[i].SetIsSelect(true);
            }
            else if (i != sltPm)
            {
                pokemonBar[i].SetIsSelect(false);
            }
        }
        else
        {
            if (i == sltPm)
            {
                pokemonBar[i].SetIsSelect(true);
            }
            else
            {
                pokemonBar[i].SetIsSelect(false);
            }
        }
    }

    if (isOprtPanel)
    {
        if (!isOprtSlt)
        {
            cursor.SetTopLeft(CURSOR_LEFT, CURSOR_TOP + CURSOR_INTERVAL * order);
        }
        else
        {
            switch (order)
            {
                case pmOprtPanelSltView:
                    pmOprtView.OnMove();

                    if (!pmOprtView.IsWork())
                    {
                        isOprtSlt = false;
                    }

                    break;

                case pmOprtPanelSltChange:
                    break;

                case pmOprtPanelSltItem:
                    break;

                case pmOprtPanelSltClose:
                    End();
                    break;
            }
        }
    }
}

void PokemonMenu::LoadBitmap()
{
    selectPanel.LoadBitmap(IDB_POKEMON_SELECT_PANEL, RGB(255, 0, 0));
    operationPanel.LoadBitmap(IDB_POKEMON_OPERATION_PANEL);
    cursor.LoadBitmap(BG_BACKPACK_ITEMCURSOR);
    pmOprtView.LoadBitmap();
    //
    blankPanel.LoadBitmap(BLANK_PANEL);
    useItemPanel.LoadBitmap(USEITEM_PANEL);
    giveItemPanel.LoadBitmap(GIVEITEM_PANEL);
    panel_description.LoadBitmap();
}

void PokemonMenu::KeyDownListener(UINT nChar)
{
    const char KEY_UP = 0x26;
    const char KEY_DOWN = 0x28;
    const char KEY_LEFT = 0x25;
    const char KEY_RIGHT = 0x27;
    const char KEY_Z = 0x5a;
    const char KEY_X = 0x58;
    TRACE("current pm: %d\n", sltPm);

    if (pmOprtView.IsWork())
    {
        pmOprtView.KeyDownListener(nChar);
    }
    else
    {
        TRACE("PKMENU KEYDOWN\n");

        switch (nChar)
        {
            case KEY_LEFT:

                //in item situation
                if (!isOprtPanel)
                {
                    if (sltPm != 0 && !inShowText)
                    {
                        sltPm = 0;
                    }
                }
                else
                {
                    if (isItem && order == pmOprtPanelSltChange &&
                            swapPm != 0)
                    {
                        swapPm = 0;
                    }
                }

                break;

            case KEY_RIGHT:
                if (!isOprtPanel)
                {
                    if (sltPm == 0 && (int)pokemons->size() > 1 && !inShowText)
                    {
                        sltPm = 1;
                    }
                }
                else
                {
                    if (isItem && order == pmOprtPanelSltChange &&
                            swapPm == 0 && (int)pokemons->size() > 1 )
                    {
                        swapPm = 1;
                    }
                }

                break;

            case KEY_UP:
                if (isOprtPanel)
                {
                    if (!isItem && order > 0)
                    {
                        order -= 1;
                    }
                    else if (isItem && order == pmOprtPanelSltChange &&
                             swapPm != 0 && swapPm != 1)
                    {
                        swapPm -= 1;
                    }
                }
                else
                {
                    if (sltPm != 0 && sltPm != 1 && !inShowText)
                    {
                        sltPm -= 1;
                    }
                }

                break;

            case KEY_DOWN:
                if (isOprtPanel)
                {
                    if (!isItem && order < 3)
                    {
                        order += 1;
                    }
                    else if (isItem && order == pmOprtPanelSltChange &&
                             swapPm != 0 && swapPm < (int)pokemons->size())
                    {
                        swapPm += 1;
                    }
                }
                else
                {
                    if (sltPm != 0 && sltPm < (int)pokemons->size() && !inShowText)
                    {
                        sltPm += 1;
                    }
                }

                break;

            case KEY_Z:
                if (itemTransferCommend != 0)
                {
                    if (inShowText)
                    {
                        itemTransferCommend = 0;
                        inShowText = false;
                        End();
                    }

                    //use item
                    if (itemTransferCommend == 1)
                    {
                        TRACE("use item %d\n", currentItemID);
                        successUseItem = (*pokemons)[sltPm]->UseItem(currentItemID);

                        if (successUseItem) panel_description.SetText("success to use item");
                        else panel_description.SetText("fail to use item");

                        inShowText = true;
                    }

                    if (itemTransferCommend == 2)
                    {
                        //TRACE("take item %d\n", currentItemID);
                        successTakeItem = (*pokemons)[sltPm]->TakeItem(currentItemID);

                        if (successTakeItem) panel_description.SetText("success to take item");
                        else panel_description.SetText("fail to take item");

                        inShowText = true;
                    }
                }
                else
                {
                    if (!isOprtPanel)
                    {
                        isOprtPanel = true;
                        order = 0;
                    }
                    else
                    {
                        isOprtSlt = true;

                        if (!isItem)
                        {
                            if (order == pmOprtPanelSltView)
                            {
                                pmOprtView.Start();
                                pmOprtView.ReceiveData((*pokemons)[sltPm]);
                            }
                            else if (order == pmOprtPanelSltChange)
                            {
                                swapPm = sltPm;
                                isItem = true;
                            }
                        }
                        else
                        {
                            if (order == pmOprtPanelSltChange)
                            {
                                Swap(sltPm, swapPm);
                                delete[] pokemonBar;
                                ReceiveData(pokemons);
                                isOprtPanel = false;
                                isItem = false;
                                order = 0;
                            }
                        }
                    }
                }

                break;

            case KEY_X:
                if (itemTransferCommend != 0)
                {
                    if (!inShowText) End();
                }
                else
                {
                    if (!isOprtPanel)
                    {
                        End();
                    }
                    else
                    {
                        isOprtPanel = false;
                    }
                }

                break;

            default:
                break;
        }
    }
}

void PokemonMenu::End()
{
    isWork = false;
    order = sltPm = swapPm = 0;
    isOprtPanel = isOprtSlt = false;
}

void PokemonMenu::ReceiveData(vector<Pokemon*>* pms)
{
    pokemons = pms;
    pokemonBar = new PokemonBar[pokemons->size()];
    SetPmBar();
}

void PokemonMenu::ReceiveItem(int commend,  int itemID)
{
    itemTransferCommend = commend;
    currentItemID = itemID;
}

bool PokemonMenu::SuccessToUseItem()
{
    bool tempSuccessIndex = successUseItem;

    if (tempSuccessIndex)
    {
        successUseItem = false;
        return tempSuccessIndex;
    }

    return false;
}

bool PokemonMenu::SuccessToTakeItem()
{
    bool tempSuccessIndex = successTakeItem;

    if (tempSuccessIndex)
    {
        successTakeItem = false;
        return tempSuccessIndex;
    }

    return false;
}


// private

void PokemonMenu::SetPmBar()
{
    for (int i = 0; i < (int)pokemons->size(); ++i)
    {
        pokemonBar[i].LoadBitmap();
        pokemonBar[i].GetPokemon((*pokemons)[i]);
        pokemonBar[i].SetOrder(i);
        SetPmBarLeftTop(i);
    }
}

void PokemonMenu::SetPmBarLeftTop(int order)
{
    if (order == 0)
    {
        pokemonBar[order].SetTopLeft(POKEMON_BAR_FIRST_LEFT,
                                     POKEMON_BAR_FIRST_TOP);
    }
    else
    {
        pokemonBar[order].SetTopLeft(POKEMON_BAR_LEFT,
                                     POKEMON_BAR_TOP + (order - 1) * POKEMON_BAR_INTERVAL);
    }
}

void PokemonMenu::Swap(int order1, int order2)
{
    Pokemon* temp = (*pokemons)[order1];
    (*pokemons)[order1] = (*pokemons)[order2];
    (*pokemons)[order2] = temp;
}
}