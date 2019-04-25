#pragma once

#include "CMap.h"
#include "CHero.h"
#include "AtkInterface.h"
#include "CObject.h"
#include "CPickableObject.h"
#include "CEvent.h"
constexpr auto GREEN_GRASS = 2;
constexpr auto GREEN_TREE = 3;
constexpr auto GREEN_FLOWER = 4;
constexpr auto GRASS_LAND = 5;
constexpr auto BILLBOARD = 6;
constexpr auto WEIBAITOWN_HOUSE1 = 7;
constexpr auto WEIBAITOWN_HOUSE2 = 8;
constexpr auto WEIBAITOWN_PRO_HOUSE = 9;
constexpr auto M_GREEN_GRASS = 10;
constexpr auto JUMP_LAND = 11;
constexpr auto NORMAL_HOUSE1 = 12;

namespace game_framework
{
class WeiBaiMap : public CMap
{
    public:
        WeiBaiMap(CEvent*);
        virtual void InitMap();
        virtual void LoadBitmap();
        virtual void OnShow();
        virtual bool IsCollision(int x, int y);
        virtual bool IsWarZone(int x, int y);
        virtual void ProduceEnemy(CHero* hero, AtkInterface &atkInterface);
        virtual CMap* ChangeMap(int x, int y, CHero* hero);
        virtual void StartAtk(CHero* self, Pokemon* enemy, AtkInterface &atkInterface);
        virtual int CheckID(int, int, int);
    private:
        bool inEvent;
        CDialog dialogBox;
        CPickableObject pickable_Antidote;
        vector<int> hitImg = { 0, 3, 6, 11 };
        vector<int> warZone = { 10 };
};
}