#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "AtkBar.h"
#include "PokemonBar.h"

namespace game_framework {
	PokemonBar::PokemonBar() :
		isSelect(false), delay(0)
	{
		// empty body
	}

	PokemonBar::~PokemonBar()
	{
		pm = nullptr;
	}

	void PokemonBar::OnShow()
	{
		IconAnime();
		targetHp->ShowBitmap("HpBar");
		bar.ShowBitmap();
		if (isSelect) {
			barSelect.ShowBitmap();
		}
		pmIcon.ShowBitmap();
		nameText.OnShow();
		levelText.OnShow();
		remainHpText.OnShow();
		allHpText.OnShow();
	}

	void PokemonBar::LoadBitmap()
	{
		greenHp.LoadBitmap(IDB_HP_GREEN);
		yellowHp.LoadBitmap(IDB_HP_YELLOW);
		redHp.LoadBitmap(IDB_HP_RED);

		nameText.LoadBitmap();
		levelText.LoadBitmap();
		remainHpText.LoadBitmap();
		allHpText.LoadBitmap();
	}

	void PokemonBar::SetTopLeft(int left, int top)
	{
		this->left = left;
		this->top = top;

		bar.SetTopLeft(left, top);
		barSelect.SetTopLeft(left, top);
		if (order == 0) {
			targetHp->SetTopLeft(left + BLD_BAR_FIRST_LEFT, top + BLD_BAR_FIRST_TOP);
			pmIcon.SetTopLeft(left + PM1_ICON_LEFT, top + PM1_ICON_TOP);
			nameText.SetTopLeft(left + PM1_NAME_LEFT, top + PM1_NAME_TOP);
			levelText.SetTopLeft(left + PM1_LEVEL_LEFT, top + PM1_LEVEL_TOP);
			remainHpText.SetTopLeft(left + PM1_RH_LEFT, top + PM1_HP_TOP);
			allHpText.SetTopLeft(left + PM1_AH_LEFT, top + PM1_HP_TOP);
		}
		else {
			targetHp->SetTopLeft(left + BLD_BAR_LEFT, top + BLD_BAR_TOP);
			pmIcon.SetTopLeft(left + PM2_ICON_LEFT, top + PM2_ICON_TOP);
			nameText.SetTopLeft(left + PM2_NAME_LEFT, top + PM2_NAME_TOP);
			levelText.SetTopLeft(left + PM2_LEVEL_LEFT, top + PM2_LEVEL_TOP);
			remainHpText.SetTopLeft(left + PM2_RH_LEFT, top + PM2_HP_TOP);
			allHpText.SetTopLeft(left + PM2_AH_LEFT, top + PM2_HP_TOP);
		}
	}

	void PokemonBar::SetOrder(int order)
	{
		this->order = order;
		if (order == 0) {
			bar.LoadBitmap(IDB_POKEMON_BAR_FIRST_UNSELECTED, RGB(255, 0, 0));
			barSelect.LoadBitmap(IDB_POKEMON_BAR_FIRST_SELECT, RGB(255, 0, 0));
		}
		else {
			bar.LoadBitmap(IDB_POKEMON_BAR_UNSELECTED, RGB(255, 0, 0));
			barSelect.LoadBitmap(IDB_POKEMON_BAR_SELECT, RGB(255, 0, 0));
		}
		SetPmInformation();
		LoadHpLen();
	}

	void PokemonBar::GetPokemon(Pokemon *pm)
	{
		this->pm = pm;
		pmIcon = pm->GetIcon();
	}

	void PokemonBar::SetIsSelect(bool flag)
	{
		isSelect = flag;
	}

	// ptivate function

	void PokemonBar::SetPmInformation()
	{
		nameText.SetText(pm->GetName());
		levelText.SetText(to_string(pm->GetLevel()));
		remainHpText.SetText(to_string(pm->GetRemainHP()));
		allHpText.SetText(to_string(pm->GetHP()));
	}

	void PokemonBar::LoadHpLen()
	{
		double rate = (double)pm->GetRemainHP() / (double)pm->GetHP();
		if (rate > 0.5) {
			targetHp = &greenHp;
		}
		else if (rate > 0.2) {
			targetHp = &yellowHp;
		}
		else {
			targetHp = &redHp;
		}
		hpLen = (int)(rate * HP_LEN);
		targetHp->SetWidth(hpLen);
	}

	void PokemonBar::IconAnime()
	{
		if (delay++ < 10) {
			if (delay == 5) {
				pmIcon.SetTopLeft(pmIcon.Left(), pmIcon.Top() - 10);
			}
			else if (delay == 9) {
				pmIcon.SetTopLeft(pmIcon.Left(), pmIcon.Top() + 10);
			}
		}
		else {
			delay = 0;
		}
	}
}