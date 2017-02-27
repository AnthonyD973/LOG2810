#include <vector>
class Graphe{
    
public:
    void Graphe(string nomFichier);
    
private:
    std::vector<Sommet*> _sommets;
};
