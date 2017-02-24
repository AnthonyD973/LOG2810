#include <vector>

#include "Chemin.h"
#include "Graphe.h"

class Algo {
public:
    explicit Algo(int nSommetsAEssayer);
    ~Algo();

    
    Chemin meilleurCheminPourGainDe(
        int gain,
        Graphe graphe, // Oui, c'est bien une copie du graphe qui est mise sur la pile! :)
        const Sommet* sDepart) const;

    Chemin meilleurCheminPourDistanceDe(
        int distance,
        Graphe graphe, // Oui, c'est bien une copie du graphe qui est mise sur la pile! :)
        const Sommet* sDepart) const;

private:
    std::vector<Sommet*> _trouverMeilleursSommets(const Sommet* s) const;

private:
    const int _N_SOMMETS_A_ESSAYER;

};