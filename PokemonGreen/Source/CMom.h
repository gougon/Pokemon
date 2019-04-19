#pragma once
#include "CCharacter.h"
namespace game_framework
{
class CMom : public CCharacter
{
    public:
        CMom();
        void SetXY(int, int);
        virtual void OnMove();
        virtual int GetX();
        virtual int GetY();
        virtual void Initialize();
        virtual void LoadBitmap();
        virtual void OnShow(int, int);
        virtual void Talk(int);
        virtual int GetVer();
    private:
        void SetDirection(int);
        CMovingBitmap* character_scene;
        CDialog momdialog;
        int cx, cy;
        int step = 0;
        int var;
        bool isForwardDown;			// 是否面朝下
        bool isForwardLeft;			// 是否面朝左
        bool isForwardRight;		// 是否面朝右
        bool isForwardUp;		 	// 是否面朝上
        bool canMoving;
        bool isBusy;
};
}