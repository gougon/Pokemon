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
    if (goodsID == Item_FighterGlove)
    {
        this->itemID = goodsID;
        this->name = "glove";
        this->description = "add 15 atk";
        this->goods_image.LoadBitmap(IDB_GOODS_FIGHTERGLOVE);
        this->cost = 100;
    }
}
int CGoods::GetID()
{
    return this->itemID;
}
int CGoods::GetCost()
{
    return cost;
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
