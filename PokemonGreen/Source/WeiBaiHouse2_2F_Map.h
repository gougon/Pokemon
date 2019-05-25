#pragma once
#ifndef WEIBAIHOUSE2_2F_MAP
#define WEIBAIHOUSE2_2F_MAP

#include "CMap.h"
#include "CHero.h"
#include "CEvent.h"

constexpr auto WEIBAITOWN_HOUSE2_2F = 2;

namespace game_framework
{
class WeiBaiHouse2_2F_Map : public CMap
{
    public:
        WeiBaiHouse2_2F_Map(CEvent*);
        virtual void InitMap();
        virtual void LoadBitmap();
        virtual void OnShow();
        virtual bool IsCollision(int x, int y, CHero &hero);
        virtual CMap* ChangeMap(int x, int y, CHero* hero);
    private:
        vector<int> hitImg = { 0, 2 };
};
}

#endif
