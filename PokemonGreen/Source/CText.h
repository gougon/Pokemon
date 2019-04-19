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
        void SetText(string inputstr);
        void SetTopLeft(int x, int y);
		int GetLength();
		int GetFontSize();
        void OnShow();
    private:
        int delay = 0;
		int fontSize = 24;
        int tx = 0, ty = 0;
        string showString;
        CAlphabet alphabet;
};
};