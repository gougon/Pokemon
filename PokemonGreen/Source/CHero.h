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
        int  GetX1();					// 擦子左上角 x 座標
        int  GetY1();					// 擦子左上角 y 座標
        int  GetX2();					// 擦子右下角 x 座標
        int  GetY2();					// 擦子右下角 y 座標
        int  GetCount();
        void SetCount(int count);
        void Initialize();				// 設定小智為初始值
        void LoadBitmap();				// 載入圖形
        void OnMove(CMap** m, AtkInterface &atkInterface);			// 移動
        void OnShow();					// 將圖形貼到畫面
        bool IsMoving();
        bool IsCanMove();
        void StartDialog();
        void EndDialog();
        bool InDialog();
        void SetCanMove(bool flag);
        void SetMovingDown(bool flag);	// 設定是否正在往下移動
        void SetMovingLeft(bool flag);	// 設定是否正在往左移動
        void SetMovingRight(bool flag); // 設定是否正在往右移動
        void SetMovingUp(bool flag);	// 設定是否正在往上移動
        void SetDirection(int flag);    // 設定目前朝向哪裡
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
        void SetXY(int nx, int ny);		// 設定座標
        void KeyIn(UINT nChar);
        int GetAtkProb();
        Pokemon* GetPokemon(int order);
        vector<Pokemon*>* GetPokemons();
        int GetPmNum();
        void AddPokemon(Pokemon* newPm);
    protected:
        void ChangeMap(CMap** m);
        CMovingBitmap HeroFront;		// 小智的動畫
        CMovingBitmap HeroBack;
        CMovingBitmap HeroRight;
        CMovingBitmap HeroLeft;
        CAnimation HeroMovingBack;
        CAnimation HeroMovingFront;
        CAnimation HeroMovingRight;
        CAnimation HeroMovingLeft;
        int x, y;					// 擦子左上角座標
        bool isMovingDown;			// 是否正在往下移動
        bool isMovingLeft;			// 是否正在往左移動
        bool isMovingRight;			// 是否正在往右移動
        bool isMovingUp;			// 是否正在往上移動
        bool isForwardDown;			// 是否面朝下
        bool isForwardLeft;			// 是否面朝左
        bool isForwardRight;		// 是否面朝右
        bool isForwardUp;			// 是否面朝上
        bool isDialog;
        //bool inMenu;
        bool inBag;
        bool canMove;
        int count;
        int atkProb;		//遇怪機率
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

