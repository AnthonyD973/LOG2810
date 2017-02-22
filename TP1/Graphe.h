#include <vector>
class Graphe{
    
public:
    void Graphe(string nomFichier);
   // operator<<(ostream, Graphe); est-ce qu'on implemente?
    Chemin plusCourtChemin(string, int);
    Chemin gainMaximal(string, int);
    
private:
    std::vector<Sommet*>_sommets;
};
