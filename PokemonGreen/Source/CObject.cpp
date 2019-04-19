#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CObject.h"
namespace game_framework
{
CObject::CObject()
{
}
int CObject::GetX()
{
    return ox;
}

int CObject::GetY()
{
    return oy;
}

void CObject::Initialize()
{
}

void CObject::SetXY(unsigned int x, unsigned int y)
{
    this->ox = x;
    this->oy = y;
}
}
