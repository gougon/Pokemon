#pragma once
#include "CHero.h"
#include "CItem.h"
namespace game_framework {
	class ItemPokeBall : public CItem {
	public:
		ItemPokeBall();
		virtual ~ItemPokeBall();
		void OnMove();
		void OnShow();
		void UsePokeBall(CHero* , Pokemon*);
		bool IsCatch();
		bool animeEnd();
		virtual bool Use(Pokemon* pm);
		virtual bool Take(Pokemon* pm, bool replacement);
	private:
		void LoadBitmap();
		void SetPos();

		bool isThrow, isCatch ,endFlag , ballopen;
		int counter, x, y;
		CAnimation ballAnime;
	};
}