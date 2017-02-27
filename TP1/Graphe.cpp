#include "Graphe.h"
#include <fstream>
#include <string>
using namespace std;

void Graphe::Graphe(string nomFichier): _sommets
{
    
    string dataPoint;
    ifstream monFichier;
    monFichier.open("nomFichier");
    int i=0;
    if (monFichier.is_open())
    {
        while ( getline(monFichier,dataPoint, ';') )
        {
            String[] point = dataPoint.split(",");

            
            if(point[1]=="pokemon")
            {
                _sommets.push_back(new Pokemon);
                _sommets[i].setNom(point[0]);
                _sommets[i].setGain(point[2]);
            }
            else if(point[1]=="pokestop")
            {
                _sommets.push_back(new Pokestop);
                _sommets[i].setNom(point[0]);
                _sommets[i].setGain(point[2]);
            }
            else if(point[1]=="arene")
            {
                _sommets.push_back(new Arene);
                _sommets[i].setNom(point[0]);
                _sommets[i].setGain(point[2]);
            }
            else //veut dire qu'on a finit de creer les sommets et qu'on commence maintenant a enregistrer les distances
            {
                _sommets[i].addDistance(point[1], point[2]);
            }
            i++;
        }
        monFichier.close();
    }
}

