#include <vector>

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
    std::vector<Sommet*> _trouverMeilleursSommets(const Sommet* s, const Graphe& graphe) const;

private:
    const int _N_SOMMETS_A_ESSAYER;

};