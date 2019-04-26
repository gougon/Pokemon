#pragma once
#include "CItem.h"
namespace game_framework
{
class CGoods : public CItem
{
    public:
        CGoods(int);
        int GetID();
        int GetCost();
        string GetName();
        string GetDescription();
        CMovingBitmap* GetImage();
        virtual void use();
    private:
        CMovingBitmap goods_image;
        string name;
        string description;
        int itemID;
        int cost;
};
}