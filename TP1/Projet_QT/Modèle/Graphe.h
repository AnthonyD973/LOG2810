#include <string>
#include <vector>

#include "Sommet.h"

using namespace std;

class Graphe {
    
public:
    Graphe(string nomFichier);

    Sommet* getSommet(int indiceDuSommet);
    const Sommet* getSommet(int indiceDuSommet) const;
    
private:
    std::vector<Sommet*> _sommets;
};
