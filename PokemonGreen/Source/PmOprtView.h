#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"
#include "Pokemon.h"
#include "Skill.h"

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

		const int REMAIN_HP_RIGHT = 380;
		const int REMAIN_HP_TOP = 175;
		const int ALL_HP_RIGHT = 460;
		const int ALL_HP_TOP = 175;
		const int SATK_RIGHT = 615;
		const int SATK_TOP = 175;
		const int ATK_RIGHT = 460;
		const int ATK_TOP = 225;
		const int SDEF_RIGHT = 615;
		const int SDEF_TOP = 225;
		const int DEF_RIGHT = 460;
		const int DEF_TOP = 275;
		const int SPD_RIGHT = 615;
		const int SPD_TOP = 275;
		const int NOW_EXP_RIGHT = 610;
		const int NOW_EXP_TOP = 345;
		const int NEED_EXP_RIGHT = 610;
		const int NEED_EXP_TOP = 390;
		const int SELECT_SKILL_PADDING = 5;

		CMovingBitmap pmAbility, pmSkillPanel;
		Pokemon *pokemon;
		vector<Skill*> skills;
		int page, skillOrder;
		bool isSelectSkill;
	};
}


