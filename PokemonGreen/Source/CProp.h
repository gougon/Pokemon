#pragma once
#include "CItem.h"
namespace game_framework
{
class CProp : public CItem
{
    public:
        CProp(int);
        int GetID();
        int GetCost();
        string GetName();
        string GetDescription();
        CMovingBitmap* GetImage();
        virtual void use();
    private:
        CMovingBitmap prop_image;
        string name;
        string description;
        int itemID;
        int cost;
};
}