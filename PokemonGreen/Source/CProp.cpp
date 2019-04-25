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
        this->prop_image.LoadBitmap(IDB_PROP_ANTIDOTE);
        this->cost = 5;
    }
    else if (propID == Item_SmallVulnerary)
    {
        this->itemID = propID;
        this->name = "s.vulnerary";
        this->description = "recover 20 hp";
        this->prop_image.LoadBitmap(IDB_PROP_VULNERARY);
        this->cost = 10;
    }
    else if (propID == Item_MediumVulnerary)
    {
        this->itemID = propID;
        this->name = "m.vulnerary";
        this->description = "recover 30 hp";
        this->prop_image.LoadBitmap(IDB_PROP_VULNERARY);
        this->cost = 15;
    }
}
int CProp::GetCost()
{
    return cost;
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
