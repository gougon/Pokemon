#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CDialog.h"

using namespace std;
namespace game_framework
{
CDialog::CDialog()
{
}

void CDialog::SetText(string inputstr)
{
    showString = inputstr;
}

void CDialog::InitDialog(char type)
{
    //判斷此對話性質
    if (type == 's') screen.LoadBitmap(SYSTEM_DIALOG_SCREEN, RGB(255, 0, 0));
    else screen.LoadBitmap(NORMAL_DIALOG_SCREEN, RGB(255, 0, 0));

    //加載游標
    cursor.AddBitmap(TEXT_CURSOR1, RGB(255, 0, 0));
    cursor.AddBitmap(TEXT_CURSOR2, RGB(255, 0, 0));
    cursor.AddBitmap(TEXT_CURSOR3, RGB(255, 0, 0));
    cursor.SetDelayCount(5);
    //加載文字
    showAlphabet.LoadBitmap();
}

void CDialog::OnMove()
{
    cursor.OnMove();
    //sequential showing text
}

void CDialog::OnShow()
{
	screen.SetTopLeft(5, 340);
	screen.ShowBitmap();
	int length = showString.length();
	int firstSentenceLength = showString.substr(0, showString.find(';')).length();
	int brFlag = 0;

	for (int i = 0; i <= length; i++)
	{
		if (i > 0 && showString[i-1] == ';')
		{
			brFlag = 1;
			i = 0;
			length -= firstSentenceLength;
			TRACE("\nfirstsentance length = %d\n", firstSentenceLength);
		}
		TRACE("\ni = %d, showstring[i] = %c\n", i + brFlag * firstSentenceLength, showString[i + brFlag * firstSentenceLength]);
		showAlphabet.GetAlphabet(showString[i + (brFlag) * firstSentenceLength])->SetTopLeft(55 + 16 * i, 360 + (brFlag * 55));
		showAlphabet.GetAlphabet(showString[i + (brFlag) * firstSentenceLength])->ShowBitmap();
	}
}
}