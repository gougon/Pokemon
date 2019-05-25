#pragma once

#include <string>
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	enum pokemonName {
		treecko, jirachi, hooh, deoxys, gardevoir, grimer, grovyle, metang, pikachu, rayquaza, smoochum
	};

	class PokemonFactory {
	public:
		Pokemon* CreatePokemon(pokemonName pokemonName);
		Pokemon* CreatePokemon(pokemonName pokemonName, int level);
		Pokemon* CreatePokemon(pokemonName pokemonName, string name);
		Pokemon* CreateEnemy(pokemonName pokemonName);
		Pokemon* CreateEnemy(pokemonName pokemonName, int level);
		Pokemon* CreateEnemyRandom();
	};
}

