#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "CProp.h"
namespace game_framework
{
CProp::CProp(int propID)
{
    if (propID == Item_Antidote)
    {
        this->itemID = propID;
        this->name = "antidote";
        this->description = "poison recover";
        this->prop_image.LoadBitmap(IDB_ANTIDOTE);
    }
}
int CProp::GetID()
{
    return this->itemID;
}
string CProp::GetName()
{
    return this->name;
}
string CProp::GetDescription()
{
    return this->description;
}
CMovingBitmap* CProp::GetImage()
{
    return  &prop_image;
}
void CProp::use()
{
    //
}
}
