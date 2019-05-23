#pragma once
#ifndef WEIBAIHOUSE1_1F_MAP
#define WEIBAIHOUSE1_1F_MAP

#include "CMap.h"
#include "CHero.h"
#include "CObject.h"
#include "CEvent.h"

// initial SX = 1020
// initial SY = 1080
constexpr auto WEIBAITOWN_HOUSE1_1F = 2;

namespace game_framework
{
class WeiBaiHouse1_1F_Map : public CMap
{
    public:
        WeiBaiHouse1_1F_Map(CEvent*);
        virtual void OnMove();
        virtual void InitMap();
        virtual void LoadBitmap();
        virtual void OnShow();
        virtual bool IsCollision(int x, int y);
        virtual CMap* ChangeMap(int x, int y, CHero* hero);
        virtual int ReturnMapID();
		virtual void KeyDownListener(UINT nChar, CHero &hero);
    private:
        bool inEvent;
		int dialogState;
        CDialog dialogBox;
        CObject book;
        vector<int> hitImg = { 0, 2 };
};
}

#endif