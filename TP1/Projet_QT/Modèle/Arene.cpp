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
