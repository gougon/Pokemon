#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"
#include "Pokemon.h"
#include "PmOprtView.h"

using namespace std;
namespace game_framework {
	class Pokemon;

	class PmOprtPanel : public ActionObject {
	public:
		PmOprtPanel();
		~PmOprtPanel();
		virtual void Init();
		virtual void OnShow();
		virtual void OnMove();
		virtual void LoadBitmap();
		virtual void KeyDownListener(UINT nChar);
		void ReceiveData(Pokemon *pm);
		void End();
	private:
		const int PANEL_LEFT = 430;
		const int PANEL_TOP = 245;
		const int CURSOR_LEFT = 445;
		const int CURSOR_TOP = 275;
		const int CURSOR_INTERVAL = 50;

		enum pmOprtPanelSlt {
			pmOprtPanelSltView, pmOprtPanelSltChange, pmOprtPanelSltItem, pmOprtPanelSltClose
		};

		CMovingBitmap operationPanel, cursor;
		Pokemon *pm;
		PmOprtView pmOprtView;
		int order;
		bool isItem;
	};
}

