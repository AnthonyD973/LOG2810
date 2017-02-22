#include "Sommet.h"

class Pokestop : public Sommet {
public:
    Pokestop(const std::map<Sommet, int>& distances);
    virtual ~Pokestop();

    virtual void visiter();
    virtual void diminuerDistanceAvantActif(int distance);

private:
    virtual bool _estActif();

private:
    int _distAvantActif;
};