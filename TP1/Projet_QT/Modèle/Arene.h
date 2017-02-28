#include "Sommet.h"

class Arene : public Sommet {
public:
    Arene();
    virtual Sommet* newClone() const { return new Arene(*this); }
    virtual ~Arene();

    virtual void visiter();
    virtual void diminuerDistanceAvantActif(int distance);

private:
    virtual bool _estActif() const;
    virtual int _obtenirDistanceAvantActif() const;

private:
    bool _estDejaVisite;
};
