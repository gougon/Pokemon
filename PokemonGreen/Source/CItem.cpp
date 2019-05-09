#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "CItem.h"
namespace game_framework
{
CItem::CItem(int itemID)
{
	this->ID = itemID;
	switch (itemID) {
	case 0:
		this->categorie = 1;
		this->name = "antidote";
		this->description = "poison recover";
		this->cost = 10;
		this->itemImage.LoadBitmap(ITEM_ANTIDOTE);
		break;
	case 1:
		this->categorie = 1;
		this->name = "s.vulnerary";
		this->description = "recover 20hp";
		this->cost = 20;
		this->itemImage.LoadBitmap(ITEM_VULNERARY);
		break;
	case 2:
		this->categorie = 1;
		this->name = "m.vulnerary";
		this->description = "recover 30hp";
		this->cost = 30;
		this->itemImage.LoadBitmap(ITEM_VULNERARY);
		break;
	case 3:
		this->categorie = 5;
		this->name = "glove";
		this->description = "add 20atk";
		this->cost = 100;
		this->itemImage.LoadBitmap(ITEM_FIGHTERGLOVE);
		break;
	case 4:
		this->categorie = 2;
		this->name = "pokeball";
		this->description = "catch pokemon";
		this->cost = 150;
		this->itemImage.LoadBitmap(ITEM_POKEBALL);
	}
}
int CItem::GetID()
{
	return this->ID;
}
int CItem::GetCost()
{
	return this->cost;
}
int CItem::GetCategorie()
{
	return this->categorie;
}
string CItem::GetName()
{
	return this->name;
}
string CItem::GetDescription()
{
	return this->description;
}
CMovingBitmap * CItem::GetImage()
{
	return &itemImage;
}
}