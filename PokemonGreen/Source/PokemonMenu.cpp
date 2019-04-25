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

namespace game_framework {
	PokemonMenu::PokemonMenu() :
		ActionObject(), order(0), sltPm(0), swapPm(0), isOprtPanel(false), isOprtSlt(false), isItem(false), isAtkChange(false)
	{
		// empty body
	}

	PokemonMenu::~PokemonMenu()
	{
		for (auto i : *pokemons) {
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
						sltPm = 0;
					}
				}
				else {
					if (isItem && order == pmOprtPanelSltChange &&
						swapPm != 0) {
						swapPm = 0;
					}
				}
				break;
			case KEY_RIGHT:
				if (!isOprtPanel) {
					if (sltPm == 0 && (int)pokemons->size() > 1) {
						sltPm = 1;
					}
				}
				else {
					if (isItem && order == pmOprtPanelSltChange &&
						swapPm == 0 && (int)pokemons->size() > 1) {
						swapPm = 1;
					}
				}
				break;
			case KEY_UP:
				if (isOprtPanel) {
					if (!isItem && order > 0) {
						order -= 1;
					}
					else if (isItem && order == pmOprtPanelSltChange &&
						swapPm != 0 && swapPm != 1) {
						swapPm -= 1;
					}
				}
				else {
					if (sltPm != 0 && sltPm != 1) {
						sltPm -= 1;
					}
				}
				break;
			case KEY_DOWN:
				if (isOprtPanel) {
					if (!isItem && order < 3) {
						order += 1;
					}
					else if (isItem && order == pmOprtPanelSltChange &&
						swapPm != 0 && swapPm < (int)pokemons->size()) {
						swapPm += 1;
					}
				}
				else {
					if (sltPm != 0 && sltPm < (int)pokemons->size()) {
						sltPm += 1;
					}
				}
				break;
			case KEY_Z:
				if (!isOprtPanel) {
					isOprtPanel = true;
					order = 0;
				}
				else {
					isOprtSlt = true;
					if (!isItem) {
						if (order == pmOprtPanelSltView) {
							pmOprtView.Start();
							pmOprtView.ReceiveData((*pokemons)[sltPm]);
						}
						else if (order == pmOprtPanelSltChange) {
							if (isAtkChange) {
								Swap(0, sltPm);
								delete[] pokemonBar;
								ReceiveData(pokemons);
								End();
							}
							else {
								swapPm = sltPm;
								isItem = true;
							}
						}
					}
					else {
						if (order == pmOprtPanelSltChange) {
							Swap(sltPm, swapPm);
							delete[] pokemonBar;
							ReceiveData(pokemons);
							isOprtPanel = false;
							isItem = false;
							order = 0;
							if (isAtkChange) {
								End();
							}
						}
					}
				}
				break;
			case KEY_X:
				if (!isOprtPanel) {
					End();
				}
				else {
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
		isOprtPanel = isOprtSlt = isAtkChange = isItem = false;
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

	void PokemonMenu::Swap(int order1, int order2)
	{
		Pokemon *temp = (*pokemons)[order1];
		(*pokemons)[order1] = (*pokemons)[order2];
		(*pokemons)[order2] = temp;
	}
}