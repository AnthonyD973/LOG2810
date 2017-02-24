#include "Algo.h"


// TODO : BESOIN D'UN CONSTRUCTEUR PAR COPIE POUR LA CLASSE GRAPHE


Algo(int nSommetsAEssayer) : _N_SOMMETS_A_ESSAYER(nSommetsAEssayer) {}

~Algo() {}

Chemin Algo::meilleurCheminPourGainDe(
    int gain,
    Graphe graphe,
    Sommet* sDepart) const
{
    Chemin meilleurCheminTrouve;
    const std::vector<Sommet*> MEILLEURS_SOMMETS =
        _trouverMeilleursSommets(sDepart);

    for(Sommet* s : MEILLEURS_SOMMETS) {
        Chemin chemin = meilleurCheminPourGainDe(gain - s->obtenirGain());
        chemin.distance += sDepart->distanceA(s);
    }


    return meilleurCheminTrouve;
}

Chemin Algo::meilleurCheminPourDistanceDe(
    int distance,
    Graphe graphe,
    Sommet* sDepart) const
{
    Chemin meilleurCheminTrouve;
    const std::vector<Sommet*> MEILLEURS_SOMMETS =
        _trouverMeilleursSommets(sDepart);

    for(Sommet* s : MEILLEURS_SOMMETS) {
        
    }

    return meilleurCheminTrouve;
}

std::vector<Sommet*> Algo::_trouverMeilleursSommets(const Sommet* s) const {
    std::vector<Sommet*> meilleursSommets;

    return meilleursSommets;
}