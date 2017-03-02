/****************************************************************************
 * Fichier: Sommet.cpp
 * Auteurs: Philippe Courtemanche, Anthony Dentinger et Marc-Gaël Hounto
 * Date: 12 fevrier 2017
 * Description: Implementation de la classe Sommet
 ****************************************************************************/

#include "Sommet.h"

using namespace std;

Sommet::Sommet() { }

Sommet::Sommet(const Sommet& s)
    : _gain(s._gain), _nom(s._nom), _distances()
{ }

Sommet::~Sommet() {}

/****************************************************************************
 * Fonction: Sommet::distanceA
 * Description: Fonction qui obtient la distance au sommet entré en paramètre
 * ParamËtres:	- (Sommet*) s: le sommet(IN)
 * Retour:		(int) la distance entre les deux sommets
 ****************************************************************************/
int Sommet::distanceA(Sommet* s) {
    int ret;

    if (s->_estActif()) {
        ret = _distances.at(s);
    }
    else {
        int daa = s->_obtenirDistanceAvantActif();
        
        bool distEstInfinie = (daa >= INT_MAX - 1);
        if (!distEstInfinie) {
            int d = _distances.at(s);
            ret = (daa > d) ? daa - d : d;
        }
        else {
            ret = daa;
        }
    }
    return ret;
}

void Sommet::setNom(string nomSommet)
{
    _nom = nomSommet;
}

void Sommet::setGain(int quantiteGain)
{
    _gain = quantiteGain;
}

/****************************************************************************
 * Fonction: Sommet::addDistance
 * Description: Fonction ajoute une distance entre un nouveau sommet et le sommet courant
 * ParamËtres:	- (Sommet*) s: le nouveau sommet(IN)
                - (int) distance: distance entre les deux sommets(IN)
 * Retour:		Aucun
 ****************************************************************************/
void Sommet::addDistance(Sommet* s, int distance)
{
    //creer une paire avec l'objet 2e point et cette distance
    pair <Sommet*,int> temp1;
    temp1 = make_pair (s, distance);

    //ajouter cette paire dans la map de l'attribut _distances de l'objet courant
    _distances.insert(temp1);
    
    //ensuite, creer une paire avec l'objet courant et cette distance
    pair <Sommet*,int> temp2;
    temp2 = make_pair (this, distance);
    
    //ajouter cette paire dans la map de l'attribut _distances de l'objet correspondant au string deuxiemePoint
    s->_distances.insert(temp2);
    
}

string Sommet::getNom() const
{
    return _nom;
}
