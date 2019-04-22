#pragma once

#include <string>
#include "Pokemon.h"

using namespace std;
namespace game_framework {
	enum pokemonName {
		treecko
	};

	class PokemonFactory {
	public:
		Pokemon* CreatePokemon(pokemonName pokemonName);
		Pokemon* CreatePokemon(pokemonName pokemonName, string name);
		Pokemon* CreateEnemy(pokemonName pokemonName);
	};
}

