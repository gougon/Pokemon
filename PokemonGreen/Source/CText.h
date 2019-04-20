#pragma once
#include "CAlphabet.h"
using namespace std;
namespace game_framework
{
class CText
{
    public:
        CText();
        void LoadBitmap();
        void SetDelayTime();
        void SetDelayTime(int);
        void SetFontSize(double);
        int GetLength();
        void SetText(string inputstr);
        void SetTopLeft(int x, int y);
        void OnShow();
    private:
        int delay = 0;
        int tx = 0, ty = 0;
        double fontsize = 16;
        string showString;
        CAlphabet alphabet;
};
};