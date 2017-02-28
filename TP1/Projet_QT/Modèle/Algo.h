#include <vector>

#include "Sommet.h"

#include "Chemin.h"
#include "Graphe.h"

class Algo {
public:
    explicit Algo(int nSommetsAEssayer);
    ~Algo();

    
    Chemin meilleurCheminPourGainDe(
        int gain,
        const Graphe& graphe,
        int indiceDuSommetDeDepart) const;

    Chemin meilleurCheminPourDistanceDe(
        int distance,
        const Graphe& graphe,
        int indiceDuSommetDeDepart) const;

private:
    std::vector<int> _trouverMeilleursSommets(Sommet* s, Graphe& graphe) const;

private:
    const int _N_SOMMETS_A_ESSAYER;

};
