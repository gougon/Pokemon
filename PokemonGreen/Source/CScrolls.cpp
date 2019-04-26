#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "CScrolls.h"
namespace game_framework
{
CScrolls::CScrolls(int scrollID)
{
    /*
    if (scrollID == Item_Antidote)
    {
    	this->itemID = scrollID;
    	this->name = "antidote";
    	this->description = "poison recover";
    	this->scrolls_image.LoadBitmap(IDB_ANTIDOTE);
    }*/
}
int CScrolls::GetID()
{
    return this->itemID;
}
int CScrolls::GetCost()
{
    return cost;
}
string CScrolls::GetName()
{
    return this->name;
}
string CScrolls::GetDescription()
{
    return this->description;
}
CMovingBitmap* CScrolls::GetImage()
{
    return  &scrolls_image;
}
void CScrolls::use()
{
    //
}
}
