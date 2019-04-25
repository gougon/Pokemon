#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "CBall.h"
namespace game_framework
{
CBall::CBall(int pokeballID)
{
    /*
    if (pokeballID == Item_Antidote)
    {
        this->itemID = pokeballID;
        this->name = "antidote";
        this->description = "poison recover";
        this->pokeball_image.LoadBitmap(IDB_ANTIDOTE);
    }*/
}
int CBall::GetID()
{
    return this->itemID;
}
int CBall::GetCost()
{
    return cost;
}
string CBall::GetName()
{
    return this->name;
}
string CBall::GetDescription()
{
    return this->description;
}
CMovingBitmap* CBall::GetImage()
{
    return  &pokeball_image;
}
void CBall::use()
{
    //
}
}
