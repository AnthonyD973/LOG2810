/*
 Fichier: Algo.h
 Auteur(s): Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 Date de creation: 12 février 2017
 Description: Description de la classe Algo
 */
#include <vector>

#include "Sommet.h"

#include "Chemin.h"
#include "Graphe.h"

class Algo {
public:
    explicit Algo(int nSommetsAEssayer);
    ~Algo();


    Chemin meilleurCheminPourDistanceDe(
        int distance,
        const Graphe& graphe,
        int indiceDuSommetDeDepart) const;
    
    Chemin meilleurCheminPourGainDe(
        int gain,
        const Graphe& graphe,
        int indiceDuSommetDeDepart) const;

private:
    Chemin _meilleurCheminPourDistanceDe(
        int distance,
        const Graphe& graphe,
        int indiceDuSommetDeDepart,
        int distanceVersSommet,
        int profondeurRecursion) const;

    Chemin _meilleurCheminPourGainDe(
        int gain,
        const Graphe& graphe,
        int indiceDuSommetDeDepart,
        int distanceVersSommet,
        int profondeurRecursion) const;

    std::vector<int> _trouverMeilleursSommets(
        Sommet* sommet,
        Graphe& graphe,
        int numMeilleursSommets) const;

private:
    const int _N_SOMMETS_A_ESSAYER;

};
