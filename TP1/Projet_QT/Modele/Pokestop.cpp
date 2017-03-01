/****************************************************************************
 * Fichier: Pokestop.cpp
 * Auteurs: Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 * Date: 12 fevrier 2017
 * Description: Implementation de la classe Pokestop
 ****************************************************************************/
#include "Pokestop.h"

Pokestop::Pokestop()
    : _distAvantActif(0)
{ }

Pokestop::~Pokestop() {}

void Pokestop::visiter() {
    _distAvantActif = 100;
}

void Pokestop::diminuerDistanceAvantActif(int distance) {
    if (_distAvantActif > distance) {
        _distAvantActif -= distance;
    }
    else {
        _distAvantActif = 0;
    }
}

bool Pokestop::_estActif() const {
    return _distAvantActif <= 0;
}

int Pokestop::_obtenirDistanceAvantActif() const {
    return _distAvantActif;
}
