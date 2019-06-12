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
#include "PokemonFactory.h"

namespace game_framework {
	Characters::Characters(AtkInterface *atkInterface) :
		atkInterface(atkInterface)
	{
		// empty body
	}

	Characters::~Characters()
	{
		for (auto i : npcs) 
			delete i;
		atkInterface = nullptr;
	}

	void Characters::InitNpcs()
	{
		// add all npcs
		NpcFactory factory;
		npcs.push_back(factory.CreateNpc(trainerMay, *atkInterface));
		npcs.push_back(factory.CreateNpc(trainerYoungster, *atkInterface));
		npcs.push_back(factory.CreateNpc(trainerGymYoungster, *atkInterface));
		npcs.push_back(factory.CreateNpc(trainerGymYamao, *atkInterface));
		npcs.push_back(factory.CreateNpc(trainerGymMaster, *atkInterface));
		npcs.push_back(factory.CreateNpc(trainerJK, *atkInterface));
		npcs.push_back(factory.CreateNpc(trainerBadguy, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenMom, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenFatguy, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenSister, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenBoy, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenGirl1, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenGirl2, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenGirl3, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenMan1, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenMan2, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenMan3, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenMan4, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenMan5, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenWoman1, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenWoman2, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenWoman3, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenWoman4, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenWoman5, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenResearcher, *atkInterface));
		npcs.push_back(factory.CreateNpc(citizenOdd, *atkInterface));
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
			if (i->GetMap() == map.GetName()) {
				if (i->GetType() == walker)
					i->OnMove(hero);
				else
					i->OnMove();
			}
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