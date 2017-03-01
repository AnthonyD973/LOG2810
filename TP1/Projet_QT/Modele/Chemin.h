/*
 Fichier: Chemin.h
 Auteur(s): Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 Date de creation: 12 février 2017
 Description: Description de la classe Chemin
 */
#ifndef CHEMIN_H
#define CHEMIN_H

#include <vector>

#include "Modele/Sommet.h"

using namespace std;

class Chemin {
public:
    Chemin() : distance(0), gain(0) {}

    int distance;
    int gain;
    std::vector<int> sommetsVisites;
};

#endif // !CHEMIN_H
