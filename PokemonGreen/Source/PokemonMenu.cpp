#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Functions.cpp"
#include "PokemonMenu.h"
#include "AtkBar.h"

namespace game_framework {
	PokemonMenu::PokemonMenu() :
		ActionObject(), order(0), sltPm(0), swapPm(0), 
		isOprtPanel(false), isOprtSlt(false), isItem(false), 
		isAtkChange(false), isUseItem(false), isTakeItem(false) , 
		inShowText(false)
	{
		// empty body
	}

	PokemonMenu::~PokemonMenu()
	{
		for (auto i : *pokemons) 
			delete i;
		delete[] pokemonBar;
	}

	void PokemonMenu::Init()
	{
		order = 0;
		sltPm = 0;
		swapPm = 0;
		selectPanel.SetTopLeft(0, 0);

		// set item
		getItem = false;
		isUseItem = false;
		isTakeItem = false;
		inShowText = false;
		itemCommand = 0;
		currentItemID = 0;

		// set top left
		operationPanel.SetTopLeft(PANEL_LEFT, PANEL_TOP);
		cursor.SetTopLeft(CURSOR_LEFT, CURSOR_TOP);
		useItemPanel.SetTopLeft(DESCRIPTIONPANEL_LEFT, DESCRIPTIONPANEL_TOP);
		giveItemPanel.SetTopLeft(DESCRIPTIONPANEL_LEFT, DESCRIPTIONPANEL_TOP);
		blankPanel.SetTopLeft(DESCRIPTIONPANEL_LEFT, DESCRIPTIONPANEL_TOP);
		description.SetTopLeft(DESCRIPTIONPANEL_LEFT + 20, DESCRIPTIONPANEL_TOP + 20);
		pmOprtView.Init();
	}

	void PokemonMenu::OnShow()
	{
		selectPanel.ShowBitmap();		// 顯示背景

		for (int i = 0; i < (int)pokemons->size(); ++i) {		// 顯示血條
			pokemonBar[i].OnShow();
		}

		if (isOprtPanel) {
			if (!isOprtSlt) {
				operationPanel.ShowBitmap();
				cursor.ShowBitmap();
			}
			else {
				if (order == pmOprtPanelSltView) {
					pmOprtView.OnShow();
				}
			}
		}
		if (itemCommand == 1)
			useItemPanel.ShowBitmap();
		if (itemCommand == 2)
			giveItemPanel.ShowBitmap();
		if (inShowText) {
			blankPanel.ShowBitmap();
			description.OnShow();
		}
	}

	void PokemonMenu::OnMove()
	{
		for (int i = 0; i < (int)pokemons->size(); ++i) {
			if (isItem && order == pmOprtPanelSltChange) {
				if (i == swapPm) {
					pokemonBar[i].SetIsSelect(true);
				}
				else if (i != sltPm) {
					pokemonBar[i].SetIsSelect(false);
				}
			}
			else {
				if (i == sltPm) {
					pokemonBar[i].SetIsSelect(true);
				}
				else {
					pokemonBar[i].SetIsSelect(false);
				}
			}
		}
		if (isOprtPanel) {
			if (!isOprtSlt) {
				cursor.SetTopLeft(CURSOR_LEFT, CURSOR_TOP + CURSOR_INTERVAL * order);
			}
			else {
				switch (order) {
				case pmOprtPanelSltView:
					pmOprtView.OnMove();
					if (!pmOprtView.IsWork()) {
						isOprtSlt = false;
					}
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
		cursor.LoadBitmap(IDB_CURSOR);

		useItemPanel.LoadBitmap(IDB_USEITEM_PANEL);
		giveItemPanel.LoadBitmap(IDB_GIVEITEM_PANEL);
		blankPanel.LoadBitmap(IDB_BLANK_PANEL);
		description.LoadBitmap();

		pmOprtView.LoadBitmap();
	}

	void PokemonMenu::KeyDownListener(UINT nChar)
	{
		const char KEY_UP = 0x26;
		const char KEY_DOWN = 0x28;
		const char KEY_LEFT = 0x25;
		const char KEY_RIGHT = 0x27;
		const char KEY_Z = 0x5a;
		const char KEY_X = 0x58;
		
		if (pmOprtView.IsWork()) {
			pmOprtView.KeyDownListener(nChar);
		}
		else {
			switch (nChar) {
			case KEY_LEFT:
				if (!isOprtPanel) {
					if (sltPm != 0) {
						CAudio::Instance()->Play(AUDIO_SELECT);
						sltPm = 0;
					}
				}
				else {
					if (isItem && order == pmOprtPanelSltChange &&
						swapPm != 0) {
						CAudio::Instance()->Play(AUDIO_SELECT);
						swapPm = 0;
					}
				}
				break;
			case KEY_RIGHT:
				if (!isOprtPanel) {
					if (sltPm == 0 && (int)pokemons->size() > 1) {
						CAudio::Instance()->Play(AUDIO_SELECT);
						sltPm = 1;
					}
				}
				else {
					if (isItem && order == pmOprtPanelSltChange &&
						swapPm == 0 && (int)pokemons->size() > 1) {
						CAudio::Instance()->Play(AUDIO_SELECT);
						swapPm = 1;
					}
				}
				break;
			case KEY_UP:
				if(!isOprtPanel) {
					if (sltPm != 0 && sltPm != 1) {
						CAudio::Instance()->Play(AUDIO_SELECT);
						sltPm -= 1;
					}
				}
				else {
					if (!isItem && order > 0) {
						CAudio::Instance()->Play(AUDIO_SELECT);
						order -= 1;
					}
					else if (isItem && order == pmOprtPanelSltChange &&
						swapPm != 0 && swapPm != 1) {
						CAudio::Instance()->Play(AUDIO_SELECT);
						swapPm -= 1;
					}
				}
				break;
			case KEY_DOWN:
				if(!isOprtPanel) {
					if (sltPm != 0 && sltPm < (int)pokemons->size()) {
						CAudio::Instance()->Play(AUDIO_SELECT);
						sltPm += 1;
					}
				}
				else {
					if (!isItem && order < 3) {
						CAudio::Instance()->Play(AUDIO_SELECT);
						order += 1;
					}
					else if (isItem && order == pmOprtPanelSltChange &&
						swapPm != 0 && swapPm < (int)pokemons->size()) {
						CAudio::Instance()->Play(AUDIO_SELECT);
						swapPm += 1;
					}
				}
				break;
			case KEY_Z:
				if (itemCommand != 0) {
					if (inShowText) {
						itemCommand = 0;
						inShowText = false;
						End();
					}
					if (itemCommand == 1) {
						isUseItem = (*pokemons)[sltPm]->UseItem(currentItemID);
						if (isUseItem) description.SetText("success to use item");
						else description.SetText("fail to use item");
						inShowText = true;
					}
					else if (itemCommand == 2) {
						isTakeItem = (*pokemons)[sltPm]->TakeItem(currentItemID);
						if (isTakeItem) description.SetText("success to take item");
						else description.SetText("fail to take item");
						inShowText = true;
					}
				}
				else {
					if (!isOprtPanel) {
						CAudio::Instance()->Play(AUDIO_SELECT);
						isOprtPanel = true;
						order = 0;
					}
					else {
						isOprtSlt = true;
						if (!isItem) {
							if (order == pmOprtPanelSltView) {
								CAudio::Instance()->Play(AUDIO_SELECT);
								pmOprtView.Start();
								pmOprtView.ReceiveData((*pokemons)[sltPm]);
							}
							else if (order == pmOprtPanelSltChange) {
								if (isAtkChange) {
									CAudio::Instance()->Play(AUDIO_SELECT);
									Swap((*pokemons)[0], (*pokemons)[sltPm]);
									delete[] pokemonBar;
									ReceiveData(pokemons);
									End();
								}
								else {
									CAudio::Instance()->Play(AUDIO_SELECT);
									swapPm = sltPm;
									isItem = true;
								}
							}
						}
						else {
							if (order == pmOprtPanelSltChange) {
								CAudio::Instance()->Play(AUDIO_SELECT);
								Swap((*pokemons)[sltPm], (*pokemons)[swapPm]);
								delete[] pokemonBar;
								ReceiveData(pokemons);
								isOprtPanel = false;
								isItem = false;
								order = 0;
								if (isAtkChange)
									End();
							}
						}
					}
				}
				break;
			case KEY_X:
				if (!isOprtPanel) {
					CAudio::Instance()->Play(AUDIO_SELECT);
					End();
				}
				else {
					if (isItem)
						isItem = false;
					CAudio::Instance()->Play(AUDIO_SELECT);
					isOprtPanel = false;
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
		inShowText = isOprtPanel = isOprtSlt = isAtkChange = isItem = false;
	}

	void PokemonMenu::ReceiveData(vector<Pokemon*>* pms)
	{
		pokemons = pms;
		pokemonBar = new PokemonBar[pokemons->size()];
		SetPmBar();
	}

	void PokemonMenu::ChangeOnAtk()
	{
		isAtkChange = true;
	}
	void PokemonMenu::GetCurrentItemCommand(int command, int itemID)
	{
		this->itemCommand = command;
		this->currentItemID = itemID;
	}

	bool PokemonMenu::SuccessToUseItem()
	{
		bool tempSuccessIndex = isUseItem;

		if (tempSuccessIndex)
		{
			isUseItem = false;
			return tempSuccessIndex;
		}

		return false;
	}

	bool PokemonMenu::SuccessToTakeItem()
	{
		bool tempSuccessIndex = isTakeItem;

		if (tempSuccessIndex)
		{
			isTakeItem = false;
			return tempSuccessIndex;
		}

		return false;
	}
	// private

	void PokemonMenu::SetPmBar()
	{
		for (int i = 0; i < (int)pokemons->size(); ++i) {
			pokemonBar[i].LoadBitmap();
			pokemonBar[i].GetPokemon((*pokemons)[i]);
			pokemonBar[i].SetOrder(i);
			SetPmBarLeftTop(i);
		}
	}

	void PokemonMenu::SetPmBarLeftTop(int order)
	{
		if (order == 0) {
			pokemonBar[order].SetTopLeft(POKEMON_BAR_FIRST_LEFT,
				POKEMON_BAR_FIRST_TOP);
		}
		else {
			pokemonBar[order].SetTopLeft(POKEMON_BAR_LEFT,
				POKEMON_BAR_TOP + (order - 1) * POKEMON_BAR_INTERVAL);
		}
	}
}