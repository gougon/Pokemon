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
		ActionObject(), order(0)
	{
		// empty body
	}

	PokemonMenu::~PokemonMenu()
	{
		for (auto i : pokemons) {
			delete i;
		}
		delete[] pokemonBar;
	}

	void PokemonMenu::Init()
	{
		order = 0;
		selectPanel.SetTopLeft(0, 0);
		pokemonBar_Unselect.SetTopLeft(POKEMON_BAR_LEFT, POKEMON_BAR_TOP);
		pokemonFirstBar_Select.SetTopLeft(POKEMON_BAR_FIRST_LEFT, POKEMON_BAR_FIRST_TOP);
		pokemonFirstBar_Unselect.SetTopLeft(POKEMON_BAR_FIRST_LEFT, POKEMON_BAR_FIRST_TOP);

		TRACE("\nInit\n");
		pmOprtPanel.Init();
	}

	void PokemonMenu::OnShow()
	{
		selectPanel.ShowBitmap();		// 顯示背景

		for (int i = 0; i < (int)pokemons.size(); ++i) {		// 顯示血條
			pokemonBar[i].OnShow();
		}

		for (int i = 1; i < (int)pokemons.size(); ++i) {		// 顯示pokemonbar_unselect
			pokemonBar_Unselect.SetTopLeft(POKEMON_BAR_LEFT, POKEMON_BAR_TOP + (POKEMON_BAR_INTERVAL * (i - 1)));
			pokemonBar_Unselect.ShowBitmap();
		}
		pokemonFirstBar_Unselect.ShowBitmap();

		if (order == 0) {		// 選第一個pm, 改變圖案
			pokemonFirstBar_Select.ShowBitmap();
		}
		else {		// 選其他的pm, 改變圖案
			pokemonBar_Select.ShowBitmap();
		}

		if (pmOprtPanel.IsWork()) {
			pmOprtPanel.OnShow();
		}
	}

	void PokemonMenu::OnMove()
	{
		pokemonBar_Select.SetTopLeft(POKEMON_BAR_LEFT, POKEMON_BAR_TOP + (POKEMON_BAR_INTERVAL * (order - 1)));
		for (int i = 1; i < (int)pokemons.size(); ++i) {
			// load pm values
		}
		if (pmOprtPanel.IsWork()) {
			pmOprtPanel.OnMove();
		}
	}

	void PokemonMenu::LoadBitmap()
	{
		selectPanel.LoadBitmap(IDB_POKEMON_SELECT_PANEL, RGB(255, 0, 0));
		pokemonBar_Select.LoadBitmap(IDB_POKEMON_BAR_SELECTED, RGB(255, 0, 0));
		pokemonBar_Unselect.LoadBitmap(IDB_POKEMON_BAR_UNSELECTED, RGB(255, 0, 0));
		pokemonFirstBar_Select.LoadBitmap(IDB_POKEMON_BAR_FIRST_SELECT, RGB(255, 0, 0));
		pokemonFirstBar_Unselect.LoadBitmap(IDB_POKEMON_BAR_FIRST_UNSELECTED, RGB(255, 0, 0));

		TRACE("\nLoad Bitmap\n");
		pmOprtPanel.LoadBitmap();
	}

	void PokemonMenu::KeyDownListener(UINT nChar)
	{
		const char KEY_UP = 0x26;
		const char KEY_DOWN = 0x28;
		const char KEY_LEFT = 0x25;
		const char KEY_RIGHT = 0x27;
		const char KEY_Z = 0x5a;
		const char KEY_X = 0x58;

		if (pmOprtPanel.IsWork()) {
			pmOprtPanel.KeyDownListener(nChar);
		}
		else {
			switch (nChar) {
			case KEY_LEFT:
				if (order != 0) {
					order = 0;
				}
				break;
			case KEY_RIGHT:
				if (order == 0 && (int)pokemons.size() > 1) {
					order = 1;
				}
				break;
			case KEY_UP:
				if (order != 0 && order != 1) {
					order -= 1;
				}
				break;
			case KEY_DOWN:
				if (order != 0 && order != 5 && order < (int)pokemons.size()) {
					order += 1;
				}
				break;
			case KEY_Z:
				pmOprtPanel.Start();
				break;
			case KEY_X:
				End();
				break;
			default:
				break;
			}
		}
	}

	void PokemonMenu::ReceiveData(vector<Pokemon*> &pms)
	{
		pokemons = pms;
		pokemonBar = new PokemonBar[pokemons.size()];
		for (int i = 0; i < (int)pokemons.size(); ++i) {
			pokemonBar[i].LoadBitmap();
			pokemonBar[i].SetAll(pokemons[i]->GetName(), pokemons[i]->GetLevel(),
				pokemons[i]->GetHP(), pokemons[i]->GetRemainHP());
			pokemonBar[i].SetOrder(i);
			pokemonBar[i].LoadPosition();
		}
	}
}