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
        bool isForwardDown;			// �O�_���¤U
        bool isForwardLeft;			// �O�_���¥�
        bool isForwardRight;		// �O�_���¥k
        bool isForwardUp;		 	// �O�_���¤W
        bool canMoving;
        bool isBusy;
};
}