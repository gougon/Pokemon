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
double CText::GetFontSize()
{
	return fontsize;
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
	int firstSentenceLength = showString.substr(0, showString.find(';')).length();
	int brFlag = 0;

	for (int i = 0; i <= length; i++)
	{
		if (i > 0 && showString[i - 1] == ';')
		{
			brFlag = 1;
			i = 0;
			length -= firstSentenceLength;
		}
		alphabet.GetAlphabet(showString[i + (brFlag)* firstSentenceLength])->SetTopLeft(
			(brFlag == 0) ? tx + int(16 * i * fontsize / 16) : tx + int(16 * (i - 1) * fontsize / 16), ty + (brFlag * 35));
		alphabet.GetAlphabet(showString[i + (brFlag)* firstSentenceLength])->ShowBitmap(fontsize / 16);
	}
}
}
