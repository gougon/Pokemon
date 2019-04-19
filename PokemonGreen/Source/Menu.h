#pragma once
#include <string>
#include <vector>
#include "CText.h"
#include "ActionObject.h"
#include "CHero.h"
#include "Pokemon.h"
#include "Illustration.h"
#include "PokemonMenu.h"
#include "Bag.h"
#include "MainMenu.h"
#include "Self.h"
#include "Record.h"

using namespace std;
namespace game_framework
{
class CHero;

class Menu : public ActionObject
{
    public:
        Menu();
        virtual void Init();
        virtual void OnShow();
        virtual void OnMove();
        virtual void LoadBitmap();
        virtual void KeyDownListener(UINT nChar);
        void End();
        void RecieveData(int itemID, int amount);
        void SetPokemons(vector<Pokemon*> &pms);
    private:
        const int MENU_LEFT = 474;
        const int MENU_TOP = 1;
        const int CURSOR_LEFT = 490;		// ª›ßÔ≈‹
        const int CURSOR_TOP = 60;
        const int MENU_INTERVAL = 47;

        enum MenuItem
        {
            itemIllustration,
            itemPokemonMenu,
            itemBag,
            itemMainMenu,
            itemSelf,
            itemRecord,
            itemClose
        };
        CText showingText;
        bool isItem;
        int order;
        int itemCount;
        CHero* hero;
        vector<ActionObject*> items;
        vector<Pokemon*> pokemons;
        CMovingBitmap cursor, menuTop, menuMiddle, menuBottom;
};
}