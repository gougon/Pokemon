#pragma once
#include "CMap.h"
#include "CHero.h"
#include "CEvent.h"
#include "Clerk.h"

namespace game_framework {
	class Douchi_Shop_Map : public CMap {
	public:
	    Douchi_Shop_Map(CEvent*);
	    virtual void OnMove();
	    virtual void InitMap();
	    virtual void LoadBitmap();
	    virtual void OnShow();
	    virtual bool IsCollision(int x, int y, CHero &hero);
	    virtual CMap* ChangeMap(int x, int y, CHero* hero);
	    virtual int checkID(int x, int y, int herodirection);
		virtual void KeyDownListener(UINT nChar, CHero& hero);
	private:
		Clerk clerk;
	    bool inEvent;
	    int hitImg[2] = { 0, 2 };
	};
}