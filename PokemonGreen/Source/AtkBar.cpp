#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "AtkBar.h"

namespace game_framework {
	void AtkBar::LoadBitmap()
	{
		nameText.LoadBitmap();
		lvText.LoadBitmap();
		remainHpText.LoadBitmap();
		allHpText.LoadBitmap();

		myBar.LoadBitmap(IDB_MY_BAR, RGB(255, 0, 0));
		enemyBar.LoadBitmap(IDB_ENEMY_BAR, RGB(255, 0, 0));
		greenHP.LoadBitmap(IDB_HP_GREEN);
		yellowHP.LoadBitmap(IDB_HP_YELLOW);
		redHP.LoadBitmap(IDB_HP_RED);
		expBar.LoadBitmap(IDB_EXPBAR);
	}

	void AtkBar::Init(barType type)
	{
		this->type = type;
		switch (type)
		{
		case barTypeMy:
			myBar.SetTopLeft(MYX, MYY);
			greenHP.SetTopLeft(HP_MYX, HP_MYY);
			yellowHP.SetTopLeft(HP_MYX, HP_MYY);
			redHP.SetTopLeft(HP_MYX, HP_MYY);
			expBar.SetTopLeft(EXP_X, EXP_Y);
			break;
		case barTypeEnemy:
			enemyBar.SetTopLeft(ENEX, ENEY);
			greenHP.SetTopLeft(HP_ENEX, HP_ENEY);
			yellowHP.SetTopLeft(HP_ENEX, HP_ENEY);
			redHP.SetTopLeft(HP_ENEX, HP_ENEY);
			break;
		default:
			ASSERT(0);
			break;
		}
		greenHP.SetWidth((int)HP_LEN);
		yellowHP.SetWidth((int)HP_LEN);
		redHP.SetWidth((int)HP_LEN);
		expBar.SetWidth((int)EXP_LEN);
		x = (int)HP_LEN;
		isAddExp = true;
		rate = 1;
	}

	void AtkBar::OnMove(Pokemon *pm)
	{
		constexpr auto V = 5;
		rate = (float)pm->GetRemainHP() / (float)pm->GetHP();
		double widthhp = rate * HP_LEN;
		if(x - V >= (int)widthhp){		// 顯示血條
			if (rate > 0.5) {
				greenHP.SetWidth(x - V);
				x = greenHP.RectWidth();
			}
			else if (rate > 0.2) {
				yellowHP.SetWidth(x - V);
				x = yellowHP.RectWidth();
			}
			else {
				redHP.SetWidth(x - V);
				x = redHP.RectWidth();
			}
		}
		else {
			if (rate > 0.5) {
				greenHP.SetWidth((int)widthhp);
			}
			else if (rate > 0.2) {
				yellowHP.SetWidth((int)widthhp);
			}
			else {
				redHP.SetWidth((int)widthhp);
			}
			x = (int)widthhp;
		}
		if (type == barTypeMy) {	// 顯示exp條和血量
			remainHpText.SetText(to_string(pm->GetRemainHP()));
			double expRate = (double)pm->GetNowExp() / (double)pm->GetNeedExp();
			double widthexp = expRate * EXP_LEN;
			if (widthexp > expBar.RectWidth()) {		// 正常經驗值依照V上升
				if ((int)widthexp - expBar.RectWidth() > V) {
					expBar.SetWidth(expBar.RectWidth() + V);
					isAddExp = true;
				}
				else{
					expBar.SetWidth((int)widthexp);
					isAddExp = false;
				}
			}
			else if ((int)(widthexp + 0.5) < expBar.RectWidth()){		// 升等經驗值上升
				isAddExp = true;
				if (expBar.RectWidth() < HP_LEN - V) {
					expBar.SetWidth(expBar.RectWidth() + V);
				}
				else if(expBar.RectWidth() < HP_LEN && expBar.RectWidth() >= HP_LEN - V){
					expBar.SetWidth((int)HP_LEN);
				}
				else {
					/*pm->SetNowExp(pm->GetNowExp() - pm->GetNeedExp());
					pm->SetLevel(pm->GetLevel() + 1);*/
					
					expBar.SetWidth(0);
				}
			}
		}
	}

	void AtkBar::OnShow()
	{
		if (rate > 0.5)
			greenHP.ShowBitmap("atkBar");
		else if (rate > 0.2)
			yellowHP.ShowBitmap("atkBar");
		else
			redHP.ShowBitmap("atkBar");

		switch (type)
		{
		case barTypeMy:
			myBar.ShowBitmap();
			expBar.ShowBitmap("atkBar");
			
			break;
		case barTypeEnemy:
			enemyBar.ShowBitmap();
			break;
		default:
			ASSERT(0);
			break;
		}

		nameText.OnShow();
		lvText.OnShow();
		if (type == barTypeMy) {
			remainHpText.OnShow();
			allHpText.OnShow();
		}
	}

	void AtkBar::ReceivePm(Pokemon *pm)
	{
		double expRate = (double)pm->GetNowExp() / (double)pm->GetNeedExp();
		double widthexp = expRate * EXP_LEN;
		expBar.SetWidth((int)(widthexp + 0.5));

		nameText.SetText(pm->GetName());
		lvText.SetText(to_string(pm->GetLevel()));
		switch (type) {
		case barTypeMy:
			remainHpText.SetText(to_string(pm->GetRemainHP()));
			allHpText.SetText(to_string(pm->GetHP()));
			nameText.SetTopLeft(MY_NAME_RIGHT - nameText.GetLength() * (int)nameText.GetFontSize(), 
				MY_FIRST_ROW);
			lvText.SetTopLeft(MY_LV_LEFT, MY_FIRST_ROW);
			remainHpText.SetTopLeft(MY_RHP_RIGHT - remainHpText.GetLength() * (int)remainHpText.GetFontSize(), 
				MY_SECOND_ROW);
			allHpText.SetTopLeft(MY_HP_LEFT, MY_SECOND_ROW);
			break;
		case barTypeEnemy:
			nameText.SetTopLeft(ENE_NAME_RIGHT - nameText.GetLength() * (int)nameText.GetFontSize(),
				ENE_FIRST_ROW);
			lvText.SetTopLeft(ENE_LV_LEFT, ENE_FIRST_ROW);
			break;
		}
	}

	bool AtkBar::IsAddExp()
	{
		return isAddExp;
	}
}