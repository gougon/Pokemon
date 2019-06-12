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
		isAtkChange(false), isUseItem(false), isTakeItem(false),
		inShowText(false), showItemMethod(false), pokemonBar(nullptr)
	{
		// empty body
	}

	PokemonMenu::~PokemonMenu()
	{
		if (pokemonBar != nullptr) {
			delete[] pokemonBar;
			pokemonBar = nullptr;
		}
	}

	void PokemonMenu::Init()
	{
		order = 0;
		sltPm = 0;
		swapPm = 0;
		selectMethod = 0;
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
		ItemSelectPanel.SetTopLeft(480, 300);
		pmOprtView.Init();
	}

	void PokemonMenu::OnShow()
	{
		if (bag->IsWork() && dynamic_cast<Bag*>(bag)->IsPokemonReceive()) bag->OnShow();
		else {
			selectPanel.ShowBitmap();		// 顯示背景

			for (int i = 0; i < (int)pokemons->size(); ++i) 		// 顯示血條
				pokemonBar[i].OnShow();

			if (isOprtPanel) {
				if (!isOprtSlt) {
					operationPanel.ShowBitmap();
					cursor.ShowBitmap();
				}
				else {
					if (order == pmOprtPanelSltView) 
						pmOprtView.OnShow();
				}
			}
			if (showItemMethod) {
				ItemSelectPanel.ShowBitmap();
				cursor.ShowBitmap();
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
		
	}

	void PokemonMenu::OnMove()
	{
		if (bag->IsWork() && dynamic_cast<Bag*>(bag)->IsPokemonReceive()) 
			bag->OnMove();
		else {
			for (int i = 0; i < (int)pokemons->size(); ++i) {
				if (isItem && order == pmOprtPanelSltChange) {
					if (i == swapPm) 
						pokemonBar[i].SetIsSelect(true);
					else if (i != sltPm) 
						pokemonBar[i].SetIsSelect(false);
				}
				else {
					if (i == sltPm)
						pokemonBar[i].SetIsSelect(true);
					else 
						pokemonBar[i].SetIsSelect(false);
				}
			}
			if (isOprtPanel) {
				if (!isOprtSlt) 
					cursor.SetTopLeft(CURSOR_LEFT, CURSOR_TOP + CURSOR_INTERVAL * order);
				else {
					if (showItemMethod) 
						cursor.SetTopLeft(CURSOR_LEFT + 50, CURSOR_TOP + 60 + CURSOR_INTERVAL * selectMethod);
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
			if (dynamic_cast<Bag*>(bag)->PokemonSuccessTakeItem()) {
				ItemFactory itemFactory;
				CItem* currentItem = itemFactory.CreateItem((*pokemons)[sltPm]->GetTakeItem());
				if (currentItemID == -1) 
					description.SetText((*pokemons)[sltPm]->GetName() + " take " + currentItem->GetName() + " success");
				else {
					CItem* oldItem = itemFactory.CreateItem(currentItemID);
					description.SetText("replace " + oldItem->GetName() + " to " + currentItem->GetName());
					delete oldItem;
				}
				delete currentItem;
				inShowText = true;
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
		ItemSelectPanel.LoadBitmap(POKEMON_MENU_ITEMCHOOSE);

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
		else if(bag->IsWork() && dynamic_cast<Bag*>(bag)->IsPokemonReceive()) bag->KeyDownListener(nChar);
		else {
			switch (nChar) {
			case KEY_LEFT:
				if (!inShowText) {
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
				}
				break;
			case KEY_RIGHT:
				if (!inShowText) {
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
				}
				break;
			case KEY_UP:
				if (!inShowText) {
					if (!isOprtPanel) {
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
						if (isItem && showItemMethod && selectMethod > 0) {
							CAudio::Instance()->Play(AUDIO_SELECT);
							selectMethod -= 1;
						}
						else if (isItem && order == pmOprtPanelSltChange &&
							swapPm != 0 && swapPm != 1) {
							CAudio::Instance()->Play(AUDIO_SELECT);
							swapPm -= 1;
						}
					}
				}
				break;
			case KEY_DOWN:
				if (!inShowText) {
					if (!isOprtPanel) {
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
						if (isItem && showItemMethod && selectMethod < 2) {
							CAudio::Instance()->Play(AUDIO_SELECT);
							selectMethod += 1;
						}
						else if (isItem && order == pmOprtPanelSltChange &&
							swapPm != 0 && swapPm < (int)pokemons->size()) {
							CAudio::Instance()->Play(AUDIO_SELECT);
							swapPm += 1;
						}
					}
				}
				break;
			case KEY_Z:
				if (inShowText) {
					if (itemCommand != 0) {
						itemCommand = 0;
						recieveItem = NULL;
						End();
					}
					else inShowText = false;
				}
				if (itemCommand != 0) {
					if (itemCommand == 1) {
						isUseItem = recieveItem->Use((*pokemons)[sltPm]);
						if (isUseItem) description.SetText((*pokemons)[sltPm]->GetName() + " use " + recieveItem->GetName() + " success");
						else description.SetText("fail to use item");
						inShowText = true;
					}
					else if (itemCommand == 2) {
						isTakeItem = recieveItem->Take((*pokemons)[sltPm] , false);
						if (isTakeItem) description.SetText((*pokemons)[sltPm]->GetName() + " take " + recieveItem->GetName() + " success");
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
									TRACE("\nin pmmenu destructor, pmsize = %d\n", pokemons->size());
									delete[] pokemonBar;
									pokemonBar = nullptr;
									ReceiveData(pokemons);
									End();
								}
								else {
									CAudio::Instance()->Play(AUDIO_SELECT);
									swapPm = sltPm;
									isItem = true;
								}
							}
							else if (order == pmOprtPanelSltItem) {
								CAudio::Instance()->Play(AUDIO_SELECT);
								selectMethod = 0;
								showItemMethod = true;
								isItem = true;
							}
						}
						else {
							if (order == pmOprtPanelSltChange) {
								CAudio::Instance()->Play(AUDIO_SELECT);
								Swap((*pokemons)[sltPm], (*pokemons)[swapPm]);
								delete[] pokemonBar;
								pokemonBar = nullptr;
								ReceiveData(pokemons);
								isOprtPanel = false;
								isItem = false;
								order = 0;
								if (isAtkChange)
									End();
							}
							if (order == pmOprtPanelSltItem) {
								CAudio::Instance()->Play(AUDIO_SELECT);
								switch (selectMethod)
								{
								case 0:
									dynamic_cast<Bag*>(bag)->ReceivePokemonCommend((*pokemons)[sltPm], true);
									currentItemID = (*pokemons)[sltPm]->GetTakeItem();
									dynamic_cast<Bag*>(bag)->Start();
									break;
								case 1:
									if ((*pokemons)[sltPm]->GetTakeItem() == -1) {
										description.SetText("your pm doesn't have item");
										inShowText = true;						
									}
									else {
										dynamic_cast<Bag*>(bag)->AddItem((*pokemons)[sltPm]->GetTakeItem(), 1);
										(*pokemons)[sltPm]->SetTakeItem(-1);
										description.SetText("receive item from pm");
										inShowText = true;
									}
									break;
								case 2:
									break;
								}
								selectMethod = 0;
								showItemMethod = false;
								isOprtPanel = false;
								isItem = false;
								order = 0;
							}
						}
					}
				}
				break;
			case KEY_X:
				if (inShowText) {
					inShowText = false;
				}
				else {
					if (!isOprtPanel) {
						CAudio::Instance()->Play(AUDIO_SELECT);
						End();
					}
					else {
						if (isItem)
							isItem = false;
						CAudio::Instance()->Play(AUDIO_SELECT);
						isOprtPanel = false;
						showItemMethod = false;
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
		inShowText = isOprtPanel = isOprtSlt = isAtkChange = isItem = false;
	}

	void PokemonMenu::ReceiveData(vector<Pokemon*>* pms)
	{
		pokemons = pms;
		if (pokemonBar != nullptr) {
			delete[] pokemonBar;
			pokemonBar = nullptr;
		}
		pokemonBar = new PokemonBar[pokemons->size()];
		SetPmBar();
	}

	void PokemonMenu::ReceiveBag(ActionObject * bag)
	{
		this->bag = bag;
	}

	bool PokemonMenu::IsItemReceive()
	{
		if (itemCommand != 0) return true;
		else return false;
	}

	void PokemonMenu::ChangeOnAtk()
	{
		isAtkChange = true;
	}
	void PokemonMenu::GetCurrentItemCommand(int commend, CItem* inItem)
	{
		this->itemCommand = commend;
		this->recieveItem = inItem;
	}

	bool PokemonMenu::SuccessToUseItem()
	{
		bool tempSuccessIndex = isUseItem;

		if (tempSuccessIndex) {
			isUseItem = false;
			return tempSuccessIndex;
		}

		return false;
	}

	bool PokemonMenu::SuccessToTakeItem()
	{
		bool tempSuccessIndex = isTakeItem;

		if (tempSuccessIndex) {
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