#pragma once
#include <vector>
#include "Menu.h"
#include "CMap.h"
#include "Bag.h"
#include "CDialog.h"
#include "AtkInterface.h"

namespace game_framework {
	class AtkInterface;
	class CMap;
	class Characters;

	constexpr int HERO_X = 300;
	constexpr int HERO_Y = 220;

	enum Event {
		winMay, winYoungster, winYamao, winJK, winBadGuy, winMaster
	};

	const int STEP_SIZE = 5;
	class CHero {
	public:
		CHero();
		~CHero();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		int  GetCount();
		int  GetSpeed();
		void SetCount(int count);
		void Initialize();				// �]�w�p������l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove(CMap** m, AtkInterface &atkInterface, Characters *characters);			// ����
		void OnShow();					// �N�ϧζK��e��
		bool IsMoving();
		bool IsJumping();
		bool IsCanMove();
		void IsInvisiable(bool inv);
		void StartDialog();
		void EndDialog();
		bool InDialog();
		void SetAtkProb(int prob);
		void SetCanMove(bool flag);
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetDirection(int flag);    // �]�w�ثe�¦V����
		void SetCatchRate(int rate);
		void SetGameEvent(int gameEvent, bool flag);
		bool GetGameEvent(int gameEvent);
		int GetDirection();
		void MoveOneBlock(int direction);
		void ReceiveData(CMap* m, ActionObject* i);
		void GetItem(int itemID, int amount);
		int* GetMoney();
		ActionObject* GetBag();
		void SetXY(int nx, int ny);		// �]�w�y��
		void KeyIn(UINT nChar, Characters* characters, CMap &map);
		int GetAtkProb();
		int GetCatchRate();
		Pokemon* GetPokemon(int order);
		vector<Pokemon*>* GetPokemons();
		int GetPmNum();
		int GetAliveNum();
		void AddPokemon(Pokemon* newPm);
		void MoveAnime();
	protected:
		void ChangeMap(CMap** m);
		int JumpAnime();
		CMovingBitmap HeroFront;		// �p�����ʵe
		CMovingBitmap HeroBack;
		CMovingBitmap HeroRight;
		CMovingBitmap HeroLeft;
		CAnimation HeroMovingBack;
		CAnimation HeroMovingFront;
		CAnimation HeroMovingRight;
		CAnimation HeroMovingLeft;
		CAnimation jumpDownEffect;
		CAnimation shineGrass;
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
		bool isRunning;
		bool isJumping;
		bool invisible;
		bool onGrass;
		int speed;
		bool inBag;
		bool canMove;
		bool isMoveOneBlock;
		int count, jumpCount;
		int atkProb, catchRate;		//�J�Ǿ��v
		bool gameEvent[6];
		vector<Pokemon*> pokemons;
	private:
		CMap* gameMap;
		ActionObject* gameMenu;
		int money;
	};
}
