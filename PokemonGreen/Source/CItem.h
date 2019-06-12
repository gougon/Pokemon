#pragma once
#include "Pokemon.h"

namespace game_framework
{
	enum Item_ID
	{
		Item_Antidote, 
		Item_SmallVulnerary,
		Item_BigVulnerary,	
		Item_FighterGlove,	
		Item_PokeBall,		
		Item_BurnMedicine	
	};

	class CItem {
	public:
		virtual ~CItem();
		int GetID();
		int GetCost();
		int GetCategorie();
		string GetName();
		string GetDescription();
		CMovingBitmap* GetImage();
		virtual bool Use(Pokemon* pm) { return false; }
		virtual bool Take(Pokemon* pm , bool replacement) { return false; }
	protected:
		int ID;
		int categorie;
		string name;
		string description;
		int cost;
		CMovingBitmap itemImage;
	};
}