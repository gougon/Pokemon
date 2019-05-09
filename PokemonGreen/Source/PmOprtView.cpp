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
		page(pagePmAbility), skillOrder(0), isSelectSkill(false), delay(0)
	{
		// empty body
	}

	PmOprtView::~PmOprtView()
	{
		delete pm;
		for (auto i : skills) {
			delete i;
		}
	}

	void PmOprtView::Init()
	{
		skillList.SetTopLeft(SK_LIST_LEFT, SK_LIST_TOP);
		skillSidebar.SetTopLeft(SK_LIST_LEFT, SK_SB_TOP);
		skillDesc.SetTopLeft(SK_ATTR_LEFT, SK_DESC_TOP);
		skillPower.SetTopLeft(160, SK_SB_CONTENT_TOP);
		skillHitRate.SetTopLeft(160, SK_SB_CONTENT_TOP + SK_INTERVAL);
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
			skillSidebar.ShowBitmap();
			skillList.ShowBitmap();
			if (isSelectSkill) {
				SelectSkillAnime();
				skillDesc.OnShow();
				skillPower.OnShow();
				skillHitRate.OnShow();
			}
			for (auto i : skillText) {
				i.OnShow();
			}
			break;
		default:
			break;
		}
		nameText.OnShow();
		lvText.OnShow();
		pmImage.ShowBitmap();
	}

	void PmOprtView::OnMove()
	{
		if (isSelectSkill) {
			skillSelect.SetTopLeft(SK_ATTR_LEFT, SK_TOP + (skillOrder * SK_INTERVAL));
			skillDesc.SetText(skills[skillOrder]->GetDescription());
			skillPower.SetText(to_string(skills[skillOrder]->GetPower()));
			skillHitRate.SetText(to_string(skills[skillOrder]->GetHitRate()));
			if (skillSidebar.Left() > SK_SB_LEFT) {
				OpenSkillSidebar();
			}
		}
		else {
			if (skillSidebar.Left() < SK_LIST_LEFT) {
				CloseSkillSidebar();
			}
		}
	}

	void PmOprtView::LoadBitmap()
	{
		pmAbility.LoadBitmap(IDB_PM_ABILITY);
		pmSkillPanel.LoadBitmap(IDB_PM_SKILL_PANEL);
		skillList.LoadBitmap(IDB_SKILL_LIST);
		skillSelect.LoadBitmap(IDB_SKILL_SELECT, RGB(255, 0, 0));
		skillSidebar.LoadBitmap(IDB_SKILL_SIDEBAR);
		nameText.LoadBitmap();
		lvText.LoadBitmap();
		skillDesc.LoadBitmap();
		skillPower.LoadBitmap();
		skillHitRate.LoadBitmap();
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
				CAudio::Instance()->Play(AUDIO_SELECT);
				page -= 1;
			}
			break;
		case KEY_RIGHT:
			if (page == pagePmAbility) {
				CAudio::Instance()->Play(AUDIO_SELECT);
				page += 1;
			}
			break;
		case KEY_UP:
			if (isSelectSkill && skillOrder > 0) {
				CAudio::Instance()->Play(AUDIO_SELECT);
				skillOrder -= 1;
			}
			break;
		case KEY_DOWN:
			if (isSelectSkill && skillOrder < ((int)skills.size() - 1)) {
				CAudio::Instance()->Play(AUDIO_SELECT);
				skillOrder += 1;
			}
			break;
		case KEY_Z:
			if (page == pagePmSkillPanel) {
				CAudio::Instance()->Play(AUDIO_SELECT);
				isSelectSkill = true;
			}
			break;
		case KEY_X:
			if (isSelectSkill) {
				CAudio::Instance()->Play(AUDIO_SELECT);
				isSelectSkill = false;
			}
			else {
				CAudio::Instance()->Play(AUDIO_SELECT);
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
		pmImage = pm->GetFrontImage();
		pmImage.SetTopLeft(IMG_LEFT, IMG_TOP);
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
		pm = nullptr;
		info.clear();
		skillText.clear();
		skills.clear();
		page = pagePmAbility;
		skillOrder = 0;
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
		PushText(info, to_string(pm->GetNeedExp() - pm->GetNowExp()));
		for (int i = 0; i < (int)info.size(); ++i) {
			info[i].SetTopLeft((int)(POSITION[2 * i] - info[i].GetLength() * info[i].GetFontSize()),
				POSITION[2 * i + 1]);
		}
	}

	void PmOprtView::SetSkillText()
	{
		for (int i = 0; i / 3 < (int)skills.size(); i += 3) {
			PushText(skillText, skills[i / 3]->GetAttributeText());
			PushText(skillText, skills[i / 3]->GetName());
			PushText(skillText, to_string(skills[i / 3]->GetRemainPP()) + " / " + to_string(skills[i / 3]->GetAllPP()));
			skillText[i].SetTopLeft(SK_ATTR_LEFT, SK_TOP + (i / 3 * SK_INTERVAL));
			skillText[i + 1].SetTopLeft(SK_NAME_LEFT, SK_TOP + (i / 3 * SK_INTERVAL));
			skillText[i + 2].SetTopLeft(SK_PP_LEFT, SK_TOP + (i / 3 * SK_INTERVAL));
		}
	}

	void PmOprtView::PushText(vector<CText> &v, string text)
	{
		CText tempText;
		tempText.SetText(text);
		v.push_back(tempText);
		v.back().LoadBitmap();
	}

	void PmOprtView::SelectSkillAnime()
	{
		if (delay++ < 20) {
			if (delay <= 10) {
				skillSelect.ShowBitmap();
			}
		}
		else {
			delay = 0;
		}
	}

	void PmOprtView::OpenSkillSidebar()
	{
		if (skillSidebar.Left() - 60 < SK_SB_LEFT) {
			skillSidebar.SetTopLeft(SK_SB_LEFT, SK_SB_TOP);
		}
		else {
			skillSidebar.SetTopLeft(skillSidebar.Left() - 60, SK_SB_TOP);
		}
	}

	void PmOprtView::CloseSkillSidebar()
	{
		if (skillSidebar.Left() + 30 > SK_LIST_LEFT) {
			skillSidebar.SetTopLeft(SK_LIST_LEFT, SK_SB_TOP);
		}
		else {
			skillSidebar.SetTopLeft(skillSidebar.Left() + 30, SK_SB_TOP);
		}
	}
}