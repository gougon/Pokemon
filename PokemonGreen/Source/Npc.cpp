#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Npc.h"
namespace game_framework {
	Npc::Npc(NpcType type) :
		type(type), isTalk(false), isEvent(false)
	{
		// empty body
	}

	CDialog* Npc::GetDialog()
	{
		if (isTalk && isEvent)
			return &eventDialog;
		else if (isTalk && !isEvent)
			return &normalDialog;
		else
			return nullptr;
	}
}