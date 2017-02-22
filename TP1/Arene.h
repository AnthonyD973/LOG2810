#include "Sommet.h"

class Arene {
public:
    Arene(const std::map<Sommet, int>& distances);
    virtual ~Arene(const std::map<Sommet, int>& distances);

    virtual void visiter();
    virtual void diminuerDistanceAvantActif(int distance);

private:
    virtual bool _estActif();

private:
    bool _estDejaVisite;
};