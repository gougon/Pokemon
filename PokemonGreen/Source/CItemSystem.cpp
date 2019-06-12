#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <string>
#include "CItemSystem.h"
namespace game_framework
{
	string CItemSystem::GetNameByID(int ID)
	{
		switch (ID) {
			case 0: return "antidote"; break;
			case 1: return "s.vulnerary"; break;
			case 2: return "m.vulnerary"; break;
			case 3: return "glove"; break;
			case 4: return "pokeball"; break;
			case 5: return "burnmedicine"; break;
		}
		return "nothing";
	}
	int CItemSystem::GetIDByName(string name)
	{
		if (name == "antidote") return 0;
		else if (name == "s.vulnerary") return 1;
		else if (name == "m.vulnerary") return 2;
		else if (name == "glove") return 3;
		else if (name == "pokeball") return 4;
		else if (name == "burnmedicine") return 5;
		return -1;
	}
}