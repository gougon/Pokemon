#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Self.h"

namespace game_framework
{
	void Self::Init()
	{
		self_image.SetTopLeft(0, 0);
		title.SetTopLeft(TITLE_LEFT, TITLE_TOP);
		title.SetText("training card");
		name.SetTopLeft(NAME_LEFT, NAME_TOP);
		name.SetText("hero");
		moneyText.SetTopLeft(NAME_LEFT, MONEY_TOP);
		illuText.SetTopLeft(NAME_LEFT, ILLU_TOP);
		money = 0;
		illuAmount = 0;
	}

	void Self::OnShow()
	{
		self_image.ShowBitmap();
		title.OnShow();
		name.OnShow();
		moneyText.OnShow();
		illuText.OnShow();
	}

	void Self::OnMove()
	{
		moneyText.SetText("money      " + to_string(money));
		illuText.SetText("illu.       " + to_string(illuAmount));
	}

	void Self::LoadBitmap()
	{
		self_image.LoadBitmap(BG_SELF);
		title.LoadBitmap();
		name.LoadBitmap();
		moneyText.LoadBitmap();
		illuText.LoadBitmap();
	}

	void Self::KeyDownListener(UINT nChar)
	{
		const char KEY_Z = 0x5a;
		const char KEY_X = 0x58;

		if (nChar == KEY_X || nChar == KEY_Z)
			End();
	}
	void Self::RecieveData(int money, int illuAmount)
	{
		this->money = money;
		this->illuAmount = illuAmount;
	}
}