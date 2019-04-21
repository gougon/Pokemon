#pragma once
#include "CItem.h"
namespace game_framework
{
class CFruit : public CItem
{
    public:
        CFruit(int);
        int GetID();
        string GetName();
        string GetDescription();
        CMovingBitmap* GetImage();
        virtual void use();
    private:
        CMovingBitmap fruit_image;
        string name;
        string description;
        int itemID;
};
}