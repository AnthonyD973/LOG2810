#ifndef CHEMIN_H
#define CHEMIN_H

#include <vector>

#include "Modèle/Sommet.h"

using namespace std;

class Chemin {
public:
    Chemin() {}

    int distance;
    int gain;
    std::vector<int> sommetsVisites;
};

#endif // !CHEMIN_H
