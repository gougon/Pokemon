#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "AtkInterface.h"
#include "CHero.h"
#include "Pokemon.h"
#include "PokemonFactory.h"
#include "PmTreecko.h"
#include "Skill.h"
#include "SkillFactory.h"
#include "SkillImpact.h"
#include "CharMay.h"
#include <iostream>
using namespace std;
namespace game_framework
{
CHero::CHero()
{
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
    atkProb = 5;
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
	invisible = false;
    PokemonFactory pmfactory;
    // SkillFactory skfactory;
    Pokemon* pm = pmfactory.CreatePokemon(treecko);
    pm->SetLevel(6);
	pm->SetNowExp(120);
    // pm->AddSkill(skfactory.CreateSkill(impact, styleSelf));
	Pokemon* pm2 = pmfactory.CreatePokemon(jirachi);
	pm2->SetLevel(20);
	// pm2->AddSkill(skfactory.CreateSkill(impact, styleSelf));
	// pm2->AddSkill(skfactory.CreateSkill(leer, styleSelf));
	Pokemon* pm3 = pmfactory.CreatePokemon(hooh);
	pm3->SetLevel(5);
	pm3->SetRemainHP(15);
	// pm3->AddSkill(skfactory.CreateSkill(impact, styleSelf));
	// pm3->AddSkill(skfactory.CreateSkill(ember, styleSelf));
    AddPokemon(pm);
	AddPokemon(pm2);
	AddPokemon(pm3);
}
void CHero::LoadBitmap()
{
    HeroBack.LoadBitmap(HERO_BACK, RGB(255, 0, 0));
    HeroFront.LoadBitmap(HERO_FRONT, RGB(255, 0, 0));
    HeroRight.LoadBitmap(HERO_RIGHT, RGB(255, 0, 0));
    HeroLeft.LoadBitmap(HERO_LEFT, RGB(255, 0, 0));
    //////////////////////////////////////////////
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
    //////////////////////////////////////////////
}
void CHero::OnMove(CMap** m, AtkInterface &atkInterface, CharMay* may)
{
	MoveAnime();
	int oneBlockTime = SM / speed;
    if (isForwardLeft)
    {
        if ((*m)->IsEntrance(x - speed, y) && count == oneBlockTime)
        {
			CAudio::Instance()->Play(AUDIO_ESCAPE);
            x -= speed;
            ChangeMap(m);
        }
        else if (!(*m)->IsCollision(x - speed, y) && !may->IsCollision(x - speed, y))
        {
            if ((*m)->IsWarZone(x - speed, y) && count == oneBlockTime)
            {
				x -= speed;
                (*m)->SetXY((*m)->GetSX() - speed, (*m)->GetSY());
                (*m)->ProduceEnemy(this, atkInterface);
            }
            else
            {
                (*m)->SetXY((*m)->GetSX() - speed, (*m)->GetSY());
                x -= speed;
            }
        }
		else if (count == 1) {
			CAudio::Instance()->Play(AUDIO_COLLISION);
		}
    }

    if (isForwardRight)
    {
        if ((*m)->IsEntrance(x + SM, y) && count == oneBlockTime)
        {
			CAudio::Instance()->Play(AUDIO_ESCAPE);
            x += speed;
            ChangeMap(m);
        }
        else if (!(*m)->IsCollision(x + SM, y) && !may->IsCollision(x + SM, y))
        {
            if ((*m)->IsWarZone(x + SM, y) && count == oneBlockTime)
            {
                x += speed;
                (*m)->SetXY((*m)->GetSX() + speed, (*m)->GetSY());
                (*m)->ProduceEnemy(this, atkInterface);
            }
            else
            {
                (*m)->SetXY((*m)->GetSX() + speed, (*m)->GetSY());
                x += speed;
            }
        }
		else if (count == 1) {
			CAudio::Instance()->Play(AUDIO_COLLISION);
		}
    }

    if (isForwardUp)
    {
        if ((*m)->IsEntrance(x, y - speed) && count == oneBlockTime)
        {
			CAudio::Instance()->Play(AUDIO_ESCAPE);
            y -= speed;
            ChangeMap(m);
        }
        else if (!(*m)->IsCollision(x, y - speed) && !may->IsCollision(x, y - speed))
        {
            if ((*m)->IsWarZone(x, y - speed) && count == oneBlockTime)
            {
                y -= speed;
                (*m)->SetXY((*m)->GetSX(), (*m)->GetSY() - speed);
                (*m)->ProduceEnemy(this, atkInterface);
            }
            else
            {
                (*m)->SetXY((*m)->GetSX(), (*m)->GetSY() - speed);
                y -= speed;
            }
        }
		else if (count == 1) {
			CAudio::Instance()->Play(AUDIO_COLLISION);
		}
    }

    if (isForwardDown)
    {
        if ((*m)->IsEntrance(x, y + SM) && count == oneBlockTime)
        {
			CAudio::Instance()->Play(AUDIO_ESCAPE);
            y += speed;
            ChangeMap(m);
        }
        else if (!(*m)->IsCollision(x, y + SM) && !may->IsCollision(x, y + SM))
        {
            if ((*m)->IsWarZone(x, y + SM) && count == oneBlockTime)
            {
                y += speed;
                (*m)->SetXY((*m)->GetSX(), (*m)->GetSY() + speed);
                (*m)->ProduceEnemy(this, atkInterface);
            }
            else
            {
                (*m)->SetXY((*m)->GetSX(), (*m)->GetSY() + speed);
                y += speed;
            }
        }
		else if(count == 1){
			CAudio::Instance()->Play(AUDIO_COLLISION);
		}
    }
}
void CHero::OnShow()
{
	if (!invisible) {
		//���W��
		if (isMovingUp || count != 0 && isForwardUp)
		{
			HeroMovingBack.SetTopLeft(HERO_X, HERO_Y);
			HeroMovingBack.OnShow();
		}
		else if(isForwardUp)
		{
			HeroBack.SetTopLeft(HERO_X, HERO_Y);
			HeroBack.ShowBitmap();
		}

		//���U��
		if (isMovingDown || count != 0 && isForwardDown)
		{
			HeroMovingFront.SetTopLeft(HERO_X, HERO_Y);
			HeroMovingFront.OnShow();
		}
		else if (isForwardDown)
		{
			HeroFront.SetTopLeft(HERO_X, HERO_Y);
			HeroFront.ShowBitmap();
		}

		//������
		if (isMovingLeft || count != 0 && isForwardLeft)
		{
			HeroMovingLeft.SetTopLeft(HERO_X, HERO_Y);
			HeroMovingLeft.OnShow();
		}
		else if (isForwardLeft)
		{
			HeroLeft.SetTopLeft(HERO_X, HERO_Y);
			HeroLeft.ShowBitmap();
		}

		//���S��
		if (isMovingRight || count != 0 && isForwardRight)
		{
			HeroMovingRight.SetTopLeft(HERO_X, HERO_Y);
			HeroMovingRight.OnShow();
		}
		else if (isForwardRight)
		{
			HeroRight.SetTopLeft(HERO_X, HERO_Y);
			HeroRight.ShowBitmap();
		}
	}
}

bool CHero::IsMoving()
{
    return (isMovingUp || isMovingLeft || isMovingDown || isMovingRight);
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
int CHero::GetDirection()
{
    if (isForwardUp) return 0;
    else if (isForwardDown) return 1;
    else if (isForwardLeft) return 2;
    else return 3;
}
void CHero::ReceiveData(CMap* m, ActionObject* i)
{
    gameMap = m;
    gameMenu = i;
}
void CHero::GetItem(int itemID, int amount)
{
	gameMenu->RecieveData(itemID, amount);
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

void CHero::KeyIn(UINT nChar, CharMay* may)
{
    const char KEY_LEFT = 0x25; // keyboard左箭頭
    const char KEY_UP = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN = 0x28; // keyboard下箭頭
    const char KEY_Z = 0x5a;
	const char KEY_X = 0x58;

    if (InDialog())
        SetCanMove(false);
    else SetCanMove(true);

    if (!IsMoving() && GetCount() == 0 && !InDialog())
    {
		if (nChar == KEY_X) {
			if (!isRunning) {
				speed = 2 * STEP_SIZE;
				isRunning = true;
			}
			else {
				speed = STEP_SIZE;
				isRunning = false;
			}
		}

        if (nChar == KEY_UP)
        {
            SetDirection(1);
            SetMovingUp(true);
        }

        if (nChar == KEY_LEFT)
        {
            SetDirection(2);
            SetMovingLeft(true);
        }

        if (nChar == KEY_DOWN)
        {
            SetDirection(3);
            SetMovingDown(true);
        }

        if (nChar == KEY_RIGHT)
        {
            SetDirection(4);
            SetMovingRight(true);
        }
    }

    if (nChar == KEY_Z)
    {
		may->KeyDownListener(nChar, *this);
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

int CHero::GetAtkProb()
{
    return atkProb;
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
		if (i->GetRemainHP() > 0) {
			aliveNum++;
		}
	}
	return aliveNum;
}

void CHero::AddPokemon(Pokemon* newPm)
{
    if (GetPmNum() < 6)
    {
        pokemons.push_back(newPm);
    }
    else
    {
        // ......
    }
}

void CHero::MoveAnime()
{
	HeroMovingBack.OnMove();
	HeroMovingFront.OnMove();
	HeroMovingLeft.OnMove();
	HeroMovingRight.OnMove();
}
}
