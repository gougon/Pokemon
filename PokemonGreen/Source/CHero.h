#pragma once
#include <vector>
#include "Menu.h"
#include "CMap.h"
#include "Bag.h"
#include "CDialog.h"
#include "Pokemon.h"
#include "AtkInterface.h"
namespace game_framework
{
class AtkInterface;
class CMap;

constexpr int HERO_X = 300;
constexpr int HERO_Y = 220;

const int STEP_SIZE = 5;
class CHero
{
    public:
        CHero();
        ~CHero();
        int  GetX1();					// ���l���W�� x �y��
        int  GetY1();					// ���l���W�� y �y��
        int  GetX2();					// ���l�k�U�� x �y��
        int  GetY2();					// ���l�k�U�� y �y��
        int  GetCount();
        void SetCount(int count);
        void Initialize();				// �]�w�p������l��
        void LoadBitmap();				// ���J�ϧ�
        void OnMove(CMap** m, AtkInterface &atkInterface);			// ����
        void OnShow();					// �N�ϧζK��e��
        bool IsMoving();
        bool IsCanMove();
        void StartDialog();
        void EndDialog();
        bool InDialog();
        void SetCanMove(bool flag);
        void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
        void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
        void SetMovingRight(bool flag); // �]�w�O�_���b���k����
        void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
        void SetDirection(int flag);    // �]�w�ثe�¦V����
        int GetDirection();
        void trigger(CMap* m);
        void ReceiveData(CMap* m, ActionObject* i);
        //void OpenMenu();
        void OpenBag();					//Bag
        void CloseBag();
        void BackpackCursorMove();
        void GetItem(int, int);
        int* GetMoney();
        //
        bool IsInBag();
        void SetXY(int nx, int ny);		// �]�w�y��
        void KeyIn(UINT nChar);
        int GetAtkProb();
        Pokemon* GetPokemon(int order);
        vector<Pokemon*>* GetPokemons();
        int GetPmNum();
        void AddPokemon(Pokemon* newPm);
    protected:
        void ChangeMap(CMap** m);
        CMovingBitmap HeroFront;		// �p�����ʵe
        CMovingBitmap HeroBack;
        CMovingBitmap HeroRight;
        CMovingBitmap HeroLeft;
        CAnimation HeroMovingBack;
        CAnimation HeroMovingFront;
        CAnimation HeroMovingRight;
        CAnimation HeroMovingLeft;
        int x, y;					// ���l���W���y��
        bool isMovingDown;			// �O�_���b���U����
        bool isMovingLeft;			// �O�_���b��������
        bool isMovingRight;			// �O�_���b���k����
        bool isMovingUp;			// �O�_���b���W����
        bool isForwardDown;			// �O�_���¤U
        bool isForwardLeft;			// �O�_���¥�
        bool isForwardRight;		// �O�_���¥k
        bool isForwardUp;			// �O�_���¤W
        bool isDialog;
        //bool inMenu;
        bool inBag;
        bool canMove;
        int count;
        int atkProb;		//�J�Ǿ��v
        vector<Pokemon*> pokemons;
    private:
        //int menuFlag = 0;
        CMap* gameMap;
        ActionObject* gameMenu;
        //Bag heroBackPack;
        int money;
        int bag_flag;
        bool CheckForward(CMap** m);
        CDialog* heroDialog;
};
}

