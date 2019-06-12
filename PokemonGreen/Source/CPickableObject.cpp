#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CPickableObject.h"
namespace game_framework
{
	int CPickableObject::GetX()
	{
		return ox;
	}

	int CPickableObject::GetY()
	{
		return oy;
	}

	void CPickableObject::OnShow(int sx, int sy)
	{
		pickable_object.SetTopLeft(ox - sx, oy - sy);
		pickable_object.ShowBitmap();
	}

	void CPickableObject::LoadBitmap()
	{
		pickable_object.LoadBitmap(IDB_PICKABLE_OBJECT, RGB(255, 0, 0));
	}

	void CPickableObject::SetXY(unsigned int x, unsigned int y)
	{
		this->ox = x;
		this->oy = y;
	}
}
