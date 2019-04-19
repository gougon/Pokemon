#pragma once
#ifndef WEIBAIPROHOUSE_MAP
#define WEIBAIPROHOUSE_MAP

#include "CMap.h"
#include "CHero.h"
#include "CEvent.h"
constexpr auto WEIBAITOWN_PRO_HOUSE_INSIDE = 2;

namespace game_framework
{
class WeiBaiProHouse_Map : public CMap
{
    public:
        WeiBaiProHouse_Map(CEvent*);
        virtual void InitMap();
        virtual void LoadBitmap();
        virtual void OnShow();
        virtual bool IsCollision(int x, int y);
        virtual CMap* ChangeMap(int x, int y, CHero* hero);
    private:
        vector<int> hitImg = { 0, 2 };
};
}

#endif