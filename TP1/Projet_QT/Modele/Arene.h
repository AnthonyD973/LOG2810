/*
 Fichier: Arene.h
 Auteur(s): Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 Date de creation: 12 février 2017
 Description: Description de la classe Arene
 */
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
