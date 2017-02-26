#include "Pokemon.h"

Pokemon::Pokemon(const std::map<Sommet, int>& distances)
    : _distAvantActif(0), Sommet(distances)
{ }

Pokemon::~Pokemon() {}

void Pokemon::visiter() {
    const int
        GAIN_POKEMON_RARE      = 100,
        GAIN_POKEMON_NORMAL    = 40,
        GAIN_POKEMON_FREQENT   = 10;
    const int
        DISTANCE_POUR_RARE     = 500,
        DISTANCE_POUR_NORMAL   = 200,
        DISTANCE_POUR_FREQUENT = 100;

    if (_gain == GAIN_POKEMON_RARE) {
        _distAvantActif = DISTANCE_POUR_RARE;
    }
    else if (_gain == GAIN_POKEMON_NORMAL) {
        _distAvantActif = DISTANCE_POUR_NORMAL;
    }
    else { // On assume que le gain est valide
        _distAvantActif = DISTANCE_POUR_FREQUENT;
    }
}

void diminuerDistanceAvantActif(int distance) {
    if (_distAvantActif >= distance) {
        _distAvantActif -= distance;
    }
    else {
        _distAvantActif = 0;
    }
}

bool Pokemon::_estActif() const {
    return _distAvantActif <= 0;
}