/****************************************************************************
 * Fichier: Arene.cpp
 * Auteurs: Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 * Date: 12 fevrier 2017
 * Description: Implementation de la classe Arene
 ****************************************************************************/
#include <stdexcept>

#include "Arene.h"

Arene::Arene()
    : _estDejaVisite(false)
{ }

Arene::~Arene() {}

void Arene::visiter() {
    if (!_estDejaVisite) {
        _estDejaVisite = true;
    }
    else {
        throw std::runtime_error("Erreur : Impossible de revisiter une "
            "arene deja visitee.");
    }
}

void Arene::diminuerDistanceAvantActif(int distance) {}

bool Arene::_estActif() const {
    return !_estDejaVisite;
}

// PRIVATE:

int Arene::_obtenirDistanceAvantActif() const {
    if (!_estDejaVisite) {
        return 0;
    }
    else {
        return INT_MAX;
    }
}
