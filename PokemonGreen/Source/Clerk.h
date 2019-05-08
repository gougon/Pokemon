#pragma once
#pragma once
#include <string>
#include <vector>
#include "CHero.h"
#include "ActionObject.h"
#include "Bag.h"
#include "CDialog.h"

using namespace std;
namespace game_framework
{
	class Clerk : public ActionObject
	{
	public:
		Clerk();
		~Clerk();
		virtual void Init();
		virtual void OnShow();
		virtual void OnMove();
		virtual void LoadBitmap();
		virtual void KeyDownListener(UINT nChar);
		void ReceiveData(CHero* hero, ActionObject* bag);
		void InsertItem(int itemId);
		void SetMoney(int* money);
		void Start();
		void End();
	private:
		CHero* hero;
		ActionObject* game_bag;
		CDialog clerkTalk;
		const int MODE_SELECT_LEFT = 18;
		const int MODE_SELECT_TOP = 3;
		const int MODE_SELECT_CURSOR_LEFT = 33;
		const int MODE_SELECT_CURSOR_TOP = 33;
		const int MONEY_PANEL_LEFT = 10;
		const int MONEY_PANEL_TOP = 5;
		const int CURRENTMONEY_LEFT = 122;
		const int CURRENTMONEY_TOP = 31;
		const int IMAGE_PANEL_LEFT = 15;
		const int IMAGE_PANEL_TOP = 207;
		const int DESCRIPTION_PANEL_LEFT = 20;
		const int DESCRIPTION_PANEL_TOP = 297;
		const int SHOPPINGLIST_LEFT = 294;
		const int SHOPPINGLIST_TOP = 5;
		CMovingBitmap tradeModeSelectPanel;
		CMovingBitmap moneyPanel, shoppingPanel, itemImagePanel, itemDescriptionPanel, blankPanel1, blankPanel2;
		CMovingBitmap itemSelecter;
		CText currentMoney, itemName, itemCost, itemDescription, itemAmountText, stillHave;
		vector<CItem*> shopping_list;
		bool inBuyMode, inSellMode, inSelectMode, inItemAmount, inShowText, firsttime;
		int item_counter, selectModeOrder, itemChooser, currentID, itemAmount;
		int* money;
	};
}