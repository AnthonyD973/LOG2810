#include "Sommet.h"

class Pokemon : public Sommet {
public:
    Pokemon(const std::map<Sommet, int>& distances);
    virtual ~Pokemon();

    virtual void visiter();
    virtual void diminuerDistanceAvantActif(int distance);

private:
    virtual bool _estActif();

private:
    int _distAvantActif;
};