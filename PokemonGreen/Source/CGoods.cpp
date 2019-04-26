#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "CGoods.h"
namespace game_framework
{
CGoods::CGoods(int goodsID)
{
    /*
    if (goodsID == Item_Antidote)
    {
        this->itemID = goodsID;
        this->name = "antidote";
        this->description = "poison recover";
        this->goods_image.LoadBitmap(IDB_ANTIDOTE);
    }*/
}
int CGoods::GetID()
{
    return this->itemID;
}
string CGoods::GetName()
{
    return this->name;
}
string CGoods::GetDescription()
{
    return this->description;
}
CMovingBitmap* CGoods::GetImage()
{
    return  &goods_image;
}
void CGoods::use()
{
    //
}
}
