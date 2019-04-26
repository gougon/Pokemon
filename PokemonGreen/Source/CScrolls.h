#pragma once
#pragma once
#include "CItem.h"
namespace game_framework
{
class CScrolls : public CItem
{
    public:
        CScrolls(int);
        int GetID();
        int GetCost();
        string GetName();
        string GetDescription();
        CMovingBitmap* GetImage();
        virtual void use();
    private:
        CMovingBitmap scrolls_image;
        string name;
        string description;
        int itemID;
        int cost;
};
}