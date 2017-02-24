#include <stdexcept>

#include "Arene.h"

Arene::Arene(const std::map<Sommet, int>& distances)
    : _estDejaVisite(false), Sommet(distances)
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

void diminuerDistanceAvantActif(int distance) {}

bool Arene::_estActif() const {
    return !_estDejaVisite;
}