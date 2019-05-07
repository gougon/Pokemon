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
		virtual void SetTopLeft() {}
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
		const int POSITION[18] = { 380, 175, 460, 175, 615, 175, 460, 225,
								615, 225, 460, 275, 615, 275, 610, 345,
								610, 390 };
		const int IMG_LEFT = 35;
		const int IMG_TOP = 120;
		const int LV_LEFT = 50;
		const int LV_TOP = 285;
		const int NAME_LEFT = 95;
		const int NAME_TOP = 285;
		const int SK_LIST_LEFT = 216;
		const int SK_LIST_TOP = 64;
		const int SK_TOP = 103;
		const int SK_ATTR_LEFT = 232;
		const int SK_NAME_LEFT = 325;
		const int SK_PP_LEFT = 510;
		const int SK_INTERVAL = 40;
		const int SK_SB_WIDTH = 196;
		const int SK_SB_LEFT = 22;
		const int SK_SB_RIGHT = 219;
		const int SK_SB_TOP = 328;
		const int SK_SB_CONTENT_LEFT = 160;
		const int SK_SB_CONTENT_TOP = 365;
		const int SK_DESC_TOP = 365;

		void SetCommon();
		void SetInfo();
		void SetSkillText();
		void PushText(vector<CText> &v, string text);
		void SelectSkillAnime();
		void OpenSkillSidebar();
		void CloseSkillSidebar();
		CMovingBitmap pmAbility, pmSkillPanel, skillList, skillSelect, skillSidebar, pmImage;
		Pokemon *pm;
		CText nameText, lvText, skillDesc, skillPower, skillHitRate;
		vector<CText> info, skillText;
		vector<Skill*> skills;
		int page, skillOrder;
		bool isSelectSkill;
		int delay;
	};
}

