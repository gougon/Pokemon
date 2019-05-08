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
#include "PmJirachi.h"
#include "PmHooh.h"

namespace game_framework {
	Pokemon* PokemonFactory::CreatePokemon(pokemonName pokemonName)
	{
		switch (pokemonName) {
		case treecko:
			return new PmTreecko(my);
			break;
		case jirachi:
			return new PmJirachi(my);
			break;
		case hooh:
			return new PmHooh(my);
			break;
		default:
			return new PmTreecko(my);
			break;
		}
	}

	Pokemon* PokemonFactory::CreatePokemon(pokemonName pokemonName, string name)
	{
		switch (pokemonName) {
		case treecko:
			return new PmTreecko(my, name);
			break;
		case jirachi:
			return new PmJirachi(my, name);
			break;
		case hooh:
			return new PmHooh(my, name);
			break;
		default:
			return new PmTreecko(my, name);
			break;
		}
	}

	Pokemon* PokemonFactory::CreateEnemy(pokemonName pokemonName)
	{
		switch (pokemonName) {
		case treecko:
			return new PmTreecko(enemy);
			break;
		case jirachi:
			return new PmJirachi(enemy);
			break;
		case hooh:
			return new PmHooh(enemy);
			break;
		default:
			return new PmTreecko(enemy);
			break;
		}
	}

	Pokemon* PokemonFactory::CreateEnemyRandom()
	{
		int name = rand() % ALL_PM_NUM;
		return CreateEnemy((pokemonName)name);
	}
}