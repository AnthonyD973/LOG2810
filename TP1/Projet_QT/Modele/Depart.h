/*
 Fichier: Depart.h
 Auteur(s): Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 Date de creation: 12 février 2017
 Description: Description de la classe Depart
 */
#ifndef DEPART_H
#define DEPART_H

#include "Sommet.h"

class Depart : public Sommet {
public:
    Depart() {}
    virtual Sommet* newClone() const { return new Depart(*this); }
    virtual ~Depart() {}

    virtual void visiter() {}
    virtual void diminuerDistanceAvantActif(int distance) {}

private:
    virtual bool _estActif() const { return false; }
    virtual int _obtenirDistanceAvantActif() const { return INT_MAX; }
};


#endif // DEPART_H
