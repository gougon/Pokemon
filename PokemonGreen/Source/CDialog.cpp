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
    TRACE("showString length = %d\n", showString.size());
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
    int brFlag = 0;

    for (int i = 0; i <= length; i++)
    {
        if (showString[i] == ';')
        {
            brFlag = 1;
            i = 0;
            length -= 21;
        }

        showAlphabet.GetAlphabet(showString[i + (brFlag) * 21])->SetTopLeft(55 + 24 * i, 360 + (brFlag * 55));
        showAlphabet.GetAlphabet(showString[i + (brFlag) * 21])->ShowBitmap();
    }
}
}