#include "Sommet.h"

class Pokemon : public Sommet {
public:
    Pokemon();
    virtual ~Pokemon();

    virtual void visiter();
    virtual void diminuerDistanceAvantActif(int distance);

private:
    virtual bool _estActif() const;
    virtual int _obtenirDistanceAvantActif() const;

private:
    int _distAvantActif;
};
