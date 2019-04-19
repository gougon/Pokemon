#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "ActionObject.h"

namespace game_framework {
	ActionObject::ActionObject() :
		isWork(false)
	{
		// empty body
	}

	void ActionObject::Start()
	{
		isWork = true;
	}

	void ActionObject::End()
	{
		isWork = false;
	}

	bool ActionObject::IsWork()
	{
		return isWork;
	}
}