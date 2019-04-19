#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "PmOprtView.h"
#include <typeinfo>

namespace game_framework {
	PmOprtView::PmOprtView() :
		page(pagePmAbility), skillOrder(0), isSelectSkill(false)
	{
		// empty body
	}

	PmOprtView::~PmOprtView()
	{
		delete pm;
	}

	void PmOprtView::Init()
	{
		// empty body
	}

	void PmOprtView::OnShow()
	{
		switch (page) {
		case pagePmAbility:
			pmAbility.ShowBitmap();
			for (auto i : info) {
				i.OnShow();
			}
			break;
		case pagePmSkillPanel:
			pmSkillPanel.ShowBitmap();
			for (auto i : skillText) {
				i.OnShow();
			}
			break;
		default:
			break;
		}
		nameText.OnShow();
		lvText.OnShow();
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
		nameText.LoadBitmap();
		lvText.LoadBitmap();
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
		this->pm = pm;
		for (int i = 0; i < pm->GetSkillNum(); ++i) {
			skills.push_back(pm->GetSkill(i));
		}
		SetCommon();
		SetInfo();
		SetSkillText();
	}

	void PmOprtView::End()
	{
		isWork = false;
		page = pagePmAbility;
	}

	// private function

	void PmOprtView::SetCommon()
	{
		lvText.SetText(to_string(pm->GetLevel()));
		nameText.SetText(pm->GetName());
		lvText.SetTopLeft(LV_LEFT, LV_TOP);
		nameText.SetTopLeft(NAME_LEFT, NAME_TOP);
	}

	void PmOprtView::SetInfo()
	{
		PushText(info, to_string(pm->GetRemainHP()));
		PushText(info, to_string(pm->GetHP()));
		PushText(info, to_string(pm->GetSatk()));
		PushText(info, to_string(pm->GetAtk()));
		PushText(info, to_string(pm->GetSdef()));
		PushText(info, to_string(pm->GetDef()));
		PushText(info, to_string(pm->GetSpeed()));
		PushText(info, to_string(pm->GetNowExp()));
		PushText(info, to_string(pm->GetNeedExp()));
		for (int i = 0; i < (int)info.size(); ++i) {
			info[i].SetTopLeft(POSITION[2 * i] - info[i].GetLength() * info[i].GetFontSize(), 
				POSITION[2 * i + 1]);
		}
	}

	void PmOprtView::SetSkillText()
	{
		for (int i = 0; i < (int)skills.size(); ++i) {
			PushText(skillText, skills[i]->GetAttributeText()); 
			PushText(skillText, skills[i]->GetName());
			PushText(skillText, to_string(skills[i]->GetRemainPP()) + "/" + to_string(skills[i]->GetAllPP()));
			skillText[i].SetTopLeft(SK_ATTR_LEFT, SK_TOP + (i * SK_INTERVAL));
			skillText[i + 1].SetTopLeft(SK_NAME_LEFT, SK_TOP + (i * SK_INTERVAL));
			skillText[i + 2].SetTopLeft(SK_PP_LEFT, SK_TOP + (i * SK_INTERVAL));
		}
	}

	void PmOprtView::PushText(vector<CText> &v, string text)
	{
		CText tempText;
		tempText.SetText(text);
		v.push_back(tempText);
		v.back().LoadBitmap();
	}
}