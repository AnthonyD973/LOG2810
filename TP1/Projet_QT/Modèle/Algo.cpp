#include <stdexcept>

#include "Algo.h"

#define EVER (;;)

// TODO : BESOIN D'UN CONSTRUCTEUR PAR COPIE POUR LA CLASSE GRAPHE


Algo::Algo(int nSommetsAEssayer) : _N_SOMMETS_A_ESSAYER(nSommetsAEssayer) {}

Algo::~Algo() {}

Chemin Algo::meilleurCheminPourGainDe(
    int gain,
    const Graphe& graphe,
    int indiceDuSommetDeDepart) const
{
    if (gain > 0) {
        Graphe copieDuGraphe = graphe;
        Sommet* sommetDeDepart = copieDuGraphe.getSommet(indiceDuSommetDeDepart);

        // D'abord, faire visiter le point courant pour modifier la copie du graphe.
        sommetDeDepart->visiter();

        // Ensuite, trouver récursivement le meilleur chemin à partir de la
        // position courante.
        Chemin meilleurCheminTrouve;
        double meilleurGainParMetre = 0.0;

        const std::vector<int> MEILLEURS_SOMMETS =
            _trouverMeilleursSommets(sommetDeDepart, copieDuGraphe);

        for(int indiceDuProchainSommet : MEILLEURS_SOMMETS) {
            Sommet* prochainSommet = copieDuGraphe.getSommet(indiceDuProchainSommet);

            Chemin cheminCourant = meilleurCheminPourGainDe(
                cheminCourant.gain - sommetDeDepart->getGain(), copieDuGraphe, indiceDuProchainSommet);

            cheminCourant.sommetsVisites.push_back(sommetDeDepart);
            cheminCourant.distance += sommetDeDepart->distanceA(prochainSommet);
            cheminCourant.gain     += sommetDeDepart->getGain();

            double gainParMetreCourant;
            if (cheminCourant.distance > 0) {
                gainParMetreCourant = (double)cheminCourant.gain / cheminCourant.distance;
            }
            else {
                gainParMetreCourant = 0;
            }

            if (gainParMetreCourant > meilleurGainParMetre) {
                meilleurCheminTrouve = cheminCourant;
                meilleurGainParMetre = gainParMetreCourant;
            }
        }
        
        // Enfin, retourner le meilleur chemin trouvé.
        return meilleurCheminTrouve;
    }
    else {
        return Chemin();
    }
}

Chemin Algo::meilleurCheminPourDistanceDe(
    int distance,
    const Graphe& graphe,
    int indiceDuSommetDeDepart) const
{
    Graphe copieDuGraphe = graphe;
    Sommet* sommetDeDepart = copieDuGraphe.getSommet(indiceDuSommetDeDepart);

    // D'abord, faire visiter le point courant pour modifier la copie du graphe.
    sommetDeDepart->visiter();

    // Ensuite, trouver récursivement le meilleur chemin à partir de la
    // position courante.
    Chemin meilleurCheminTrouve;
    double meilleurGainParMetre = 0.0;

    const std::vector<int> MEILLEURS_SOMMETS =
        _trouverMeilleursSommets(sommetDeDepart, copieDuGraphe);

    for(int indiceDuProchainSommet : MEILLEURS_SOMMETS) {
        Sommet* prochainSommet = copieDuGraphe.getSommet(indiceDuProchainSommet);

        if (sommetDeDepart->distanceA(prochainSommet) <= distance) {
            Chemin cheminCourant = meilleurCheminPourGainDe(
                cheminCourant.gain - sommetDeDepart->getGain(),
                copieDuGraphe,
                indiceDuProchainSommet);

            cheminCourant.sommetsVisites.push_back(sommetDeDepart);
            cheminCourant.distance += sommetDeDepart->distanceA(prochainSommet);
            cheminCourant.gain     += sommetDeDepart->getGain();

            double gainParMetreCourant;
            if (cheminCourant.distance > 0) {
                gainParMetreCourant = (double)cheminCourant.gain / cheminCourant.distance;
            }
            else {
                gainParMetreCourant = 0;
            }

            if (gainParMetreCourant > meilleurGainParMetre) {
                meilleurCheminTrouve = cheminCourant;
                meilleurGainParMetre = gainParMetreCourant;
            }
        }
    }

    // Enfin, retourner le meilleur chemin trouvé.
    return meilleurCheminTrouve;
}

std::vector<int> Algo::_trouverMeilleursSommets(Sommet* s, Graphe& graphe) const {
    // D'abord, créer un vecteur des gains par mètre pour chaque sommet.
    std::vector<double> gainsParMetre;
    int indiceDuSommet = 0;
    try {
        for EVER {
            Sommet* sommet = graphe.getSommet(indiceDuSommet++);

            int gain     = sommet->getGain();
            int distance = sommet->distanceA(s);
            gainsParMetre.push_back((double)gain/distance);
        }
    }
    catch(const std::out_of_range& e) {}

    // Ensuite, déterminer les meilleurs sommets à partir des gains par mètre.
    std::vector<int> meilleursSommets;
    for(int i = 0; i < _N_SOMMETS_A_ESSAYER; ++i) {
        double meilleurGain = -1.0;
        int indiceDuMeilleurGain;
        
        for (int j = 0; j < (int)gainsParMetre.size(); ++j) {
            if (gainsParMetre[j] > meilleurGain) {
                meilleurGain = gainsParMetre[j];
                indiceDuMeilleurGain = j;
            }
        }

        meilleursSommets.push_back(indiceDuMeilleurGain);
        gainsParMetre[indiceDuMeilleurGain] = -1.0;
    }

    return meilleursSommets;
}
