#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CHero.h"
#include "Pokemon.h"
#include "PokemonFactory.h"
#include "PmTreecko.h"
#include "Skill.h"
#include "SkillFactory.h"
#include "SkillImpact.h"
#include "Characters.h"
#include <iostream>
using namespace std;

namespace game_framework
{
	CHero::CHero()
	{
		// empty body
	}
	CHero::~CHero()
	{
		for (auto i : pokemons)
			delete i;
	}
	int CHero::GetX1()
	{
		return x;
	}
	int CHero::GetY1()
	{
		return y;
	}
	int CHero::GetX2()
	{
		return x + 60;
	}
	int CHero::GetY2()
	{
		return y + 80;
	}

	int CHero::GetCount()
	{
		return count;
	}

	int CHero::GetSpeed()
	{
		return speed;
	}

	void CHero::SetCount(int count)
	{
		this->count = count;
	}

	void CHero::Initialize()
	{
		const int X_POS = 300;
		const int Y_POS = 240;
		x = X_POS;
		y = Y_POS;
		count = 0;
		jumpCount = 0;
		atkProb = 10;
		catchRate = 60;
		speed = STEP_SIZE;
		money = 1000;
		canMove = false;
		isDialog = false;
		isForwardDown = true;
		isForwardLeft = isForwardRight = isForwardUp = false;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		HeroMovingBack.SetDelayCount(5);
		HeroMovingFront.SetDelayCount(5);
		HeroMovingLeft.SetDelayCount(5);
		HeroMovingRight.SetDelayCount(5);
		isRunning = false;
		isJumping = false;
		isMoveOneBlock = false;
		invisible = false;
		onGrass = false;
		PokemonFactory pmfactory;
		AddPokemon(pmfactory.CreatePokemon(treecko));
		pokemons[0]->SetLevel(8);
		pokemons[0]->SetNowExp(200);
		AddPokemon(pmfactory.CreatePokemon(jirachi));
		pokemons[1]->SetLevel(5);
		AddPokemon(pmfactory.CreatePokemon(hooh));
		pokemons[2]->SetLevel(5);
		pokemons[2]->SetRemainHP(15);
		for(int i = 0; i < 6; ++i)
			gameEvent[i] = false;
	}
	void CHero::LoadBitmap()
	{
		HeroBack.LoadBitmap(HERO_BACK, RGB(255, 0, 0));
		HeroFront.LoadBitmap(HERO_FRONT, RGB(255, 0, 0));
		HeroRight.LoadBitmap(HERO_RIGHT, RGB(255, 0, 0));
		HeroLeft.LoadBitmap(HERO_LEFT, RGB(255, 0, 0));

		HeroMovingBack.AddBitmap(HERO_BACK_ONE, RGB(255, 0, 0));
		HeroMovingBack.AddBitmap(HERO_BACK, RGB(255, 0, 0));
		HeroMovingBack.AddBitmap(HERO_BACK_TWO, RGB(255, 0, 0));
		HeroMovingBack.AddBitmap(HERO_BACK, RGB(255, 0, 0));
		HeroMovingFront.AddBitmap(HERO_FRONT_ONE, RGB(255, 0, 0));
		HeroMovingFront.AddBitmap(HERO_FRONT, RGB(255, 0, 0));
		HeroMovingFront.AddBitmap(HERO_FRONT_TWO, RGB(255, 0, 0));
		HeroMovingFront.AddBitmap(HERO_FRONT, RGB(255, 0, 0));
		HeroMovingRight.AddBitmap(HERO_RIGHT_ONE, RGB(255, 0, 0));
		HeroMovingRight.AddBitmap(HERO_RIGHT, RGB(255, 0, 0));
		HeroMovingRight.AddBitmap(HERO_RIGHT_TWO, RGB(255, 0, 0));
		HeroMovingRight.AddBitmap(HERO_RIGHT, RGB(255, 0, 0));
		HeroMovingLeft.AddBitmap(HERO_LEFT_ONE, RGB(255, 0, 0));
		HeroMovingLeft.AddBitmap(HERO_LEFT, RGB(255, 0, 0));
		HeroMovingLeft.AddBitmap(HERO_LEFT_TWO, RGB(255, 0, 0));
		HeroMovingLeft.AddBitmap(HERO_LEFT, RGB(255, 0, 0));

		jumpDownEffect.AddBitmap(IDB_SHADOW, RGB(255, 0, 0));
		jumpDownEffect.AddBitmap(IDB_SHADOW, RGB(255, 0, 0));
		jumpDownEffect.AddBitmap(IDB_SHADOW, RGB(255, 0, 0));
		jumpDownEffect.AddBitmap(IDB_JUMP_SAND1, RGB(255, 0, 0));
		jumpDownEffect.AddBitmap(IDB_JUMP_SAND2, RGB(255, 0, 0));
		jumpDownEffect.AddBitmap(IDB_JUMP_SAND3, RGB(255, 0, 0));
		jumpDownEffect.SetDelayCount(10);

		shineGrass.AddBitmap(IDB_SHINE_GRASS1, RGB(255, 0, 0));
		shineGrass.AddBitmap(IDB_SHINE_GRASS2, RGB(255, 0, 0));
		shineGrass.SetDelayCount(4);
	}
	void CHero::OnMove(CMap** m, AtkInterface &atkInterface, Characters *characters)
	{
		MoveAnime();
		int oneBlockTime = SM / speed;

		// 設定移動後的座標和碰撞的座標
		int targetx = x, targety = y;
		if (isForwardUp)
			targety = y - speed;
		else if (isForwardRight)
			targetx = x + speed;
		else if (isForwardDown)
			targety = y + speed;
		else if (isForwardLeft)
			targetx = x - speed;

		int collisionx = targetx, collisiony = targety;
		if (targetx - x > 0)
			collisionx = x + SM;
		if (targety - y > 0)
			collisiony = y + SM;

		// 移動碰撞判斷
		if ((*m)->IsEntrance(collisionx, collisiony) && count == oneBlockTime) {
			CAudio::Instance()->Play(AUDIO_ESCAPE);
			x = targetx;
			y = targety;
			ChangeMap(m);
		}
		else if (!(*m)->IsCollision(collisionx, collisiony, *this) && !characters->IsCollision(collisionx, collisiony, **m)) {
			if ((*m)->IsWarZone(collisionx, collisiony) && count == oneBlockTime)
				(*m)->ProduceEnemy(this, atkInterface);
			else if ((*m)->IsJumpLand(collisionx, collisiony, *this))
				isJumping = true;

			(*m)->SetXY((*m)->GetSX() - (x - targetx), (*m)->GetSY() - (y - targety));
			x = targetx;
			y = targety;
		}
		else if (count == 1)
			CAudio::Instance()->Play(AUDIO_COLLISION);

		// 進入草叢變色
		onGrass = (*m)->IsWarZone(collisionx, collisiony);
		if (onGrass) {
			int targetx = (!isForwardRight) ?
				(x / SM) * SM : ((x + SM) / SM) * SM;
			int targety = (!isForwardDown) ?
				(y / SM) * SM : ((y + SM) / SM) * SM;
			shineGrass.SetTopLeft(targetx - (*m)->GetSX(), targety - (*m)->GetSY());
			shineGrass.OnMove();
		}

		if (isMoveOneBlock) {
			if (count == 1) {
				isMoveOneBlock = false;
				SetMovingUp(false);
				SetMovingDown(false);
				SetMovingLeft(false);
				SetMovingRight(false);
				return;
			}
		}
	}
	void CHero::OnShow()
	{
		int targety = isJumping ? HERO_Y + JumpAnime() : HERO_Y;
		if (!invisible) {
			// 設定hero目標圖片和動畫
			CMovingBitmap *targetBitmap;
			CAnimation *targetAnimetion;
			if (isForwardUp) {
				targetBitmap = &HeroBack;
				targetAnimetion = &HeroMovingBack;
			}
			else if (isForwardRight) {
				targetBitmap = &HeroRight;
				targetAnimetion = &HeroMovingRight;
			}
			else if (isForwardDown) {
				targetBitmap = &HeroFront;
				targetAnimetion = &HeroMovingFront;
			}
			else if (isForwardLeft) {
				targetBitmap = &HeroLeft;
				targetAnimetion = &HeroMovingLeft;
			}

			// 目標圖像開始動作
			if (IsMoving() || count != 0) {
				if (isJumping) {
					jumpDownEffect.SetTopLeft(HERO_X, HERO_Y + 63);
					jumpDownEffect.OnMove();
					jumpDownEffect.OnShow();
				}
				targetAnimetion->SetTopLeft(HERO_X, targety);
				targetAnimetion->OnShow();
			}
			else {
				targetBitmap->SetTopLeft(HERO_X, targety);
				targetBitmap->ShowBitmap();
			}
		}

		// 設定草地閃爍
		if (count == 0) 
			shineGrass.Reset();
		if (onGrass && count != 0 && count != 6 && count != 12)
			shineGrass.OnShow();
	}

	bool CHero::IsMoving()
	{
		return (isMovingUp || isMovingLeft || isMovingDown || isMovingRight);
	}

	bool CHero::IsJumping()
	{
		return isJumping;
	}

	bool CHero::IsCanMove()
	{
		return canMove;
	}

	void CHero::StartDialog()
	{
		isDialog = true;
	}
	void CHero::IsInvisiable(bool inv)
	{
		this->invisible = inv;
	}
	void CHero::EndDialog()
	{
		isDialog = false;
	}

	bool CHero::InDialog()
	{
		return isDialog;
	}

	void CHero::SetAtkProb(int prob)
	{
		atkProb = prob;
	}

	void CHero::SetCanMove(bool flag)
	{
		canMove = flag;
	}

	void CHero::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}
	void CHero::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}
	void CHero::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}
	void CHero::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
	void CHero::SetDirection(int flag)
	{
		isForwardUp = (flag == 1) ? true : false;
		isForwardLeft = (flag == 2) ? true : false;
		isForwardDown = (flag == 3) ? true : false;
		isForwardRight = (flag == 4) ? true : false;
	}
	void CHero::SetCatchRate(int rate)
	{
		catchRate = rate;
	}
	void CHero::SetGameEvent(int gameEvent, bool flag)
	{
		this->gameEvent[gameEvent] = flag;
	}
	bool CHero::GetGameEvent(int gameEvent)
	{
		return this->gameEvent[gameEvent];
	}
	int CHero::GetDirection()
	{
		if (isForwardUp) return 0;
		else if (isForwardDown) return 1;
		else if (isForwardLeft) return 2;
		else return 3;
	}
	void CHero::MoveOneBlock(int direction)
	{
		if (direction == 1) {
			SetDirection(1);
			SetMovingUp(true);
		}
		else if (direction == 2) {
			SetDirection(2);
			SetMovingLeft(true);
		}
		else if (direction == 3) {
			SetDirection(3);
			SetMovingDown(true);
		}
		else {
			SetDirection(4);
			SetMovingRight(true);
		}

		isMoveOneBlock = true;
	}
	void CHero::ReceiveData(CMap* m, ActionObject* i)
	{
		gameMap = m;
		gameMenu = i;
	}
	void CHero::GetItem(int itemID, int amount)
	{
		gameMenu->RecieveItem(itemID, amount);
	}
	int * CHero::GetMoney()
	{
		return &money;
	}
	ActionObject * CHero::GetBag()
	{
		return dynamic_cast<Menu*>(gameMenu)->GetBag();
	}
	void CHero::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}

	void CHero::KeyIn(UINT nChar, Characters* characters, CMap &map)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_Z = 0x5a;
		const char KEY_X = 0x58;

		if (InDialog())
			SetCanMove(false);
		else
			SetCanMove(true);

		if (!IsMoving() && GetCount() == 0 && !InDialog()) {
			if (nChar == KEY_X) {
				if (!isRunning) {
					jumpDownEffect.SetDelayCount(2);
					speed = 2 * STEP_SIZE;
					isRunning = true;
				}
				else {
					jumpDownEffect.SetDelayCount(4);
					speed = STEP_SIZE;
					isRunning = false;
				}
			}

			if (nChar == KEY_UP) {
				SetDirection(1);
				SetMovingUp(true);
			}
			if (nChar == KEY_LEFT) {
				SetDirection(2);
				SetMovingLeft(true);
			}
			if (nChar == KEY_DOWN) {
				SetDirection(3);
				SetMovingDown(true);
			}
			if (nChar == KEY_RIGHT) {
				SetDirection(4);
				SetMovingRight(true);
			}
		}

		if (nChar == KEY_Z) {
			characters->KeyDownListener(nChar, *this, map);
			SetCanMove(false);
		}

	}

	void CHero::ChangeMap(CMap** m)
	{
		CMap* delMap = (*m);
		(*m) = (*m)->ChangeMap(x, y, this);
		delete delMap;
		this->SetXY((*m)->GetSX() + HERO_X, (*m)->GetSY() + HERO_Y + 20);
	}

	int CHero::JumpAnime()
	{
		if (jumpCount + 1 == 24 && speed == 5 || jumpCount + 1 == 12 && speed == 10) {
			jumpCount = 0;
			jumpDownEffect.Reset();
			isJumping = false;
			return 0;
		}
		jumpCount++;
		if (jumpCount <= 2 && speed == 5 || jumpCount <= 1 && speed == 10)
			return -15;
		else if (jumpCount <= 4 && speed == 5 || jumpCount <= 2 && speed == 10)
			return -22;
		else if (jumpCount <= 6 && speed == 5 || jumpCount <= 3 && speed == 10)
			return -37;
		else if (jumpCount <= 8 && speed == 5 || jumpCount <= 4 && speed == 10)
			return -44;
		else if (jumpCount <= 10 && speed == 5 || jumpCount <= 5 && speed == 10)
			return -47;
		else if (jumpCount <= 12 && speed == 5 || jumpCount <= 6 && speed == 10)
			return -37;
		else if (jumpCount <= 14 && speed == 5 || jumpCount <= 7 && speed == 10)
			return -33;
		else if (jumpCount <= 16 && speed == 5 || jumpCount <= 8 && speed == 10)
			return -26;
		else if (jumpCount <= 18 && speed == 5 || jumpCount <= 9 && speed == 10)
			return -18;
		else if (jumpCount <= 20 && speed == 5 || jumpCount <= 10 && speed == 10)
			return -3;
		else if (jumpCount <= 22 && speed == 5 || jumpCount <= 11 && speed == 10)
			return 0;
		else return 0;
	}

	int CHero::GetAtkProb()
	{
		return atkProb;
	}

	int CHero::GetCatchRate()
	{
		return catchRate;
	}

	Pokemon* CHero::GetPokemon(int order)
	{
		return pokemons[order];
	}

	vector<Pokemon*>* CHero::GetPokemons()
	{
		return &pokemons;
	}

	int CHero::GetPmNum()
	{
		return pokemons.size();
	}

	int CHero::GetAliveNum()
	{
		int aliveNum = 0;
		for (auto i : pokemons) {
			if (i->GetRemainHP() > 0)
				aliveNum++;
		}
		return aliveNum;
	}

	void CHero::AddPokemon(Pokemon* newPm)
	{
		if (GetPmNum() < 6)
			pokemons.push_back(newPm);
	}

	void CHero::MoveAnime()
	{
		HeroMovingBack.OnMove();
		HeroMovingFront.OnMove();
		HeroMovingLeft.OnMove();
		HeroMovingRight.OnMove();
	}
}
