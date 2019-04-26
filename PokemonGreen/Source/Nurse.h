#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"
#include "Pokemon.h"
#include "CDialog.h"

using namespace std;
namespace game_framework
{
	class Nurse : public ActionObject
	{
	public:
		Nurse();
		virtual void Init();
		virtual void OnShow();
		virtual void OnMove();
		virtual void LoadBitmap();
		virtual void KeyDownListener(UINT nChar);
		void ReceiveData(vector<Pokemon*>* pokemons);
		/*void Start();
		void End();
		bool IsWork();*/
	protected:
		bool isWork = false;
		int count;
		vector<Pokemon*>* pokemons;
		CDialog dialogBox;
	};
}