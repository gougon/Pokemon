#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CFatguy.h"
namespace game_framework
{
	CFatguy::CFatguy()
	{
		character_scene = setCharacter(1);
	}
	void CFatguy::SetXY(int cx, int cy)
	{
		this->cx = cx;
		this->cy = cy;
	}
	void CFatguy::OnMove()
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
	int CFatguy::GetX()
	{
		return cx;
	}
	int CFatguy::GetY()
	{
		return cy;
	}
	void CFatguy::Initialize()
	{
		isForwardRight = isForwardLeft = isForwardUp = false;
		isForwardDown = true;
		canMoving = true;
		isBusy = false;
		var = 0;
	}
	void CFatguy::LoadBitmap()
	{
		character_scene[0].LoadBitmap(FATGUY_UP, RGB(255, 0, 0));
		character_scene[1].LoadBitmap(FATGUY_DOWN, RGB(255, 0, 0));
		character_scene[2].LoadBitmap(FATGUY_LEFT, RGB(255, 0, 0));
		character_scene[3].LoadBitmap(FATGUY_RIGHT, RGB(255, 0, 0));
	}
	void CFatguy::OnShow(int sx, int sy)
	{
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
	void CFatguy::Talk(int herodirection)
	{
		isBusy = true;
		canMoving = false;
		SetDirection(herodirection);
		var++;
	}
	int CFatguy::GetVer()
	{
		if (var > 4) var = 3;

		return var;
	}
	void CFatguy::SetDirection(int herodirection)
	{
		isForwardDown = (herodirection == 0) ? true : false;
		isForwardUp = (herodirection == 1) ? true : false;
		isForwardRight = (herodirection == 2) ? true : false;
		isForwardLeft = (herodirection == 3) ? true : false;
	}
}
