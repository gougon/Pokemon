#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"
#include "PokemonMenu.h"
#include "CText.h"
#include "CItem.h"
#include "CDialog.h"
#include "ItemFactory.h"
#define MAXITEMAMOUNT 100
using namespace std;
namespace game_framework
{
class Bag : public ActionObject
{
    public:
        Bag();
		virtual ~Bag();
        virtual void Init();
        virtual void OnShow();
        virtual void OnMove();
        virtual void LoadBitmap();
        virtual void KeyDownListener(UINT nChar);
		virtual void SetTopLeft() {}
        void RecievePokemonMenu(ActionObject*);
		void ReceivePokemonCommend(Pokemon*, bool);
		bool PokemonSuccessTakeItem();
		bool IsPokemonReceive();
        void AddItem(int, int);
        void DropItem(int, int);
		void SetBattleMode();
        void SetSellMode(int* money);
        int GetItemAmount(int itemID);
		int SelectPokeball();
		void Start();
        void End();
    private:
		const int CAT_LOC_LEFT = 105;
		const int CAT_LOC_TOP = 27;
		const int CAT_FLAG_LEFT1 = 113;
		const int CAT_FLAG_LEFT2 = 135;
		const int CAT_FLAG_LEFT3 = 158;
		const int CAT_FLAG_LEFT4 = 178;
		const int CAT_FLAG_LEFT5 = 200;
		const int CAT_FLAG_TOP = 84;
		const int ITEM_NAME_LEFT = 340;
		const int ITEM_TOP = 50;
		const int ITEM_LEFTAMOUNT_LEFT = 560;
		const int ITEM_IMAGE_LEFT = 13;
		const int ITEM_IMAGE_TOP = 214;
		const int ITEM_DESCRIPTION_LEFT = 15;
		const int ITEM_DESCRIPTION_TOP = 300;
		const int ITEM_CHOOSER_LEFT = 310;
		const int ITEM_CHOOSER_TOP = 62;
		const int CONSOLE_PANEL_LEFT = 345;
		const int CONSOLE_PANEL_TOP = 340;
		const int ITEMAMOUNT_PANEL_LEFT = 495;
		const int ITEMAMOUNT_PANEL_TOP = 385;
		const int DROPAMOUNT_LEFT = 565;
		const int DROPAMOUNT_TOP = 410;
		const int YESNO_PANEL_LEFT = 495;
		const int YESNO_PANEL_TOP = 335;
		const int YESNOCHOOSER_LEFT = 513;
		const int YESNOCHOOSER_TOP1 = 365;
		const int YESNOCHOOSER_TOP2 = 415;
		/*sell mode SetTopLeft*/
		const int MONEY_PANEL_LEFT = 10;
		const int MONEY_PANEL_TOP = 5;
		const int CURRENTMONEY_LEFT = 122;
		const int CURRENTMONEY_TOP = 31;
		////////////////////////////
		unsigned int Get_CurrentCategorie_Size();
		CItem* SelectItem();
        int categorie_flagIndex, panel_flagIndex;
        unsigned int chooser, dropAmount, currentID;
        unsigned int item_amount[MAXITEMAMOUNT];
		/*Sell mode*/
		CMovingBitmap money_panel;
		CDialog clerkDialog;
		CText currentMoney;
		bool inSellMode, inShowText;
		int *money;
		/*battle mode*/
		int ballID;
		bool inBattle , isSelectball;
		CMovingBitmap useOnAttack_Panel;
		/*pk_menu mode*/
		Pokemon* receivePk;
		bool successReceive;
		bool isReceivePokemon;

        bool inPokemonMenu, inPanel, inItemamount, inYesno, yesnoChooser;
		vector<CItem*> items;
		CText categorie_text;
		CText item_name;
        CText item_cost;	//inSellMode
		CText drop_amount;
        CText description;
        CText item_left_amount;
        CAnimation cursor;
        CMovingBitmap backpack_panel;
		CMovingBitmap amountSelect_panel;
        CMovingBitmap yesno_panel;
        CMovingBitmap categorie_flag;
        CMovingBitmap item_selector;
        CMovingBitmap item_image;
        CMovingBitmap background_image;
		CMovingBitmap panel_selector;
        ActionObject* pk_Menu;
		ItemFactory itemFactory;
};
}
