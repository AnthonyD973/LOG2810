#include <vector>

class Chemin {
public:
    Chemin();
    int distance;
    int gain;
    std::vector<Sommet>_pointsVisites;
};
