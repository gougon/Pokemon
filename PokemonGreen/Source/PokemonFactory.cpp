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
#include "PmVaporeon.h"
#include "PmVulpix.h"

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
		case vaporeon:
			return new PmVaporeon(my);
			break;
		case vulpix:
			return new PmVulpix(my);
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
			return new PmTreecko(my , name);
			break;
		case jirachi:
			return new PmJirachi(my, name);
			break;
		case hooh:
			return new PmHooh(my, name);
			break;
		case deoxys:
			return new PmDeoxys(my, name);
			break;
		case gardevoir:
			return new PmGardevoir(my, name);
			break;
		case grovyle:
			return new PmGrovyle(my, name);
			break;
		case metang:
			return new PmMetang(my, name);
			break;
		case pikachu:
			return new PmPikachu(my, name);
			break;
		case rayquaza:
			return new PmRayquaza(my, name);
			break;
		case smoochum:
			return new PmSmoochum(my, name);
			break;
		case vaporeon:
			return new PmVaporeon(my, name);
			break;
		case vulpix:
			return new PmVulpix(my, name);
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
		case deoxys:
			return new PmDeoxys(enemy);
			break;
		case gardevoir:
			return new PmGardevoir(enemy);
			break;
		case grovyle:
			return new PmGrovyle(enemy);
			break;
		case metang:
			return new PmMetang(enemy);
			break;
		case pikachu:
			return new PmPikachu(enemy);
			break;
		case rayquaza:
			return new PmRayquaza(enemy);
			break;
		case smoochum:
			return new PmSmoochum(enemy);
			break;
		case vaporeon:
			return new PmVaporeon(enemy);
			break;
		case vulpix:
			return new PmVulpix(enemy);
			break;
		default:
			return new PmTreecko(enemy);
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