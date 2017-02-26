#include "Sommet.h"

class Pokemon : public Sommet {
public:
    Pokemon(const std::map<Sommet, int>& distances);
    virtual ~Pokemon();

    virtual void visiter();
    virtual void diminuerDistanceAvantActif(int distance);

private:
    virtual bool _estActif() const;

private:
    int _distAvantActif;
};