#pragma once
enum Item_ID
{
    Item_Antidote //0
};
namespace game_framework
{
class CItem
{
    public:
        CItem();
        virtual void Use();
};
}