#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Skill.h"

namespace game_framework {
	Skill::Skill() 
		: category(physical), power(0), allpp(0), remainpp(0), hitRate(0)
	{
		/* empty body */
	}
}