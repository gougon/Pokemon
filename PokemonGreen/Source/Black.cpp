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

	void Black::SetDelay(int millisecond)
	{
		this->millisecond = millisecond;
	}

	void Black::Draw()
	{
		static int counter = 0;
		int finalCounter = (millisecond / 33);
		if (counter < finalCounter) {
			counter++;
			black.ShowBitmap();
		}
		else {
			counter = 0;
		}
	}
}