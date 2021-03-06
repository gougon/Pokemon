#pragma once
#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"
#include "Pokemon.h"
#include "PmOprtView.h"
#include "PokemonBar.h"
#include "Bag.h"
#include "CItem.h"

using namespace std;
namespace game_framework {
	class Pokemon;

	class PokemonMenu : public ActionObject {
	public:
		PokemonMenu();
		~PokemonMenu();
		virtual void Init();
		virtual void OnShow();
		virtual void OnMove();
		virtual void LoadBitmap();
		virtual void SetTopLeft() {}
		virtual void KeyDownListener(UINT nChar);
		virtual void End();
		void ReceiveData(vector<Pokemon*>* pms);
		void ReceiveBag(ActionObject* bag);
		bool IsItemReceive();
		void ChangeOnAtk();
		void GetCurrentItemCommand(int commend, CItem* recieveItem);
		bool SuccessToUseItem();
		bool SuccessToTakeItem();
	private:
		enum pmOprtPanelSlt {
			pmOprtPanelSltView, pmOprtPanelSltChange, pmOprtPanelSltItem, pmOprtPanelSltClose
		};

		const int POKEMON_BAR_LEFT = 235;
		const int POKEMON_BAR_TOP = 30;
		const int POKEMON_BAR_FIRST_LEFT = 5;
		const int POKEMON_BAR_FIRST_TOP = 60;
		const int POKEMON_BAR_INTERVAL = 70;

		const int PANEL_LEFT = 430;
		const int PANEL_TOP = 245;
		const int CURSOR_LEFT = 445;
		const int CURSOR_TOP = 275;
		const int CURSOR_INTERVAL = 50;
		const int DESCRIPTIONPANEL_LEFT = 4;
		const int DESCRIPTIONPANEL_TOP = 385;

		void SetPmBar();
		void SetPmBarLeftTop(int order);
		CMovingBitmap selectPanel, operationPanel, cursor;
		vector<Pokemon*>* pokemons;
		PokemonBar *pokemonBar;
		PmOprtView pmOprtView;
		int order, sltPm, swapPm;
		bool isOprtPanel, isOprtSlt, isItem, isAtkChange;
		//item
		ActionObject* bag;
		CItem* recieveItem;
		CText description;
		CMovingBitmap useItemPanel, giveItemPanel, blankPanel , ItemSelectPanel;
		int itemCommand, currentItemID , selectMethod;
		bool getItem, isUseItem, isTakeItem, inShowText , showItemMethod;
	};
}
