#pragma once

#include <vector>
#include "Npc.h"

using namespace std;
namespace game_framework {
	class Trainer : public Npc {
	public:
		Trainer(AtkInterface *atkInterface);
		virtual ~Trainer(); 
		virtual void KeyDownListener(UINT nChar, CHero &hero) = 0;
		virtual void LoadBitmap() = 0;
		virtual void OnShow(CHero &hero) = 0;
		virtual void ReShow(CHero &hero) = 0;
		virtual void OnMove() { }; // for don't move
		virtual void OnMove(CHero &hero) { }; // for need to move
		void InsertPokemon(Pokemon *pokemon);
		void SetXY(int x, int y);
		void SetIsEvent(bool flag);
		string GetName();
		int GetPmNum();
		int GetAliveNum();
		string GetMap();
		CMovingBitmap *GetAtkImg();
		Pokemon *GetPokemon(int order);
		vector<Pokemon*>* GetPokemons();
		bool IsTalk();
		bool IsCollision(int x, int y);
	protected:
		virtual void Talk(CHero &hero) = 0;
		void StopTalk(CHero &hero);
		void StartAtk(CHero* self, Trainer* trainer, AtkInterface &atkInterface);
		bool IsBeTalked(CHero &hero);
		bool IsDiscoverHero(CHero &hero);

		AtkInterface *atkInterface;
		CDialog eventDialog, normalDialog;
		vector<Pokemon*> pokemons;
		string name, map;
		int direction;
		int x, y;	// 現在所在位置，不用算sm
		bool isTalk, isEvent;
		int prize;
		int atkDialogCounter;
	};
}
