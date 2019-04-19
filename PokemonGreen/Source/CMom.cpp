#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CMom.h"
namespace game_framework
{
CMom::CMom()
{
    character_scene = setCharacter(0);
}

void CMom::SetXY(int cx, int cy)
{
    this->cx = cx;
    this->cy = cy;
}

void CMom::OnMove()
{
    if (canMoving)
    {
        stepcounter++;
        //TRACE("stepcounter = %d\n", stepcounter);

        if (stepcounter == 132)
        {
            isForwardUp = false;
            isForwardDown = false;
            isForwardLeft = false;
            isForwardRight = false;

            if (step == 0)
            {
                for (int i = 0; i < 12; i++)
                {
                    SetXY(cx, cy);
                    cx -= 5;
                }

                isForwardLeft = true;
            }
            else if (step == 1)
            {
                cy += 60;
                isForwardDown = true;
            }
            else if (step == 2)
            {
                cx += 60;
                isForwardRight = true;
            }
            else if (step == 3)
            {
                cx += 60;
                isForwardRight = true;
            }
            else if (step == 4)
            {
                cy -= 60;
                isForwardUp = true;
            }
            else if (step == 5)
            {
                cy -= 60;
                isForwardUp = true;
            }
            else if (step == 6)
            {
                cx -= 60;
                isForwardLeft = true;
            }
            else if (step == 7)
            {
                cx -= 60;
                isForwardLeft = true;
            }
            else if (step == 8)
            {
                cy += 60;
                isForwardDown = true;
            }
            else step = 0;

            step++;
            stepcounter = 0;
        }
    }
}

int CMom::GetX()
{
    return cx;
}
int CMom::GetY()
{
    return cy;
}

void CMom::Initialize()
{
    isForwardRight = isForwardLeft = isForwardUp = false;
    isForwardDown = true;
    canMoving = true;
    isBusy = false;
    var = 0;
}

void CMom::LoadBitmap()
{
    character_scene[0].LoadBitmap(MOM_UP, RGB(255, 0, 0));
    character_scene[1].LoadBitmap(MOM_DOWN, RGB(255, 0, 0));
    character_scene[2].LoadBitmap(MOM_LEFT, RGB(255, 0, 0));
    character_scene[3].LoadBitmap(MOM_RIGHT, RGB(255, 0, 0));
}

void CMom::OnShow(int sx, int sy)
{
    //TRACE("mom loc = %d , %d\n", cx - sx, cy - sy);
    if (isForwardUp)
    {
        character_scene[0].SetTopLeft(cx - sx, cy - sy);
        character_scene[0].ShowBitmap();
    }
    else if (isForwardDown)
    {
        character_scene[1].SetTopLeft(cx - sx, cy - sy);
        character_scene[1].ShowBitmap();
    }
    else if (isForwardLeft)
    {
        character_scene[2].SetTopLeft(cx - sx, cy - sy);
        character_scene[2].ShowBitmap();
    }
    else
    {
        character_scene[3].SetTopLeft(cx - sx, cy - sy);
        character_scene[3].ShowBitmap();
    }
}

void CMom::Talk(int herodirection)
{
    isBusy = true;
    canMoving = false;
    SetDirection(herodirection);
    var++;
    TRACE("Mom talk\n");
}

int CMom::GetVer()
{
    if (var > 4) var = 3;

    return var;
}

void CMom::SetDirection(int herodirection)
{
    TRACE("herodirection = %d\n", herodirection);
    isForwardDown = (herodirection == 0) ? true : false;
    isForwardUp = (herodirection == 1) ? true : false;
    isForwardRight = (herodirection == 2) ? true : false;
    isForwardLeft = (herodirection == 3) ? true : false;
}

}
