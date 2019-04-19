#pragma once
#include<string>
#include"CDialog.h"
using namespace std;
namespace game_framework
{
class CObject
{
    public:
        CObject();
        int GetX();
        int GetY();
        void Initialize();
        void SetXY(unsigned int, unsigned int);
    private:
        int ox, oy;
};
}