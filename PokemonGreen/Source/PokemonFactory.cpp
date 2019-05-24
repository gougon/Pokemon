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
#include "PmDeoxys.h"
#include "PmGardevoir.h"
#include "PmGrimer.h"
#include "PmGrovyle.h"
#include "PmMetang.h"
#include "PmPikachu.h"
#include "PmRayquaza.h"
#include "PmSmoochum.h"

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
		case deoxys:
			return new PmDeoxys(my);
			break;
		case gardevoir:
			return new PmGardevoir(my);
			break;
		case grovyle:
			return new PmGrovyle(my);
			break;
		case metang:
			return new PmMetang(my);
			break;
		case pikachu:
			return new PmPikachu(my);
			break;
		case rayquaza:
			return new PmRayquaza(my);
			break;
		case smoochum:
			return new PmSmoochum(my);
			break;
		default:
			return new PmTreecko(my);
			break;
		}
	}

	Pokemon* PokemonFactory::CreatePokemon(pokemonName pokemonName, int level)
	{
		Pokemon *pm = CreatePokemon(pokemonName);
		pm->SetLevel(level);
		return pm;
	}

	Pokemon* PokemonFactory::CreatePokemon(pokemonName pokemonName, string name)
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
		case deoxys:
			return new PmDeoxys(my);
			break;
		case gardevoir:
			return new PmGardevoir(my);
			break;
		case grovyle:
			return new PmGrovyle(my);
			break;
		case metang:
			return new PmMetang(my);
			break;
		case pikachu:
			return new PmPikachu(my);
			break;
		case rayquaza:
			return new PmRayquaza(my);
			break;
		case smoochum:
			return new PmSmoochum(my);
			break;
		default:
			return new PmTreecko(my);
			break;
		}
	}

	Pokemon* PokemonFactory::CreateEnemy(pokemonName pokemonName)
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
		case deoxys:
			return new PmDeoxys(my);
			break;
		case gardevoir:
			return new PmGardevoir(my);
			break;
		case grovyle:
			return new PmGrovyle(my);
			break;
		case metang:
			return new PmMetang(my);
			break;
		case pikachu:
			return new PmPikachu(my);
			break;
		case rayquaza:
			return new PmRayquaza(my);
			break;
		case smoochum:
			return new PmSmoochum(my);
			break;
		default:
			return new PmTreecko(my);
			break;
		}
	}

	Pokemon* PokemonFactory::CreateEnemy(pokemonName pokemonName, int level)
	{
		Pokemon *pm = CreateEnemy(pokemonName);
		pm->SetLevel(level);
		return pm;
	}

	Pokemon* PokemonFactory::CreateEnemyRandom()
	{
		int name = rand() % ALL_PM_NUM;
		return CreateEnemy((pokemonName)name);
	}
}