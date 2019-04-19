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

		pmOprtPanel.Init();
	}

	void PokemonMenu::OnShow()
	{
		selectPanel.ShowBitmap();		// 顯示背景

		for (int i = 0; i < (int)pokemons.size(); ++i) {		// 顯示血條
			pokemonBar[i].OnShow();
		}

		if (pmOprtPanel.IsWork()) {
			pmOprtPanel.OnShow();
		}
	}

	void PokemonMenu::OnMove()
	{
		for (int i = 0; i < (int)pokemons.size(); ++i) {
			if (i == order) {
				pokemonBar->SetIsSelect(true);
			}
			else {
				pokemonBar->SetIsSelect(false);
			}
		}
		if (pmOprtPanel.IsWork()) {
			pmOprtPanel.OnMove();
		}
	}

	void PokemonMenu::LoadBitmap()
	{
		selectPanel.LoadBitmap(IDB_POKEMON_SELECT_PANEL, RGB(255, 0, 0));
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
				if (order != 0 && order < (int)pokemons.size()) {
					order += 1;
				}
				break;
			case KEY_Z:
				pmOprtPanel.Start();
				pmOprtPanel.ReceiveData(pokemons[order]);
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

		SetPmBar();
	}

	// private

	void PokemonMenu::SetPmBar()
	{
		for (int i = 0; i < (int)pokemons.size(); ++i) {
			pokemonBar[i].LoadBitmap();
			pokemonBar[i].GetPokemon(pokemons[i]);
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