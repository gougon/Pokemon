#pragma once

#include "CMap.h"
#include "CHero.h"
#include "AtkInterface.h"
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
constexpr auto RT_SEA1 = 15;
constexpr auto RT_SEA2 = 16;
constexpr auto LAKE_102 = 17;
constexpr auto LAND_C = 18;
constexpr auto LAND_T = 19;
constexpr auto LAND_R = 20;
constexpr auto LAND_B = 21;
constexpr auto LAND_L = 22;
constexpr auto LAND_RT = 23;
constexpr auto LAND_RB = 24;
constexpr auto LAND_LT = 25;
constexpr auto LAND_LB = 26;
constexpr auto TIANYUAN_RTLAKE = 27;
constexpr auto TIANYUAN_RBHOUSE = 28; // def = 20
constexpr auto TIANYUAN_NHOUSE = 29;
constexpr auto TIANYUAN_LTHOUSE = 30;
constexpr auto TIANYUAN_LLAKE1 = 31;
constexpr auto TIANYUAN_LLAKE2 = 32;
constexpr auto TIANYUAN_LLAKE3 = 33;
constexpr auto TIANYUAN_LLAKE4 = 34;
constexpr auto TIANYUAN_GYM = 35;

namespace game_framework {
	class WeiBaiMap : public CMap {
    public:
        WeiBaiMap(CEvent*);
		~WeiBaiMap();
        virtual void InitMap();
        virtual void LoadBitmap();
        virtual void OnShow();
		virtual void ReShow(CHero &hero);
		virtual void OnMove();
        virtual bool IsCollision(int x, int y, CHero &hero);
        virtual bool IsWarZone(int x, int y);
		virtual bool IsJumpLand(int x, int y, CHero &hero);
        virtual void ProduceEnemy(CHero* hero, AtkInterface &atkInterface);
        virtual CMap* ChangeMap(int x, int y, CHero* hero);
		virtual void KeyDownListener(UINT nChar, CHero &hero);
        virtual void StartAtk(CHero* self, Pokemon* enemy, AtkInterface &atkInterface);
		void KeyDownListener(UINT nchar) { /*empty body*/ }
    private:
        bool inEvent;
		int dialogState;
        CDialog dialogBox;
		CAnimation flower, rtsea1, rtsea2, test;
        CPickableObject pickable_Antidote;
        int hitImg[14] = { 0, 3, 6, 15, 16, 17, 27, 28, 30, 31, 32, 33, 34, 35 };
        int warZone = 10;
		int jumpLand = 11;
	};
}