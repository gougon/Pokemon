#pragma once
#include <string>
#include <vector>
#include "CItem.h"
#include "CHero.h"
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	class Pokeball : public CItem {
	public:
		Pokeball();
		void OnMove();
		void OnShow();
		void Use(CHero &hero, Pokemon &enemy);
	private:
		void LoadBitmap();
		void SetPos();

		bool isThrow, isCatch;
		int counter, x, y;
		CAnimation ballAnime;
	};
}