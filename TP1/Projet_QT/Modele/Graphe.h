/*
 Fichier: Graphe.h
 Auteur(s): Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 Date de creation: 12 février 2017
 Description: Description de la classe Graphe
 */
#ifndef GRAPHE_H
#define GRAPHE_H

#include <string>
#include <vector>

#include "Sommet.h"

using namespace std;

class Graphe {
    
public:
    Graphe(string nomFichier);
    Graphe(const Graphe& graphe); // Constructeur par copie
    ~Graphe();

    Sommet* getSommet(int indiceDuSommet);
    const Sommet* getSommet(int indiceDuSommet) const;

    int getNumSommets() const;

    void diminuerDistanceAvantActif(int distance);
    
private:
    std::vector<Sommet*> _sommets;
};

#endif // !GRAPHE_H
