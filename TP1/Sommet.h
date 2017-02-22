#include <map>

class Sommet {
public:
    Sommet();
    virtual ~Sommet();
    
    int distanceA(Sommet s);
    virtual void visiter() = 0;
    void diminuerDistanceAvantActif(int distance);

private:
    virtual bool _estActif();

private:
    std::map<Sommet, int> _distances;
};