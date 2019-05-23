#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CHero.h"
#include "Characters.h"
#include "CMap.h"
#include "NpcFactory.h"

namespace game_framework {
	Characters::Characters(AtkInterface *atkInterface) :
		atkInterface(atkInterface)
	{
		// empty body
	}

	Characters::~Characters()
	{
		for (auto i : npcs) {
			delete i;
		}
	}

	void Characters::InitNpcs()
	{
		// add all npcs
		NpcFactory factory;
		npcs.push_back(factory.CreateNpc(trainerMay, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenMom, *atkInterface));

		// load bitmap for all npcs
		LoadBitmap();
	}

	void Characters::KeyDownListener(UINT nChar, CHero &hero, CMap &map)
	{
		for (auto i : npcs) {
			if(i->GetMap() == map.GetName())
				i->KeyDownListener(nChar, hero);
		}
	}

	void Characters::OnShow(CHero &hero, CMap &map)
	{
		for (auto i : npcs) {
			if (i->GetMap() == map.GetName())
				i->OnShow(hero);
		}
	}

	void Characters::ReShow(CHero &hero, CMap &map)
	{
		for (auto i : npcs) {
			if (i->GetMap() == map.GetName())
				i->ReShow(hero);
		}
	}

	void Characters::OnMove(CHero &hero, CMap &map)
	{
		for (auto i : npcs) {
			if (i->GetMap() == map.GetName())
				i->OnMove();
		}
	}

	bool Characters::IsCollision(int x, int y, CMap &map)
	{
		for (auto i : npcs) {
			if (i->GetMap() == map.GetName() && i->IsCollision(x, y))
				return true;
		}

		// none collision
		return false;
	}

	bool Characters::IsTalk()
	{
		for (auto i : npcs) {
			if (i->IsTalk())
				return true;
		}

		// nobody talk
		return false;
	}

	// private

	void Characters::LoadBitmap()
	{
		// list trainers
		for (auto i : npcs) {
			i->LoadBitmap();
		}
	}
}