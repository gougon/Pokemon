#pragma once

#include <vector>
#include "AtkInterface.h"
#include "CHero.h"
#include "CDialog.h"

using namespace std;
namespace game_framework
{
	class AtkInterface;
	class CHero;
	enum direction {
		up, down, left, right
	};

	class Trainer {
	public:
		Trainer(AtkInterface *atkInterface);
		virtual void KeyDownListener(UINT nChar, CHero &hero) = 0;
		virtual void LoadBitmap() = 0;
		virtual void OnShow(CHero &hero) = 0;
		virtual void OnMove() { }; // for don't move
		virtual void OnMove(CHero &hero) { }; // for need to move
		void SetIsLose(bool flag);
		int GetPmNum();
		int GetAliveNum();
		string GetName();
		CMovingBitmap *GetAtkImg();
		Pokemon *GetPokemon(int order);
		vector<Pokemon*>* GetPokemons();
		bool IsTalk();
		bool IsCollision(int x, int y);
	protected:
		virtual void Talk(CHero &hero) = 0;
		void StopTalk();
		void StartAtk(CHero* self, Trainer* trainer, AtkInterface &atkInterface);
		bool IsBeTalked(CHero &hero);

		AtkInterface *atkInterface;
		CMovingBitmap normalImg[4], atkImg;
		vector<Pokemon*> pokemons;
		CDialog unLoseDialog, loseDialog;
		string name;
		int direction;
		int x, y;	// 現在所在位置，不用算sm
		int prize;
		int atkDialogCounter;
		bool isTalk, isLose;
	};
}
