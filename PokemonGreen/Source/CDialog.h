#pragma once
#include <string>
#include <vector>
#include "CAlphabet.h"

using namespace std;
namespace game_framework {
	enum alphaID {
		a, b, c, d, e, f, g, h, 
		i, j, k, l, m, n, o, p, 
		q, r, s, t, u, v, w, x, 
		y, z, 
	};

	class CDialog {
	public:
		CDialog();
		~CDialog();
		void SetText(string inputstr);
		void AddText(string text);
		void Next();
		void Reset();
		void InitDialog(char);
		void OnShow();
		bool IsEnd();
		int GetCurrentTextNumber();
	private:
		CMovingBitmap screen;
		string showString;
		CAlphabet showAlphabet;
		vector<string> texts;
		int textCounter, textNum;
	};
}