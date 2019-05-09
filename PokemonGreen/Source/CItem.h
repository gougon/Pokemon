#pragma once
enum Item_ID
{
	Item_Antidote, //0
	Item_SmallVulnerary, //1
	Item_BigVulnerary,	 //2
	Item_FighterGlove,	 //3
	Item_PokeBall		//4
};
namespace game_framework
{
	class CItem
	{
	public:
		CItem(int itemID);
		int GetID();
		int GetCost();
		int GetCategorie();
		string GetName();
		string GetDescription();
		CMovingBitmap* GetImage();
	private:
		int categorie;
		int ID;
		int cost;
		string name;
		string description;
		CMovingBitmap itemImage;
	};
}