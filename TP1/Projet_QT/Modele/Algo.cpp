/****************************************************************************
 * Fichier: Algo.cpp
 * Auteurs: Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 * Date: 12 fevrier 2017
 * Description: Implementation de la classe Algo
 ****************************************************************************/
#include <stdexcept>

#include "Algo.h"


Algo::Algo(int nSommetsAEssayer) : _N_SOMMETS_A_ESSAYER(nSommetsAEssayer) {}

Algo::~Algo() {}

/****************************************************************************
 * Fonction: Algo::meilleurCheminPourDistanceDe
 * Description: Détermine le chemin optimal pour une distance max donnée.
 * ParamËtres:  - (int) distance: distance maximale à parcourir(IN)
 *              - (const Graphe&) graphe: Graphe sur lequel optimiser.
 *              - (int) indiceDuSommetDeDepart: indiceDuSommetDeDepart :)
 * Retour:		Le chemin optimal
 ****************************************************************************/

Chemin Algo::meilleurCheminPourDistanceDe (
        int distance,
        const Graphe &graphe,
        int indiceDuSommetDeDepart) const
{

    Chemin meilleurChemin = _meilleurCheminPourDistanceDe(distance, graphe, indiceDuSommetDeDepart, 0, 0);

    // Remettre les sommets dans le bon ordre.
    std::vector<int> sommetsVisites;
    for (int i = (int)meilleurChemin.sommetsVisites.size() - 1; i >= 0; --i) {
        sommetsVisites.push_back(meilleurChemin.sommetsVisites[i]);
    }
    meilleurChemin.sommetsVisites = sommetsVisites;

    return meilleurChemin;
}

/****************************************************************************
 * Fonction: Algo::meilleurCheminPourGainDe
 * Description: Détermine le chemin optimal pour un gain minimal donné.
 * ParamËtres:  - (int) gain: gain minimal à obtenir(IN)
 *              - (const Graphe&) graphe: Graphe sur lequel optimiser.
 *              - (int) indiceDuSommetDeDepart: indiceDuSommetDeDepart :)
 * Retour:		Le chemin optimal
 ****************************************************************************/

Chemin Algo::meilleurCheminPourGainDe (
        int gain,
        const Graphe &graphe,
        int indiceDuSommetDeDepart) const
{

    Chemin meilleurChemin = _meilleurCheminPourGainDe(gain, graphe, indiceDuSommetDeDepart, 0, 0);

    // Remettre les sommets dans le bon ordre.
    std::vector<int> sommetsVisites;
    for (int i = (int)meilleurChemin.sommetsVisites.size() - 1; i >= 0; --i) {
        sommetsVisites.push_back(meilleurChemin.sommetsVisites[i]);
    }
    meilleurChemin.sommetsVisites = sommetsVisites;

    return meilleurChemin;
}

// PRIVATE:

/****************************************************************************
 * Fonction: Algo::_meilleurCheminPourDistanceDe
 * Description: Détermine le chemin optimal pour une distance max donnée.
 * ParamËtres:  - (int) distance: Distance maximale à parcourir(IN)
 *              - (const Graphe&) graphe: Graphe sur lequel optimiser.
 *              - (int) indiceDuSommetDeDepart: indiceDuSommetDeDepart :)
 *              - (int) distanceVersSommet: Distance du dernier point visité au sommetDeDepart.
 *              - (int) profondeurRecursion: Profondeur de la récursion pour cet appel.
 * Retour:		Le chemin optimal
 ****************************************************************************/

Chemin Algo::_meilleurCheminPourDistanceDe (
    int distance,
    const Graphe& graphe,
    int indiceDuSommetDeDepart,
    int distanceVersSommet,
    int profondeurRecursion) const
{
    Graphe copieDuGraphe = graphe;
    Sommet* sommetDeDepart = copieDuGraphe.getSommet(indiceDuSommetDeDepart);

    // On vient de se déplacer vers le sommet de départ.
    copieDuGraphe.diminuerDistanceAvantActif(distanceVersSommet);

    // D'abord, faire visiter le point courant pour modifier la copie du graphe.
    sommetDeDepart->visiter();

    // Ensuite, trouver récursivement le meilleur chemin à partir de la
    // position courante.
    Chemin meilleurCheminTrouve;
    meilleurCheminTrouve.gain = -1;

    int numMeilleursSommets = (profondeurRecursion <= 10) ? _N_SOMMETS_A_ESSAYER : 1;
    const std::vector<int> MEILLEURS_SOMMETS =
        _trouverMeilleursSommets(sommetDeDepart, copieDuGraphe, numMeilleursSommets);

    for(int indiceDuProchainSommet : MEILLEURS_SOMMETS) {
        Sommet* prochainSommet = copieDuGraphe.getSommet(indiceDuProchainSommet);

        int d = sommetDeDepart->distanceA(prochainSommet);
        if (d <= distance) {
            Chemin cheminCourant = _meilleurCheminPourDistanceDe(
                distance - d,
                copieDuGraphe,
                indiceDuProchainSommet,
                d,
                profondeurRecursion + 1);

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

/****************************************************************************
 * Fonction: Algo::_meilleurCheminPourGainDe
 * Description: Détermine le chemin optimal pour un gain minimum donné.
 * ParamËtres:  - (int) gain: Gain minimal à obtenir(IN)
 *              - (const Graphe&) graphe: Graphe sur lequel optimiser.
 *              - (int) indiceDuSommetDeDepart: indiceDuSommetDeDepart :)
 *              - (int) distanceVersSommet: Distance du dernier point visité au sommetDeDepart.
 *              - (int) profondeurRecursion: Profondeur de la récursion pour cet appel.
 * Retour:		Le chemin optimal
 ****************************************************************************/

Chemin Algo::_meilleurCheminPourGainDe(
    int gain,
    const Graphe& graphe,
    int indiceDuSommetDeDepart,
    int distanceVersSommet,
    int profondeurRecursion) const
{
    //     vvvvvvvvvvvvvvvvvvvvvvvvvv
    // >>> Duplication de code FTW!!! <<<   *dies*
    //     ^^^^^^^^^^^^^^^^^^^^^^^^^^

    if (gain > 0) {
        Graphe copieDuGraphe = graphe;
        Sommet* sommetDeDepart = copieDuGraphe.getSommet(indiceDuSommetDeDepart);

        // On vient de se déplacer vers le sommet de départ.
        copieDuGraphe.diminuerDistanceAvantActif(distanceVersSommet);

        // D'abord, faire visiter le point courant pour modifier la copie du graphe.
        sommetDeDepart->visiter();

        // Ensuite, trouver récursivement le meilleur chemin à partir de la
        // position courante.
        Chemin meilleurCheminTrouve;
        meilleurCheminTrouve.distance = INT_MAX/2;

        int numMeilleursSommets = (profondeurRecursion <= 10) ? _N_SOMMETS_A_ESSAYER : 1;
        const std::vector<int> MEILLEURS_SOMMETS =
            _trouverMeilleursSommets(sommetDeDepart, copieDuGraphe, numMeilleursSommets);

        for(int indiceDuProchainSommet : MEILLEURS_SOMMETS) {
            Sommet* prochainSommet = copieDuGraphe.getSommet(indiceDuProchainSommet);

            int d = sommetDeDepart->distanceA(prochainSommet);
            int g = sommetDeDepart->getGain();
            Chemin cheminCourant = _meilleurCheminPourGainDe(
                gain - g,
                copieDuGraphe,
                indiceDuProchainSommet,
                d,
                profondeurRecursion + 1);

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

/****************************************************************************
 * Fonction: Algo::_trouverMeilleursSommets
 * Description: Détermine les sommets optimums vers lesquels on devrait aller.
 *              Le choix est fait selon le gain par mètre.
 * ParamËtres:  - (Sommet*) sommet: Sommet de départ.
                - (Graphe&) graphe: Graphe duquel sont tirés les sommets.
                - (int) numMeilleursSommets: Nombre de sommets optimums désiré.
 * Retour:		Les numMeilleursSommets meilleurs sommets à visiter.
 ****************************************************************************/

std::vector<int> Algo::_trouverMeilleursSommets(
        Sommet* sommet,
        Graphe& graphe,
        int numMeilleursSommets) const
{
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
    for(int i = 0; i < numMeilleursSommets; ++i) {
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
