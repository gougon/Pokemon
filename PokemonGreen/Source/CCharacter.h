#pragma once
#include <vector>
#include <string>
using namespace std;
enum characterId
{
    mom          //0
};
namespace game_framework
{
class CCharacter
{
    public:
        CCharacter();
        CCharacter(int chaID);
        CMovingBitmap* setCharacter(int chaNum);
        virtual int GetX()
        {
            return 0;
        }
        virtual int GetY()
        {
            return 0;
        }
        virtual void OnMove() {}
        virtual int GetVer()
        {
            return 0;
        }
        virtual void Initialize() {}
        virtual void LoadBitmap() {}
        virtual void OnShow(int, int) {}
        virtual void Talk(int) {}
    protected:
        CMovingBitmap* character_scene_pointer;
        CMovingBitmap  scene[4];
        int stepcounter = 0;
};
}