#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"
#include "Pokemon.h"
#include "Skill.h"
#include "CText.h"

using namespace std;
namespace game_framework {
	class Pokemon;

	
	class PmOprtView : public ActionObject {
	public:
		PmOprtView();
		~PmOprtView();
		virtual void Init();
		virtual void OnShow();
		virtual void OnMove();
		virtual void LoadBitmap();
		virtual void KeyDownListener(UINT nChar);
		void ReceiveData(Pokemon *pm);
		void End();
	private:
		enum pmOprtViewPage {
			pagePmAbility, pagePmSkillPanel
		};

		enum viewInfo {
			remainHp, allHp, satk, atk, sdef, def, spd, nowExp, needExp
		};

		// RIGHT TOP
		// REMAIN_HP ALL_HP SATK ATK SDEF DEF SPD NOW_EXP NEED_EXP
		const int POSITION[18] = {380, 175, 460, 175, 615, 175, 460, 225, 
								615, 225, 460, 275, 615, 275, 610, 345, 
								610, 390};
		const int SELECT_SKILL_PADDING = 5;
		const int LV_LEFT = 50;
		const int LV_TOP = 305;
		const int NAME_LEFT = 95;
		const int NAME_TOP = 305;
		const int SK_TOP = 103;
		const int SK_ATTR_LEFT = 232;
		const int SK_NAME_LEFT = 325;
		const int SK_PP_LEFT = 510;
		const int SK_INTERVAL = 40;

		void SetCommon();
		void SetInfo();
		void SetSkillText();
		void PushText(vector<CText> &v, string text);
		CMovingBitmap pmAbility, pmSkillPanel, pmImage;
		Pokemon *pm;
		CText nameText, lvText;
		vector<CText> info, skillText;
		vector<Skill*> skills;
		int page, skillOrder;
		bool isSelectSkill;
	};
}


