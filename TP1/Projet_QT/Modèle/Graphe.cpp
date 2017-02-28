#include <fstream>
#include <string>
#include <sstream>

#include "Graphe.h"
#include "Pokemon.h"
#include "Pokestop.h"
#include "Arene.h"

using namespace std;

Graphe::Graphe(string nomFichier)
{
    
    string dataPoint;
    ifstream monFichier;
    monFichier.open(nomFichier);
    int i=0;
    if (monFichier.is_open())
    {
        string ligne;
        getline(monFichier, ligne);
        stringstream sLigne(ligne);
        
        while ( getline(sLigne, dataPoint, ';') )
        {
            string point[3];
            stringstream sPoint(dataPoint);

            getline(sPoint, point[0], ',');
            getline(sPoint, point[1], ',');
            getline(sPoint, point[2], ';');

            
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
            _sommets[i]->setNom(point[0]);
            _sommets[i]->setGain(point[2]);
            i++;
        }

        string ligne2;
        getline(monFichier, ligne2);
        stringstream sLigne2(ligne2);
        
        while(getline(sLigne2,dataPoint, ';')) //on a finit de creer les sommets et qu'on commence maintenant a enregistrer les distances
        {
            //trouver l'objet sommet* correspondant a point[1]
            //pour ce, boucler a travers le vecteur de sommets pour trouver l'objet sommet qui correspond au string deuxiemePoint
            string point[3];
            stringstream sPoint(dataPoint);

            getline(sPoint, point[0], ',');
            getline(sPoint, point[0], ',');
            getline(sPoint, point[0], ';');

            int indiceDeuxiemePoint;
            for(int i = 0; i < (int)_sommets.size(); i++)
            {
                if(_sommets[i]->getNom() == point[1])
                {
                    indiceDeuxiemePoint=i;
                }
            }
            
            //trouver l'objet sommet* correspondant a point[0]
            //pour ce, boucler a travers le vecteur de sommets pour trouver l'objet sommet qui correspond au string premierPoint
            int indicePremierPoint;
            for(int i = 0; i < (int)_sommets.size(); i++)
            {
                if(_sommets[i]->getNom() == point[0])
                {
                    indicePremierPoint=i;
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

