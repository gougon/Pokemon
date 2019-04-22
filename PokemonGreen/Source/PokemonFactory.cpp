#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "PokemonFactory.h"
#include "Pokemon.h"
#include "PmTreecko.h"

namespace game_framework {
	Pokemon* PokemonFactory::CreatePokemon(pokemonName pokemonName)
	{
		//Skill *skill;
		if (pokemonName == treecko) {
			return new PmTreecko(my);
		}
		else {			 // else if skill......
			return new PmTreecko(my);
		}
	}

	Pokemon* PokemonFactory::CreatePokemon(pokemonName pokemonName, string name)
	{
		//Skill *skill;
		if (pokemonName == treecko) {
			return new PmTreecko(my, name);
		}
		else {			 // else if skill......
			return new PmTreecko(my, name);
		}
	}

	Pokemon* PokemonFactory::CreateEnemy(pokemonName pokemonName)
	{
		//Skill *skill;
		if (pokemonName == treecko) {
			return new PmTreecko(enemy);
		}
		else {			 // else if skill......
			return new PmTreecko(enemy);
		}
	}
}