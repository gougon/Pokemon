#pragma once

#include "CMap.h"
#include "CHero.h"
#include "AtkInterface.h"
#include "CObject.h"
#include "CPickableObject.h"
#include "CEvent.h"
#include "CFatguy.h"

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

namespace game_framework {
	class WeiBaiMap : public CMap {
    public:
        WeiBaiMap(CEvent*);
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
		CFatguy fatguy;
        CDialog dialogBox;
		CAnimation flower;
        CPickableObject pickable_Antidote;
        vector<int> hitImg = { 0, 3, 6 };
        vector<int> warZone = { 10 };
		vector<int> jumpLand = { 11 };
	};
}