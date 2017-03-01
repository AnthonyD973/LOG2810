/*
 Fichier: Pokestop.h
 Auteur(s): Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 Date de creation: 12 février 2017
 Description: Description de la classe Pokestop
 */
#include "Sommet.h"

class Pokestop : public Sommet {
public:
    Pokestop();
    virtual Sommet* newClone() const { return new Pokestop(*this); }
    virtual ~Pokestop();

    virtual void visiter();
    virtual void diminuerDistanceAvantActif(int distance);

private:
    virtual bool _estActif() const;
    virtual int _obtenirDistanceAvantActif() const;

private:
    int _distAvantActif;
};
