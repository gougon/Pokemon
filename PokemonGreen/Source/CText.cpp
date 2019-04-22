#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CText.h"
namespace game_framework
{
CText::CText()
{
}
void CText::LoadBitmap()
{
    alphabet.LoadBitmap();
}
void CText::SetDelayTime()
{
    this->delay = 0;
}
void CText::SetDelayTime(int delay)
{
    if (delay == 0) ASSERT(0);
    else this->delay = delay;
}
void CText::SetFontSize(double newFontSize)
{
    fontsize = newFontSize;
}
int CText::GetLength()
{
    return showString.length();
}
void CText::SetText(string inputstr)
{
    showString = inputstr;
}
void CText::SetTopLeft(int input_x, int input_y)
{
    this->tx = input_x;
    this->ty = input_y;
}

void CText::OnShow()
{
    int length = showString.length();

    for (int i = 0; i <= length; i++)
    {
        alphabet.GetAlphabet(showString[i])->SetTopLeft(tx + int(16 * i * fontsize / 16), ty);
        alphabet.GetAlphabet(showString[i])->ShowBitmap(fontsize / 16);
    }
}
}
