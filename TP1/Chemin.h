#include <vector>

class Chemin {
public:
    Chemin(vector<Sommet*>pointsVisites);
    int distance;
    int gain;
    std::vector<Sommet*>_pointsVisites;
};
