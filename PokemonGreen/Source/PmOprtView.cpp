#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "PmOprtView.h"

namespace game_framework {
	PmOprtView::PmOprtView() :
		page(pagePmAbility), skillOrder(0), isSelectSkill(false)
	{
		// empty body
	}

	PmOprtView::~PmOprtView()
	{
		delete pokemon;
	}

	void PmOprtView::Init()
	{
		/*REMAIN_HP_RIGHT = 380;
		REMAIN_HP_TOP = 175;
		ALL_HP_RIGHT = 460;
		ALL_HP_TOP = 175;
		SATK_RIGHT = 615;
		SATK_TOP = 175;
		ATK_RIGHT = 460;
		ATK_TOP = 225;
		SDEF_RIGHT = 615;
		SDEF_TOP = 225;
		DEF_RIGHT = 460;
		DEF_TOP = 275;
		SPD_RIGHT = 615;
		SPD_TOP = 275;
		NOW_EXP_RIGHT = 610;
		NOW_EXP_TOP = 345;
		NEED_EXP_RIGHT = 610;
		NEED_EXP_TOP = 390;			®M¥Î¦r*/
	}

	void PmOprtView::OnShow()
	{
		switch (page) {
		case pagePmAbility:
			pmAbility.ShowBitmap();
			break;
		case pagePmSkillPanel:
			pmSkillPanel.ShowBitmap();
			break;
		default:
			break;
		}
	}

	void PmOprtView::OnMove()
	{
		if (isSelectSkill) {

		}
	}

	void PmOprtView::LoadBitmap()
	{
		pmAbility.LoadBitmap(IDB_PM_ABILITY);
		pmSkillPanel.LoadBitmap(IDB_PM_SKILL_PANEL);
	}

	void PmOprtView::KeyDownListener(UINT nChar)
	{
		const char KEY_UP = 0x26;
		const char KEY_DOWN = 0x28;
		const char KEY_LEFT = 0x25;
		const char KEY_RIGHT = 0x27;
		const char KEY_Z = 0x5a;
		const char KEY_X = 0x58;

		switch (nChar) {
		case KEY_LEFT:
			if (page == pagePmSkillPanel) {
				page -= 1;
			}
			break;
		case KEY_RIGHT:
			if (page == pagePmAbility) {
				page += 1;
			}
			break;
		case KEY_UP:
			if (isSelectSkill && skillOrder > 0) {
				skillOrder -= 1;
			}
			break;
		case KEY_DOWN:
			if (isSelectSkill && skillOrder < ((int)skills.size() - 1)) {
				skillOrder += 1;
			}
			break;
		case KEY_Z:
			if (page == pagePmSkillPanel) {
				isSelectSkill = true;
			}
			break;
		case KEY_X:
			if (isSelectSkill) {
				isSelectSkill = false;
			}
			else {
				End();
			}
			break;
		default:
			break;
		}
	}

	void PmOprtView::ReceiveData(Pokemon *pm)
	{
		pokemon = pm;
		for (int i = 0; i < pm->GetSkillNum(); ++i) {
			skills.push_back(pm->GetSkill(i));
		}
	}

	void PmOprtView::End()
	{
		isWork = false;
		page = pagePmAbility;
	}
}