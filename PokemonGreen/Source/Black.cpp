#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Black.h"

namespace game_framework {
	Black::Black()
	{
		black.LoadBitmap(IDB_BLACK);
		black.SetTopLeft(0, 0);
	}

	Black* Black::Instance()
	{
		return &delay;
	}

	void Black::Draw()
	{

	}
}