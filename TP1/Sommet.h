#include <map>

class Sommet {
public:
    Sommet(const std::map<Sommet, int>& distances);
    virtual ~Sommet();

    int distanceA(Sommet s);
    virtual void visiter() = 0;
    virtual void diminuerDistanceAvantActif(int distance) = 0;

private:
    virtual bool _estActif();

private:
    std::map<Sommet, int> _distances;
};