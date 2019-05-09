#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "AtkBar.h"

namespace game_framework {
	AtkBar::AtkBar(barType rtype) :
		type(rtype)
	{
		// empty body
	}

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
		burnIcon.LoadBitmap(IDB_BURN_ICON, RGB(255, 0, 0));
	}

	void AtkBar::Init()
	{
		InitBarByType();
		InitHp();
		isAddExp = true;
		hpWidthRate = 1;
	}

	void AtkBar::OnMove()
	{
		// setting hp bar and exp bar
		hpWidthRate = pm->GetRemainHP() / (double)pm->GetHP();
		int hpWidth = (int)(hpWidthRate * HP_LEN);
		int nextHpPos = (x - V >= hpWidth) ? x - V : hpWidth;

		SetHpBarWidth(nextHpPos);

		// set exp bar and hp text
		if (type == barTypeMy) {	// 顯示exp條和血量
			remainHpText.SetText(to_string(pm->GetRemainHP()));
			double widthexp = pm->GetNowExp() / (double)pm->GetNeedExp() * EXP_LEN;
			if (widthexp > expBar.RectWidth()) {		// 正常經驗值依照V上升
				int nextExp = (int)widthexp - expBar.RectWidth();
				if (nextExp > V)
					expBar.SetWidth(expBar.RectWidth() + V);
				else
					expBar.SetWidth((int)widthexp);
				isAddExp = (nextExp > V) ? true : false;
			}
			else if ((int)(widthexp + 0.5) < expBar.RectWidth()) {		// 升等經驗值上升
				isAddExp = true;
				if (expBar.RectWidth() < HP_LEN - V)
					expBar.SetWidth(expBar.RectWidth() + V);
				else if (expBar.RectWidth() < HP_LEN && expBar.RectWidth() >= HP_LEN - V)
					expBar.SetWidth((int)HP_LEN);
				else
					expBar.SetWidth(0);
			}
			else {
				// 
			}
		}
	}

	void AtkBar::OnShow()
	{
		targetHpBar->ShowBitmap("atkBar");

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

		if (pm->GetStatus()->GetStatu() != none) {
			statuIcon->ShowBitmap();
		}
	}

	void AtkBar::SetTopLeft()
	{
		switch (type)
		{
		case barTypeMy:
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

	void AtkBar::ReceiveType(barType rtype)
	{
		type = rtype;
	}

	void AtkBar::ReceiveStatu(int statu)
	{
		// set statu icon
		if (pm->GetStatus()->GetStatu() != none) {
			statuIcon = &burnIcon;
			switch (type) {
			case barTypeMy:
				statuIcon->SetTopLeft(420, 260);
				break;
			case barTypeEnemy:
				statuIcon->SetTopLeft(50, 85);
				break;
			}
		}
	}

	void AtkBar::ReceiveData(Pokemon *rpm)
	{
		pm = rpm;

		double expRate = (double)pm->GetNowExp() / (double)pm->GetNeedExp();
		double expWidth = expRate * EXP_LEN;
		expBar.SetWidth((int)(expWidth + 0.5));

		nameText.SetText(pm->GetName());
		lvText.SetText(to_string(pm->GetLevel()));
		if (type == barTypeMy) {
			remainHpText.SetText(to_string(pm->GetRemainHP()));
			allHpText.SetText(to_string(pm->GetHP()));
		}

		SetTopLeft();
	}

	bool AtkBar::IsAddExp()
	{
		return isAddExp;
	}

	bool AtkBar::IsAnime()
	{
		return (x != (int)(hpWidthRate * HP_LEN) && x != 1);
	}

	// private

	void AtkBar::InitBarByType()
	{
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
	}

	void AtkBar::InitHp()
	{
		greenHP.SetWidth((int)HP_LEN);
		yellowHP.SetWidth((int)HP_LEN);
		redHP.SetWidth((int)HP_LEN);
		expBar.SetWidth((int)EXP_LEN);
		x = (int)HP_LEN;
	}

	void AtkBar::SetHpBarWidth(int width)
	{
		double nowHpWidthRate = width / HP_LEN;
		if (nowHpWidthRate >= 0.5)
			targetHpBar = &greenHP;
		else if (nowHpWidthRate >= 0.2)
			targetHpBar = &yellowHP;
		else
			targetHpBar = &redHP;
		targetHpBar->SetWidth(width);
		x = targetHpBar->RectWidth();
	}
}