/*
 Fichier: Pokemon.h
 Auteur(s): Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 Date de creation: 12 février 2017
 Description: Description de la classe Pokemon
 */
#include "Sommet.h"

class Pokemon : public Sommet {
public:
    Pokemon();
    virtual Sommet* newClone() const { return new Pokemon(*this); }
    virtual ~Pokemon();

    virtual void visiter();
    virtual void diminuerDistanceAvantActif(int distance);

private:
    virtual bool _estActif() const;
    virtual int _obtenirDistanceAvantActif() const;

private:
    int _distAvantActif;
};
