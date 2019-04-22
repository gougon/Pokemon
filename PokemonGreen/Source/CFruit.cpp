#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "CFruit.h"
namespace game_framework
{
CFruit::CFruit(int fruitID)
{
    /*
    if (fruitID == Item_Antidote)
    {
        this->itemID = fruitID;
        this->name = "antidote";
        this->description = "poison recover";
        this->fruit_image.LoadBitmap(IDB_ANTIDOTE);
    }*/
}
int CFruit::GetID()
{
    return this->itemID;
}
string CFruit::GetName()
{
    return this->name;
}
string CFruit::GetDescription()
{
    return this->description;
}
CMovingBitmap* CFruit::GetImage()
{
    return  &fruit_image;
}
void CFruit::use()
{
    //
}
}