#pragma once
enum Item_ID
{
    Item_Antidote, //0
    Item_SmallVulnerary, //1
    Item_MediumVulnerary, //2
    Item_FighterGlove  //3
};
namespace game_framework
{
class CItem
{
    public:
        CItem();
        virtual int GetCost() = 0;
        virtual int GetID() = 0;
        virtual string GetName() = NULL;
        virtual string GetDescription() = NULL;
        virtual CMovingBitmap* GetImage() = NULL;
};
}