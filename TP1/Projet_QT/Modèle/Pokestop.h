#include "Sommet.h"

class Pokestop : public Sommet {
public:
    Pokestop();
    virtual ~Pokestop();

    virtual void visiter();
    virtual void diminuerDistanceAvantActif(int distance);

private:
    virtual bool _estActif() const;
    virtual int _obtenirDistanceAvantActif() const;

private:
    int _distAvantActif;
};
