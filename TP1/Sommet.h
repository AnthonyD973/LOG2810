#include <map>
#include <limits.h>

class Sommet {
public:
    Sommet(int gain, const std::map<Sommet*, int>& distances);
    virtual ~Sommet();

    int distanceA(const Sommet* s);
    virtual void visiter() = 0;
    virtual void diminuerDistanceAvantActif(int distance) = 0;

private:
    virtual bool _estActif() = 0;
    virtual int _obtenirDistanceAvantActif() = 0;

private:
    int _gain;
    std::map<Sommet*, int> _distances;
};