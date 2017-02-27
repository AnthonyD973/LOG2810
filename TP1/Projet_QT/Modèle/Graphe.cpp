#include "Graphe.h"
#include <fstream>
#include <string>
using namespace std;

void Graphe::Graphe(string nomFichier): _sommets
{
    //lis le .txt
    //premiere sequence: point1, type, gain
    //2e sequence: point1, point2, distance
    
    //lis premiere sequence: cree les sommets
    //lis 2e sequence: sauvegarde la distance entre les sommets
   /*
    sring dataPoint;
    
    fichier >> dataPoint;
    
    sstream >> nomPoint
    
    Sommet s;
    s.setNom(nomPoint);
    
    */
    
    
    
    
    
    
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
                _sommets[i]=new Pokemon;
                _sommets[i].setNom(point[0]);
                _sommets[i].setGain(point[2]);
            }
            else if(point[1]=="pokestop")
            {
                _sommets[i]=new Pokestop;
                _sommets[i].setNom(point[0]);
                _sommets[i].setGain(point[2]);
            }
            else if(point[1]=="arene")
            {
                _sommets[i]=new Arene;
                _sommets[i].setNom(point[0]);
                _sommets[i].setGain(point[2]);
            }
            else //veut dire qu'on a finit de creer les sommets et qu'on commence maintenant a enregistrer les distances
            {
                
            }
            i++;
        }
        monFichier.close();
    }
}

Chemin plusCourtChemin(string, int)
{
    
}

Chemin gainMaximal (string, int)
{
    
}
