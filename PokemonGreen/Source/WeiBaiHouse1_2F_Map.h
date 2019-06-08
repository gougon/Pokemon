#pragma once
#ifndef WEIBAIHOUSE1_2F_MAP
#define WEIBAIHOUSE1_2F_MAP

#include "CMap.h"
#include "CHero.h"
#include "CEvent.h"
constexpr auto WEIBAITOWN_HOUSE1_2F = 2;

namespace game_framework
{
class WeiBaiHouse1_2F_Map : public CMap
{
    public:
        WeiBaiHouse1_2F_Map(CEvent*);
        virtual void InitMap();
        virtual void LoadBitmap();
        virtual void OnShow();
        virtual bool IsCollision(int x, int y, CHero &hero);
        virtual CMap* ChangeMap(int x, int y, CHero* hero);
    private:
        int hitImg[2] = { 0, 2 };
};
}

#endif