#include "Chemin.h"
using namespace std;
Chemin::Chemin(vector<Sommet*> pointsVisites)
{
    //on calcule la distance et le gain a partir du vecteur de points visites
    
    //distance: additionne la distance entre chaque element du vecteur avec le prochain element
    distance = 0;
    for(int i=0; i<pointsVisites.size()-1;i++)
    {
        distance += *pointsVisites[i].distanceA(pointsVisites[i+1]);
    }
    
    //addition des gains de tous les points visites
    gain = 0;
    for(int j=0; j<pointsVisites.size();j++)
    {
        gain += *pointsVisites[j].getGain();
    }
    
}
