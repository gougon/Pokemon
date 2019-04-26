#pragma once
#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"
#include "Pokemon.h"
#include "PmOprtView.h"
#include "PokemonBar.h"
#include "CText.h"

using namespace std;
namespace game_framework
{
class Pokemon;

<<<<<<< HEAD
class PokemonMenu : public ActionObject
{
    public:
        PokemonMenu();
        ~PokemonMenu();
        virtual void Init();
        virtual void OnShow();
        virtual void OnMove();
        virtual void LoadBitmap();
        virtual void KeyDownListener(UINT nChar);
        virtual void End();
        void ReceiveData(vector<Pokemon*>* pms);
        //item function
        void ReceiveItem(int commend, int itemID);
        bool SuccessToUseItem();
        bool SuccessToTakeItem();
    private:
        enum pmOprtPanelSlt
        {
            pmOprtPanelSltView, pmOprtPanelSltChange, pmOprtPanelSltItem, pmOprtPanelSltClose
        };
=======
	class PokemonMenu : public ActionObject {
	public:
		PokemonMenu();
		~PokemonMenu();
		virtual void Init();
		virtual void OnShow();
		virtual void OnMove();
		virtual void LoadBitmap();
		virtual void KeyDownListener(UINT nChar);
		virtual void End();
		void ReceiveData(vector<Pokemon*>* pms);
		void ChangeOnAtk();
	private:
		enum pmOprtPanelSlt {
			pmOprtPanelSltView, pmOprtPanelSltChange, pmOprtPanelSltItem, pmOprtPanelSltClose
		};
>>>>>>> 9c1c6bf5c624e9a0e003821a8ec7d41fcb3499b7

        const int POKEMON_BAR_LEFT = 235;
        const int POKEMON_BAR_TOP = 30;
        const int POKEMON_BAR_FIRST_LEFT = 5;
        const int POKEMON_BAR_FIRST_TOP = 60;
        const int POKEMON_BAR_INTERVAL = 70;

        const int PANEL_LEFT = 430;
        const int PANEL_TOP = 245;
        const int CURSOR_LEFT = 445;
        const int CURSOR_TOP = 275;
        const int DESCRIPTIONPANEL_LEFT = 4;
        const int DESCRIPTIONPANEL_TOP = 385;
        const int CURSOR_INTERVAL = 50;

<<<<<<< HEAD
        void SetPmBar();
        void SetPmBarLeftTop(int order);
        void Swap(int order1, int order2);
        CMovingBitmap blankPanel;
        CMovingBitmap selectPanel, operationPanel, cursor;
        vector<Pokemon*>* pokemons;
        PokemonBar* pokemonBar;
        PmOprtView pmOprtView;
        // PmOprtPanel pmOprtPanel;
        int order, sltPm, swapPm;
        bool isOprtPanel, isOprtSlt, isItem;
        // itemcommend
        CText panel_description;
        CMovingBitmap useItemPanel, giveItemPanel;
        bool successUseItem, successTakeItem, inShowText;
        int currentItemID;
        int itemTransferCommend;
};
=======
		void SetPmBar();
		void SetPmBarLeftTop(int order);
		void Swap(int order1, int order2);
		CMovingBitmap selectPanel, operationPanel, cursor;
		vector<Pokemon*>* pokemons;
		PokemonBar *pokemonBar;
		PmOprtView pmOprtView;
		int order, sltPm, swapPm;
		bool isOprtPanel, isOprtSlt, isItem, isAtkChange;
	};
>>>>>>> 9c1c6bf5c624e9a0e003821a8ec7d41fcb3499b7
}
