#pragma once
#include "CMap.h"
#include "CHero.h"
#include "CEvent.h"
#include "Clerk.h"
constexpr auto SHOP_MAP = 2;

namespace game_framework
{
class Shop_Map : public CMap
{
    public:
        Shop_Map(CEvent*);
        virtual void OnMove();
        virtual void InitMap();
        virtual void LoadBitmap();
        virtual void OnShow();
        virtual bool IsCollision(int x, int y);
        virtual CMap* ChangeMap(int x, int y, CHero* hero);
        virtual int checkID(int x, int y, int herodirection);
		virtual void KeyDownListener(UINT nChar, CHero& hero);
    private:
		Clerk clerk;
        bool inEvent;
        vector<int> hitImg = { 0, 2 };
};
}