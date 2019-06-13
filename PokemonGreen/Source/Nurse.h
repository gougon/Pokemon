#pragma once
#include <string>
#include <vector>
#include "CHero.h"
#include "ActionObject.h"
#include "Pokemon.h"
#include "CDialog.h"

using namespace std;
namespace game_framework {
	class Nurse : public ActionObject {
	public:
		Nurse();
		~Nurse();
		virtual void Init();
		virtual void OnShow();
		virtual void OnMove();
		virtual void LoadBitmap();
		virtual void KeyDownListener(UINT nChar);
		virtual void SetTopLeft() {}
		void ReceiveData(CHero &hero);
		void End();
		void Start();
	protected:
		enum yn {
			yes, no
		};

		const int YNPANEL_LEFT = 430;
		const int YNPANEL_TOP = 195;
		const int CURSOR_LEFT = 450;
		const int CURSOR_TOP = 225;
		const int CURSOR_TOP2 = 275;
		const int HEAL_ANIME_NUM = 12;		
		const int HEAL_BALL_LEFT = 225;
		const int HEAL_BALL_TOP = 90;
		const int HEAL_BALL_INTERVAL = 12;
		const int HEAL_BALL_DELAY = 20;

		bool IsHealing();
		void SetBall(CAnimation *ball, int row, int col);
		void Heal();

		bool isAnime;
		int count, choice, pmNum, audioCount;
		CHero *hero;
		vector<Pokemon*>* pokemons;
		CDialog dialogBox;
		CMovingBitmap ynPanel, cursor;
		CAnimation *ball;
	};
}