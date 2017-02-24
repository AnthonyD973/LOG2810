#include "Pokestop.h"

Pokestop::Pokestop()
    : _distAvantActif(0), Sommet(distances)
{ }

Pokestop::~Pokestop() {}

void Pokestop::visiter() {
    _distAvantActif = 100;
}

void diminuerDistanceAvantActif(int distance) {
    if (_distAvantActif > distance) {
        _distAvantActif -= distance;
    }
    else {
        _distAvantActif = 0;
    }
}

bool Pokestop::_estActif() {
    return _distAvantActif <= 0;
}