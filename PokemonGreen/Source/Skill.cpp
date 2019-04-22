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

	string Skill::GetAttributeText()
	{
		switch (attribute) {
		case normal:
			return "normal";
		case fighting:
			return "fighting";
		case flying:
			return "flying";
		case poison:
			return "poison";
		case ground:
			return "ground";
		case rock:
			return "rock";
		case bug:
			return "bug";
		case ghost:
			return "ghost";
		case steel:
			return "steel";
		case fire:
			return "fire";
		case water:
			return "water";
		case grass:
			return "grass";
		case electric:
			return "electric";
		case psychic:
			return "psychic";
		case ice:
			return "ice";
		case dragon:
			return "dragon";
		case dark:
			return "dark";
		default:
			ASSERT("Skill doesn't have attribute!");
			return 0;
		}
	}

	string Skill::GetName()
	{
		return name;
	}

	string Skill::GetDescription()
	{
		return description;
	}

	int Skill::GetRemainPP()
	{
		return remainpp;
	}

	int Skill::GetAllPP()
	{
		return allpp;
	}

	int Skill::GetPower()
	{
		return power;
	}

	int Skill::GetHitRate()
	{
		return (int)(hitRate * 100);
	}
}