#include <fstream>
#include <string>
#include <sstream>

#include "Graphe.h"
#include "Pokemon.h"
#include "Pokestop.h"
#include "Arene.h"
#include "Depart.h"

using namespace std;

Graphe::Graphe(string nomFichier)
{
    ifstream monFichier;
    monFichier.open(nomFichier);
    if (monFichier.is_open())
    {
        string ligne1;
        getline(monFichier, ligne1);
        stringstream sLigne(ligne1);

        string dataPoint;
        // D'abord, créer les sommets conaissant leur type et leur gain.
        while ( getline(sLigne, dataPoint, ';') )
        {
            string point[3];
            stringstream sPoint(dataPoint);

            getline(sPoint, point[0], ',');
            getline(sPoint, point[1], ',');
            getline(sPoint, point[2]);

            
            if(point[1]=="pokemon")
            {
                _sommets.push_back(new Pokemon);
            }
            else if(point[1]=="pokestop")
            {
                _sommets.push_back(new Pokestop);
            }
            else if(point[1]=="arene")
            {
                _sommets.push_back(new Arene);
            }
            else { // Point de départ
                _sommets.push_back(new Depart);
            }
            _sommets.back()->setNom (point[0]);
            _sommets.back()->setGain(point[2]);
        }

        string ligne2;
        getline(monFichier, ligne2);
        stringstream sLigne2(ligne2);
        
        while(getline(sLigne2,dataPoint, ';')) //on a fini de creer les sommets et qu'on commence maintenant a enregistrer les distances
        {
            string point[3];
            stringstream sPoint(dataPoint);

            getline(sPoint, point[0], ',');
            getline(sPoint, point[1], ',');
            getline(sPoint, point[2]);

            // trouver l'objet sommet* correspondant a point[0]
            // pour ce, boucler a travers le vecteur de sommets pour trouver l'objet sommet qui correspond au string premierPoint
            int indicePremierPoint;
            for(int i = 0; i < (int)_sommets.size(); i++)
            {
                if(_sommets[i]->getNom() == point[0])
                {
                    indicePremierPoint=i;
                    break;
                }
            }

            // trouver l'objet sommet* correspondant a point[1]
            // pour ce, boucler a travers le vecteur de sommets pour trouver l'objet sommet qui correspond au string deuxiemePoint
            int indiceDeuxiemePoint;
            for(int i = 0; i < (int)_sommets.size(); i++)
            {
                if(_sommets[i]->getNom() == point[1])
                {
                    indiceDeuxiemePoint=i;
                    break;
                }
            }

            _sommets[indicePremierPoint]->addDistance(_sommets[indiceDeuxiemePoint], point[2]);

        }
        monFichier.close();
    }
}

Sommet* Graphe::getSommet(int indiceDuSommet) {
    return _sommets[indiceDuSommet];
}

const Sommet* Graphe::getSommet(int indiceDuSommet) const {
    return _sommets[indiceDuSommet];
}

