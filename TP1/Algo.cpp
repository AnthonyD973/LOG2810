#include "Algo.h"


// TODO : BESOIN D'UN CONSTRUCTEUR PAR COPIE POUR LA CLASSE GRAPHE


Algo(int nSommetsAEssayer) : _N_SOMMETS_A_ESSAYER(nSommetsAEssayer) {}

~Algo() {}

Chemin Algo::meilleurCheminPourGainDe(
    int gain,
    const Graphe& graphe,
    int indiceDuSommetDeDepart) const
{
    Graphe copieDuGraphe = graphe;
    Sommet* sDepart = copieDuGraphe.getSommet(indiceDuSommetDeDepart);

    // D'abord, faire visiter le point courant pour modifier la copie du graphe.
    sDepart->visiter();

    // Ensuite, trouver récursivement le meilleur chemin à partir de la
    // position courante.
    Chemin meilleurCheminTrouve;
    int meilleurGainParMetre = 0;

    const std::vector<Sommet*> MEILLEURS_SOMMETS =
        _trouverMeilleursSommets(sDepart);

    for(Sommet* s : MEILLEURS_SOMMETS) {
        Chemin chemin = meilleurCheminPourGainDe(gain - s->getGain(), graphe, s);

        int gainParMetreCourant = chemin.gain / chemin.distance;

        if (gainParMetreCourant >= meilleurGainparMetre) {
            meilleurCheminTrouve = chemin;
            meilleurGainParMetre = gainParMetreCourant;
        }
    }


    return meilleurCheminTrouve;
}

Chemin Algo::meilleurCheminPourDistanceDe(
    int distance,
    const Graphe& graphe,
    int indiceDuSommetDeDepart) const
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