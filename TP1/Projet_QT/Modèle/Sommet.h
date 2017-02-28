#ifndef SOMMET_H
#define SOMMET_H

#include <string>
#include <map>
#include <limits.h>

using namespace std;

class Sommet {
public:
    Sommet();
    virtual ~Sommet();

    int distanceA(Sommet *s);
    inline int getGain() const { return _gain; }
    string getNom() const;
    virtual void visiter() = 0;
    virtual void diminuerDistanceAvantActif(int distance) = 0;
    void setNom(string nomSommet);
    void setGain(string quantiteGain);
    void addDistance(Sommet* deuxiemePoint, string distance);

private:
    virtual bool _estActif() const = 0;
    virtual int _obtenirDistanceAvantActif() const = 0;

private:
    int _gain;
    string _nom;
    std::map<Sommet*, int> _distances;
};

#endif // !SOMMET_H
