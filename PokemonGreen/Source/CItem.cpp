#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "CItem.h"
namespace game_framework
{
	CItem::~CItem()
	{
		// empty body
	}

	int CItem::GetID()
	{
		return ID;
	}

	int CItem::GetCost()
	{
		return cost;
	}

	int CItem::GetCategorie()
	{
		return categorie;
	}

	string CItem::GetName()
	{
		return name;
	}

	string CItem::GetDescription()
	{
		return description;
	}

	CMovingBitmap * CItem::GetImage()
	{
		return &itemImage;
	}
}