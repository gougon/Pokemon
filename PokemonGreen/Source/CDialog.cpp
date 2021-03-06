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
		textCounter = 0;
		textNum = 0;
		showString = "";
	}

	CDialog::~CDialog()
	{
		texts.clear();
 		vector<string>(texts).swap(texts);
	}

	void CDialog::SetText(string inputstr)
	{
		showString = inputstr;
	}

	void CDialog::AddText(string text)
	{
		texts.push_back(text);
		textNum++;
	}

	void CDialog::Next()
	{
		textCounter = (textCounter == textNum) ? textCounter : textCounter + 1;
	}

	void CDialog::Reset()
	{
		textCounter = 0;
	}

	void CDialog::InitDialog(char type)
	{
		//判斷此對話性質
		if (type == 's') screen.LoadBitmap(SYSTEM_DIALOG_SCREEN, RGB(255, 0, 0));
		else screen.LoadBitmap(NORMAL_DIALOG_SCREEN, RGB(255, 0, 0));

		//加載文字
		showAlphabet.LoadBitmap();
	}

	void CDialog::OnShow()
	{
		screen.SetTopLeft(5, 340);
		screen.ShowBitmap();
		showString = (textNum == 0) ? showString : texts[textCounter];
		int length = showString.length();
		int firstSentenceLength = showString.substr(0, showString.find(';')).length();
		int brFlag = 0;

		for (int i = 0; i <= length; i++){
			if (i > 0 && showString[i-1] == ';') {
				brFlag = 1;
				i = 0;
				length -= firstSentenceLength;
			}
			showAlphabet.GetAlphabet(showString[i + (brFlag) * firstSentenceLength])->SetTopLeft(
				(brFlag == 0) ? 55 + 16 * i : 55 + 16 * (i - 1), 360 + (brFlag * 55));
			showAlphabet.GetAlphabet(showString[i + (brFlag) * firstSentenceLength])->ShowBitmap();
		}
	}

	bool CDialog::IsEnd()
	{
		return (textCounter == textNum);
	}

	int CDialog::GetCurrentTextNumber()
	{
		return textCounter;
	}
}