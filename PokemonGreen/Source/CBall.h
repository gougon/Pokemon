#pragma once
#include "CItem.h"
namespace game_framework
{
class CBall : public CItem
{
    public:
        CBall(int);
        int GetID();
        string GetName();
        string GetDescription();
        CMovingBitmap* GetImage();
        virtual void use();
    private:
        CMovingBitmap pokeball_image;
        string name;
        string description;
        int itemID;
};
}