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

    int distanceA(const Sommet* s) const;
    inline int getGain() const { return _gain; }
    virtual void visiter() = 0;
    virtual void diminuerDistanceAvantActif(int distance) = 0;
    string getNom() const;
    void setNom(string nomSommet);
    void setGain(string quantiteGain);
    void addDistance(string deuxiemePoint, string distance);

private:
    virtual bool _estActif() const = 0;
    virtual int _obtenirDistanceAvantActif() const = 0;

private:
    int _gain;
    string _nom;
    std::map<Sommet*, int> _distances;
};

#endif // !SOMMET_H
