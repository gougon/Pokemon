#pragma once
#include "Pokemon.h"
enum Item_ID
{
	Item_Antidote, //0
	Item_SmallVulnerary, //1
	Item_BigVulnerary,	 //2
	Item_FighterGlove,	 //3
	Item_PokeBall,		//4
	Item_BurnMedicine	//5
};
namespace game_framework
{
	class CItem
	{
	public:
		CItem();
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