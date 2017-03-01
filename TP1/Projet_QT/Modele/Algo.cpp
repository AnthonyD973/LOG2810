#include <stdexcept>

#include "Algo.h"


Algo::Algo(int nSommetsAEssayer) : _N_SOMMETS_A_ESSAYER(nSommetsAEssayer) {}

Algo::~Algo() {}

Chemin Algo::meilleurCheminPourDistanceDe (
        int distance,
        const Graphe &graphe,
        int indiceDuSommetDeDepart) const {

    Chemin meilleurChemin = _meilleurCheminPourDistanceDe(distance, graphe, indiceDuSommetDeDepart);

    // Remettre les sommets dans le bon ordre.
    std::vector<int> sommetsVisites;
    for (int i = (int)meilleurChemin.sommetsVisites.size() - 1; i >= 0; --i) {
        sommetsVisites.push_back(meilleurChemin.sommetsVisites[i]);
    }
    meilleurChemin.sommetsVisites = sommetsVisites;

    return meilleurChemin;
}

Chemin Algo::meilleurCheminPourGainDe (
        int distance,
        const Graphe &graphe,
        int indiceDuSommetDeDepart) const {

    Chemin meilleurChemin = _meilleurCheminPourGainDe(distance, graphe, indiceDuSommetDeDepart);

    // Remettre les sommets dans le bon ordre. (>>> Duplication de code FTW!!! <<<   *dies*)
    std::vector<int> sommetsVisites;
    for (int i = (int)meilleurChemin.sommetsVisites.size() - 1; i >= 0; --i) {
        sommetsVisites.push_back(meilleurChemin.sommetsVisites[i]);
    }
    meilleurChemin.sommetsVisites = sommetsVisites;

    return meilleurChemin;
}

// PRIVATE:

Chemin Algo::_meilleurCheminPourDistanceDe (
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
    meilleurCheminTrouve.gain = -1;

    const std::vector<int> MEILLEURS_SOMMETS =
        _trouverMeilleursSommets(sommetDeDepart, copieDuGraphe);

    for(int indiceDuProchainSommet : MEILLEURS_SOMMETS) {
        Sommet* prochainSommet = copieDuGraphe.getSommet(indiceDuProchainSommet);

        int d = sommetDeDepart->distanceA(prochainSommet);
        if (d <= distance) {
            Chemin cheminCourant = _meilleurCheminPourDistanceDe(
                distance - d,
                copieDuGraphe,
                indiceDuProchainSommet);

            cheminCourant.sommetsVisites.push_back(indiceDuSommetDeDepart);
            cheminCourant.distance += sommetDeDepart->distanceA(prochainSommet);
            cheminCourant.gain     += sommetDeDepart->getGain();

            // Un chemin c1 est meilleur qu'un chemin c2 si c1 a un gain plus grand que c2.
            if (cheminCourant.gain > meilleurCheminTrouve.gain) {
                meilleurCheminTrouve = cheminCourant;
            }
        }
    }

    // Enfin, retourner le meilleur chemin trouvé.
    return meilleurCheminTrouve;
}

Chemin Algo::_meilleurCheminPourGainDe(
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
        meilleurCheminTrouve.distance = INT_MAX/2;

        const std::vector<int> MEILLEURS_SOMMETS =
            _trouverMeilleursSommets(sommetDeDepart, copieDuGraphe);

        for(int indiceDuProchainSommet : MEILLEURS_SOMMETS) {
            Sommet* prochainSommet = copieDuGraphe.getSommet(indiceDuProchainSommet);

            int g = sommetDeDepart->getGain();
            Chemin cheminCourant = _meilleurCheminPourGainDe(
                gain - g,
                copieDuGraphe,
                indiceDuProchainSommet);

            cheminCourant.sommetsVisites.push_back(indiceDuSommetDeDepart);
            cheminCourant.distance += sommetDeDepart->distanceA(prochainSommet);
            cheminCourant.gain     += sommetDeDepart->getGain();

            // Un chemin c1 est meilleur qu'un chemin c2 si c1 a une distance plus petite que c2.
            if (cheminCourant.distance < meilleurCheminTrouve.distance) {
                meilleurCheminTrouve = cheminCourant;
            }
        }

        // Enfin, retourner le meilleur chemin trouvé.
        return meilleurCheminTrouve;
    }
    else {
        Chemin meilleurCheminTrouve;
        meilleurCheminTrouve.gain = graphe.getSommet(indiceDuSommetDeDepart)->getGain();
        meilleurCheminTrouve.sommetsVisites.push_back(indiceDuSommetDeDepart);
        return meilleurCheminTrouve;
    }
}

std::vector<int> Algo::_trouverMeilleursSommets(Sommet* sommet, Graphe& graphe) const {
    // D'abord, créer un vecteur des gains par mètre pour chaque sommet.
    std::vector<double> gainsParMetre;
    for (int i = 0; i < graphe.getNumSommets(); ++i) {
        Sommet* s = graphe.getSommet(i);

        int gain     = s->getGain();
        int distance = sommet->distanceA(s);
        if (distance == 0) {
            if (gain > 0) {
                gainsParMetre.push_back(1000000.0);
            }
            else {
                gainsParMetre.push_back(0.0);
            }
        }
        else {
            gainsParMetre.push_back((double)gain/distance);
        }
    }

    // Ensuite, déterminer les meilleurs sommets à partir des gains par mètre.
    std::vector<int> meilleursSommets;
    for(int i = 0; i < _N_SOMMETS_A_ESSAYER; ++i) {
        double meilleurGain = -1.0;
        int indiceDuMeilleurGain = -1;
        
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
