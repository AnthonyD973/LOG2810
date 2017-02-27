#include "Sommet.h"

Sommet::Sommet()
{ }

Sommet::Sommet(int gain, const std::map<Sommet*, int>& distances)
    : _gain(gain), _distances(distances)
{ }

Sommet::~Sommet() {}

int Sommet::distanceA(const Sommet* s) const {
    int ret;

    if (s.estActif()) {
        ret = _distances[s];
    }
    else {
        int daa = s->_obtenirDistanceAvantActif();
        
        bool distEstInfinie = (daa <= INT_MAX - 1);
        if (!distEstInfinie) {
            ret = daa + _distances[s];
        }
        else {
            ret = daa;
        }
    }
    return ret;
}
