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
    atkProb = 1;
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
    inBag = false;
    bag_flag = 3;
    PokemonFactory pmfactory;
    SkillFactory skfactory;
    Pokemon* pm = pmfactory.CreatePokemon(treecko);
    pm->SetLevel(6);
    pm->SetNowExp(120);
    pm->SetRemainHP(15);
    pm->AddSkill(skfactory.CreateSkill(impact, styleSelf));
    Pokemon* pm2 = pmfactory.CreatePokemon(treecko, "second");
    pm2->SetLevel(20);
    pm2->AddSkill(skfactory.CreateSkill(impact, styleSelf));
    AddPokemon(pm);
    AddPokemon(pm2);
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
    //heroBackPack.LoadBitmap();
}
void CHero::OnMove(CMap** m, AtkInterface &atkInterface)
{
    HeroMovingBack.OnMove();
    HeroMovingFront.OnMove();
    HeroMovingLeft.OnMove();
    HeroMovingRight.OnMove();

    if (isForwardLeft)
    {
        if ((*m)->IsEntrance(x - STEP_SIZE, y) && count == 12)
        {
            x -= STEP_SIZE;
            ChangeMap(m);
        }
        else if (!(*m)->IsCollision(x - STEP_SIZE, y))
        {
            if ((*m)->IsWarZone(x - STEP_SIZE, y) && count == 12)
            {
                (*m)->SetXY((*m)->GetSX() - STEP_SIZE, (*m)->GetSY());
                (*m)->ProduceEnemy(this, atkInterface);
            }
            else
            {
                (*m)->SetXY((*m)->GetSX() - STEP_SIZE, (*m)->GetSY());
                x -= STEP_SIZE;
            }
        }
    }

    if (isForwardRight)
    {
        if ((*m)->IsEntrance(x + SM, y) && count == 12)
        {
            x += STEP_SIZE;
            ChangeMap(m);
        }
        else if (!(*m)->IsCollision(x + SM, y))
        {
            if ((*m)->IsWarZone(x + SM, y) && count == 12)
            {
                x += STEP_SIZE;
                (*m)->SetXY((*m)->GetSX() + STEP_SIZE, (*m)->GetSY());
                (*m)->ProduceEnemy(this, atkInterface);
            }
            else
            {
                (*m)->SetXY((*m)->GetSX() + STEP_SIZE, (*m)->GetSY());
                x += STEP_SIZE;
            }
        }
    }

    if (isForwardUp)
    {
        if ((*m)->IsEntrance(x, y - STEP_SIZE) && count == 12)
        {
            y -= STEP_SIZE;
            ChangeMap(m);
        }
        else if (!(*m)->IsCollision(x, y - STEP_SIZE))
        {
            if ((*m)->IsWarZone(x, y - STEP_SIZE) && count == 12)
            {
                y -= STEP_SIZE;
                (*m)->SetXY((*m)->GetSX(), (*m)->GetSY() - STEP_SIZE);
                (*m)->ProduceEnemy(this, atkInterface);
            }
            else
            {
                (*m)->SetXY((*m)->GetSX(), (*m)->GetSY() - STEP_SIZE);
                y -= STEP_SIZE;
            }
        }
    }

    if (isForwardDown)
    {
        if ((*m)->IsEntrance(x, y + SM) && count == 12)
        {
            y += STEP_SIZE;
            ChangeMap(m);
        }
        else if (!(*m)->IsCollision(x, y + SM))
        {
            if ((*m)->IsWarZone(x, y + SM) && count == 12)
            {
                y += STEP_SIZE;
                (*m)->SetXY((*m)->GetSX(), (*m)->GetSY() + STEP_SIZE);
                (*m)->ProduceEnemy(this, atkInterface);
            }
            else
            {
                (*m)->SetXY((*m)->GetSX(), (*m)->GetSY() + STEP_SIZE);
                y += STEP_SIZE;
            }
        }
    }
}
void CHero::OnShow()
{
    //往上走
    if (isMovingUp)
    {
        HeroMovingBack.SetTopLeft(HERO_X, HERO_Y);
        HeroMovingBack.OnShow();
    }

    if (isForwardUp && !isMovingUp)
    {
        HeroBack.SetTopLeft(HERO_X, HERO_Y);
        HeroBack.ShowBitmap();
    }

    //往下走
    if (isMovingDown)
    {
        HeroMovingFront.SetTopLeft(HERO_X, HERO_Y);
        HeroMovingFront.OnShow();
    }

    if (isForwardDown && !isMovingDown)
    {
        HeroFront.SetTopLeft(HERO_X, HERO_Y);
        HeroFront.ShowBitmap();
    }

    //往左走
    if (isMovingLeft)
    {
        HeroMovingLeft.SetTopLeft(HERO_X, HERO_Y);
        HeroMovingLeft.OnShow();
    }

    if (isForwardLeft && !isMovingLeft)
    {
        HeroLeft.SetTopLeft(HERO_X, HERO_Y);
        HeroLeft.ShowBitmap();
    }

    //往又走
    if (isMovingRight)
    {
        HeroMovingRight.SetTopLeft(HERO_X, HERO_Y);
        HeroMovingRight.OnShow();
    }

    if (isForwardRight && !isMovingRight)
    {
        HeroRight.SetTopLeft(HERO_X, HERO_Y);
        HeroRight.ShowBitmap();
    }

    if (inBag)
    {
        //heroBackPack.Open();
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
bool CHero::CheckForward(CMap** m)
{
    int eventCheckIndex = 0;

    if (isForwardLeft)
    {
        eventCheckIndex = (*m)->CheckID(x - STEP_SIZE, y, GetDirection());
    }

    if (isForwardRight)
    {
        eventCheckIndex = (*m)->CheckID(x + SM, y, GetDirection());
    }

    if (isForwardUp)
    {
        eventCheckIndex = (*m)->CheckID(x, y - STEP_SIZE, GetDirection());
    }

    if (isForwardDown)
    {
        eventCheckIndex = (*m)->CheckID(x, y + SM, GetDirection());
    }

    if (eventCheckIndex == WeibaiTown_pick_Pokemomball)
    {
        gameMenu->RecieveData(0, 1);
        gameMenu->RecieveData(1, 2);
        gameMenu->RecieveData(3, 2);
    }

    return eventCheckIndex;
}
int* CHero::GetMoney()
{
    return &money;
}
int CHero::GetDirection()
{
    if (isForwardUp) return 0;
    else if (isForwardDown) return 1;
    else if (isForwardLeft) return 2;
    else return 3;
}
void CHero::trigger(CMap* m)
{
    isDialog =  CheckForward(&m);
}
void CHero::ReceiveData(CMap* m, ActionObject* i)
{
    gameMap = m;
    gameMenu = i;
}
void CHero::OpenBag()
{
    canMove = false;
    inBag = true;
}
void CHero::CloseBag()
{
    inBag = false;
    canMove = true;
}
void CHero::BackpackCursorMove()
{
    //heroBackPack.CursorMove();
}
void CHero::GetItem(int itemID, int amount)
{
    //heroBackPack.AddItem(itemID, amount);
}
bool CHero::IsInBag()
{
    return inBag;
}
/*void CHero::OpenMenu()
{
    inMenu = true;

    switch (menuFlag)
    {
        case 0:
            //menuflag.setPosition
            break;

        case 1:
            //menuflag.setPosition
            break;

        case 2:
            //menuflag.setPosition
            break;

        case 3:
            //menuflag.setPosition
            break;

        case 4:
            //menuflag.setPosition
            break;
    }
}*/
void CHero::SetXY(int nx, int ny)
{
    x = nx;
    y = ny;
}

void CHero::KeyIn(UINT nChar)
{
    const char KEY_LEFT = 0x25; // keyboard左箭頭
    const char KEY_UP = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN = 0x28; // keyboard下箭頭
    const char KEY_Z = 0x5a;

    if (InDialog())
        SetCanMove(false);
    else SetCanMove(true);

    if (!IsMoving() && GetCount() == 0 && !InDialog())
    {
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
        SetCanMove(false);
        trigger(gameMap);
    }

    /*if (inMenu)
    {
        if (nChar == KEY_UP && menuFlag > 0)
            menuFlag--;

        if (nChar == KEY_DOWN && menuFlag < 5)
            menuFlag++;
    }*/
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

    for (auto i : pokemons)
    {
        if (i->GetRemainHP() > 0)
        {
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
}
